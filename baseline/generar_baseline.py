"""
Baseline del TFG: Claude escribe HLS C++ directamente y se sintetiza con
Vitis HLS, SIN ninguno de los agentes del pipeline (ni Generador sobre Allo,
ni Ejecutor, ni Validador, ni cascada L1-L4, ni política de escalada).

Sirve de grupo de control: misma spec de entrada (specs/*.yaml), mismo
modelo, mismas condiciones de síntesis y mismo criterio funcional que el
pipeline, para poder atribuir las diferencias a la propuesta del TFG.

Modos:
  oneshot  -> una sola generación por run (pass@1). Lo que haría alguien
              pidiéndole el acelerador a Claude sin más.
  feedback -> hasta --max-iter intentos por run devolviendo a Claude la
              salida de Vitis tal cual (sin Validador ni escalada). Variante
              intermedia: aísla cuánto aporta "Allo + cascada" frente a
              "C++ + lazo con el compilador".

Uso (desde TFG/baseline, con el entorno de Vitis HLS ya cargado):
  python3 -u generar_baseline.py --runs 5 --objetivo-ii 20
  python3 -u generar_baseline.py --runs 5 --objetivo-ii 10 --modo feedback
  python3 -u generar_baseline.py --spec ../specs/spec_fft_radix4.yaml --runs 5 --objetivo-ii 5

Es reanudable: los runs que ya tienen resultado.json se saltan. Si el SDK
falla (p. ej. cuota de Pro agotada, issue #1031) el script se detiene SIN
registrar el run como fallo del modelo; basta con relanzar el mismo comando.
"""

import argparse
import asyncio
import json
import re
import shutil
import sys
import time
from datetime import datetime
from pathlib import Path

from claude_agent_sdk import AssistantMessage, ClaudeAgentOptions, ResultMessage, TextBlock, query

import arnes
from comun import (
    DIR_RESULTADOS_BASELINE, FLOW_TARGET_POR_DEFECTO, MAX_ITERACIONES_POR_DEFECTO, PART_POR_DEFECTO,
    PERIODO_RELOJ_NS_POR_DEFECTO, SPEC_POR_DEFECTO, TIMEOUT_VITIS_POR_DEFECTO, TOLERANCIA_POR_DEFECTO,
    cargar_spec, firma_cpp,
)


class ErrorInfraestructura(Exception):
    """Fallo del SDK / cuota: no es culpa del modelo, no se registra el run."""


# ---------------------------------------------------------------------------
# Prompts. Deliberadamente "de usuario competente", sin pistas de diseño
# (nada de particionado, dataflow, etc.): esas pistas son justo lo que el
# pipeline descubre por sí mismo y darlas aquí sesgaría la comparación.
# ---------------------------------------------------------------------------

SYSTEM_PROMPT = """\
Eres un ingeniero experto en síntesis de alto nivel (HLS) para FPGA con
AMD/Xilinx Vitis HLS 2023.1. Escribes código C++ sintetizable, correcto y
optimizado con las directivas (#pragma HLS ...) que consideres oportunas.

Reglas de entrega:
- Devuelve UN ÚNICO bloque de código ```cpp con el archivo kernel.cpp completo.
- La función top debe tener EXACTAMENTE la firma que se te indica (mismo
  nombre, mismos parámetros, mismo orden, mismos tipos).
- No incluyas main() ni testbench: el testbench ya existe.
- Puedes usar la biblioteca estándar de C++ soportada por Vitis HLS y las
  cabeceras de Vitis (hls_math.h, ap_int.h, ap_fixed.h, hls_stream.h...).
- No expliques nada fuera del bloque de código.
"""


def construir_prompt(spec: dict, part: str, periodo_ns: float) -> str:
    objetivo_ii = spec["restricciones"]["objetivo_ii"]
    # La spec se pasa igual que al Generador del pipeline (json.dumps del
    # YAML); lo que se añade es solo lo que exige el cambio de lenguaje
    # (firma C++ y objetivo de síntesis). Deliberadamente NO se describe el
    # golden model (referencia, orden de salida, tolerancia): el Generador
    # tampoco lo recibe y solo lo descubre fallando en L2.
    partes = [
        f"Especificación del bloque:\n{json.dumps(spec, indent=2, ensure_ascii=False)}",
        f"Firma obligatoria de la función top:\n{firma_cpp(spec)}",
        "Las entradas se leen y las salidas se escriben in-place. Los tipos allo.float32 "
        "de la spec corresponden a float en C++.",
        f"Objetivo de síntesis: dispositivo {part}, periodo de reloj {periodo_ns} ns, "
        f"y II <= {objetivo_ii} en todos los bucles pipelineados del diseño "
        f"(se mide el peor II de todos ellos en el informe de csynth).",
    ]
    return "\n\n".join(partes)


def construir_prompt_feedback(prompt_base: str, codigo_anterior: str, errores: str) -> str:
    return (
        f"{prompt_base}\n\n"
        f"Tu versión anterior de kernel.cpp:\n```cpp\n{codigo_anterior}\n```\n\n"
        f"Resultado al ejecutarla con Vitis HLS (C simulation + síntesis):\n{errores}\n\n"
        f"Corrige el código y devuelve el kernel.cpp completo."
    )


def extraer_codigo(texto: str) -> str | None:
    bloques = re.findall(r"```(?:cpp|c\+\+|cc|c|hpp)?[ \t]*\n(.*?)```", texto, re.DOTALL | re.IGNORECASE)
    if not bloques:
        return None
    return max(bloques, key=len).strip() + "\n"


async def llamar_claude(prompt: str, modelo: str | None) -> dict:
    # Mismas opciones que el Generador del pipeline: sin herramientas y
    # dontAsk (si no, el SDK puede quedarse colgado esperando un permiso).
    opciones = ClaudeAgentOptions(
        system_prompt=SYSTEM_PROMPT,
        allowed_tools=[],
        permission_mode="dontAsk",
        **({"model": modelo} if modelo else {}),
    )
    texto, uso = "", {}
    t0 = time.monotonic()
    try:
        async for msg in query(prompt=prompt, options=opciones):
            if isinstance(msg, AssistantMessage):
                for bloque in msg.content:
                    if isinstance(bloque, TextBlock):
                        texto += bloque.text
            elif isinstance(msg, ResultMessage):
                uso = {
                    "duracion_ms": getattr(msg, "duration_ms", None),
                    "num_turns": getattr(msg, "num_turns", None),
                    "usage": getattr(msg, "usage", None),
                    "total_cost_usd": getattr(msg, "total_cost_usd", None),
                    "is_error": getattr(msg, "is_error", None),
                }
                if uso["is_error"]:
                    raise ErrorInfraestructura(f"ResultMessage con is_error=True: {getattr(msg, 'result', '')}")
    except ErrorInfraestructura:
        raise
    except Exception as e:  # noqa: BLE001 -- issue #1031 y similares
        raise ErrorInfraestructura(f"{type(e).__name__}: {e}") from e
    if not texto.strip():
        raise ErrorInfraestructura("Respuesta vacía del SDK (¿cuota agotada?)")
    return {"texto": texto, "uso": uso, "t_generacion_s": round(time.monotonic() - t0, 1)}


# ---------------------------------------------------------------------------
# Un intento = generar -> escribir archivos -> Vitis (csim + csynth) -> analizar
# ---------------------------------------------------------------------------

async def ejecutar_intento(dir_intento: Path, prompt: str, spec: dict, vectores, args) -> tuple[dict, str | None, str]:
    dir_intento.mkdir(parents=True, exist_ok=True)
    (dir_intento / "prompt.txt").write_text(prompt)

    gen = await llamar_claude(prompt, args.modelo)
    (dir_intento / "respuesta.txt").write_text(gen["texto"])
    codigo = extraer_codigo(gen["texto"])
    registro = {"t_generacion_s": gen["t_generacion_s"], "uso_sdk": gen["uso"], "codigo_extraido": codigo is not None}

    if codigo is None:
        registro.update({"etapa_fallo": "sin_codigo", "exito": False, "csim_compila": False, "csim_ok": False,
                         "sintesis_ok": False, "cumple_ii": False, "metricas_hls": None})
        return registro, None, "No se encontró ningún bloque ```cpp en tu respuesta."

    (dir_intento / "kernel.cpp").write_text(codigo)
    arnes.escribir_vectores_h(spec, vectores, dir_intento / "vectores.h")
    arnes.escribir_testbench(spec, args.tolerancia, dir_intento / "tb.cpp")
    arnes.escribir_run_tcl(spec, args.part, args.periodo_reloj, args.flow_target, dir_intento / "run.tcl")

    objetivo_ii = spec["restricciones"]["objetivo_ii"]
    print(f"      Vitis HLS (csim + csynth, timeout {args.timeout}s)...", flush=True)
    ejec = arnes.ejecutar_vitis(dir_intento, args.timeout)
    analisis = arnes.analizar_ejecucion(ejec, dir_intento, spec, objetivo_ii, args.periodo_reloj)
    registro.update(analisis)

    if not args.conservar_proyecto:
        shutil.rmtree(dir_intento / "proj", ignore_errors=True)

    if registro["etapa_fallo"] == "entorno_csim":
        raise ErrorInfraestructura(
            "La csim falló por el entorno (enlazador de Vitis vs libm del sistema), no por el código: "
            f"{registro['fallo_entorno_csim']}. Revisa {dir_intento / 'vitis.log'}"
        )

    feedback = arnes.resumen_errores_para_feedback(analisis, ejec["log"], objetivo_ii)
    return registro, codigo, feedback


async def ejecutar_run(dir_run: Path, spec: dict, vectores, args) -> dict:
    prompt_base = construir_prompt(spec, args.part, args.periodo_reloj)
    max_iter = 1 if args.modo == "oneshot" else args.max_iter
    intentos, prompt, codigo_anterior = [], prompt_base, None
    t0 = time.monotonic()

    for j in range(1, max_iter + 1):
        print(f"    intento {j}/{max_iter}", flush=True)
        registro, codigo, feedback = await ejecutar_intento(dir_run / f"intento_{j:02d}", prompt, spec, vectores, args)
        registro["intento"] = j
        intentos.append(registro)
        print(f"      -> etapa_fallo={registro['etapa_fallo']} csim_ok={registro['csim_ok']} "
              f"sintesis_ok={registro['sintesis_ok']} II={(registro['metricas_hls'] or {}).get('II')}", flush=True)
        if registro["exito"]:
            break
        if codigo is not None:
            codigo_anterior = codigo
        prompt = (construir_prompt_feedback(prompt_base, codigo_anterior, feedback)
                  if codigo_anterior else prompt_base + "\n\n" + feedback)

    final = intentos[-1]
    return {
        "bloque": spec["bloque"],
        "objetivo_ii": spec["restricciones"]["objetivo_ii"],
        "modo": args.modo,
        "exito": final["exito"],
        "n_intentos": len(intentos),
        "t_total_s": round(time.monotonic() - t0, 1),
        "final": final,
        "intentos": intentos,
    }


async def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--spec", type=Path, default=SPEC_POR_DEFECTO)
    p.add_argument("--objetivo-ii", type=int, default=None, help="Sobrescribe restricciones.objetivo_ii de la spec")
    p.add_argument("--runs", type=int, default=5, help="Runs independientes (el LLM no es determinista)")
    p.add_argument("--modo", choices=["oneshot", "feedback"], default="oneshot")
    p.add_argument("--max-iter", type=int, default=MAX_ITERACIONES_POR_DEFECTO, help="Solo en modo feedback")
    p.add_argument("--n-vectores", type=int, default=1,
                   help="1 = exactamente el vector de L2 (seed 0); >1 añade seeds 1, 2...")
    p.add_argument("--tolerancia", type=float, default=TOLERANCIA_POR_DEFECTO)
    p.add_argument("--part", default=PART_POR_DEFECTO)
    p.add_argument("--periodo-reloj", type=float, default=PERIODO_RELOJ_NS_POR_DEFECTO)
    p.add_argument("--flow-target", default=FLOW_TARGET_POR_DEFECTO)
    p.add_argument("--timeout", type=int, default=TIMEOUT_VITIS_POR_DEFECTO)
    p.add_argument("--modelo", default=None, help="Por defecto el mismo que usa el pipeline (el del SDK)")
    p.add_argument("--salida", type=Path, default=DIR_RESULTADOS_BASELINE)
    p.add_argument("--conservar-proyecto", action="store_true", help="No borrar proj/ tras analizar (ocupa mucho)")
    args = p.parse_args()

    if not arnes.vitis_hls_disponible():
        sys.exit("vitis_hls no está en el PATH. Carga antes el entorno: source <Vitis>/settings64.sh")

    spec = cargar_spec(args.spec, args.objetivo_ii)
    objetivo_ii = spec["restricciones"]["objetivo_ii"]
    vectores = arnes.generar_vectores(spec, args.n_vectores)
    dir_config = args.salida / spec["bloque"] / f"ii{objetivo_ii}_{args.modo}"
    dir_config.mkdir(parents=True, exist_ok=True)

    (dir_config / "config.json").write_text(json.dumps({
        "spec_ruta": str(args.spec), "spec": spec, "modo": args.modo, "max_iter": args.max_iter,
        "n_vectores": args.n_vectores, "tolerancia": args.tolerancia, "part": args.part,
        "periodo_reloj_ns": args.periodo_reloj, "flow_target": args.flow_target, "timeout_s": args.timeout,
        "modelo": args.modelo or "(por defecto del SDK)", "system_prompt": SYSTEM_PROMPT,
    }, indent=2, ensure_ascii=False))

    print(f"Baseline {spec['bloque']} | objetivo_ii={objetivo_ii} | modo={args.modo} | runs={args.runs}")
    print(f"Resultados en {dir_config}")

    for k in range(1, args.runs + 1):
        dir_run = dir_config / f"run_{k:02d}"
        if (dir_run / "resultado.json").exists() and arnes.run_contaminado_por_entorno(dir_run):
            destino = dir_run.with_name(dir_run.name + f"_descartado_entorno_{datetime.now():%Y%m%d_%H%M%S}")
            dir_run.rename(destino)
            print(f"  run {k:02d}: su csim falló por el entorno, no por el código -> apartado en "
                  f"{destino.name} y se repite")
        if (dir_run / "resultado.json").exists():
            print(f"  run {k:02d}: ya hecho, se salta")
            continue
        if dir_run.exists():
            shutil.rmtree(dir_run)  # run a medias de una ejecución interrumpida
        print(f"  run {k:02d} ({datetime.now():%H:%M:%S})", flush=True)
        try:
            resultado = await ejecutar_run(dir_run, spec, vectores, args)
        except ErrorInfraestructura as e:
            # Se conserva lo hecho como evidencia del fallo, pero renombrado
            # para que el siguiente lanzamiento repita el run desde cero.
            if dir_run.exists():
                destino = dir_run.with_name(f"{dir_run.name}_descartado_{datetime.now():%Y%m%d_%H%M%S}")
                dir_run.rename(destino)
                print(f"\n    (lo generado se ha guardado en {destino.name})")
            print(f"\n[!] Fallo de infraestructura (no del modelo): {e}\n"
                  f"    El run {k:02d} NO se ha registrado. Corrige la causa (o espera a tener cuota, si es "
                  f"del SDK) y relanza el mismo comando: se reanudará desde aquí.")
            sys.exit(2)
        resultado["fecha"] = datetime.now().isoformat(timespec="seconds")
        (dir_run / "resultado.json").write_text(json.dumps(resultado, indent=2, ensure_ascii=False))
        print(f"  run {k:02d}: {'ÉXITO' if resultado['exito'] else 'fallo'} "
              f"({resultado['n_intentos']} intento(s), {resultado['t_total_s']}s)")

    print("\nHecho. Resumen: python3 resumir.py")


if __name__ == "__main__":
    asyncio.run(main())
