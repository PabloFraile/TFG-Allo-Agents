"""
Baseline VHDL del TFG: Claude escribe VHDL directamente, sin agentes, en un
solo intento (pass@1). Es lo que haría alguien pidiéndole el bloque a Claude
sin más: no hay lazo de corrección, ni Validador, ni cascada L1-L4.

Mismas condiciones que el baseline C++ (generar_baseline.py) y que el
pipeline: misma spec, mismo modelo y opciones del SDK, mismo vector y misma
tolerancia funcional, mismo part y mismo reloj. Lo único que cambia es el
lenguaje y, con él, la herramienta:

  - compilación + simulación: GHDL (VHDL-2008), testbench generado por el arnés
  - síntesis: Vivado, synth_design fuera de contexto

En RTL no existe el II, así que se elimina restricciones.objetivo_ii de la
spec que recibe el modelo (no significa nada para él) y se conserva
throughput_min. El rendimiento se mide como latencia en ciclos (simulación)
x periodo estimado (síntesis), igual que t_FFT en la comparativa.

Uso (desde TFG/baseline, con el entorno de Vivado cargado):
  source <ruta_Vivado_2023.1>/settings64.sh
  python3 -u generar_baseline_vhdl.py --runs 20

Es reanudable: los runs con resultado.json se saltan. Si el SDK falla (cuota,
issue #1031) el script se para sin registrar el run como fallo del modelo.
"""

import argparse
import asyncio
import copy
import json
import re
import shutil
import sys
import time
from datetime import datetime
from pathlib import Path

import arnes
import arnes_vhdl
from comun import (
    DIR_RESULTADOS_BASELINE, PART_POR_DEFECTO, PERIODO_RELOJ_NS_POR_DEFECTO, SPEC_POR_DEFECTO,
    TIMEOUT_VITIS_POR_DEFECTO, TOLERANCIA_POR_DEFECTO,
)
import yaml


class ErrorInfraestructura(Exception):
    """Fallo del SDK / cuota: no es culpa del modelo, no se registra el run."""


# Mismo tono que el baseline C++: "usuario competente", sin pistas de diseño
# (arquitectura, pipeline, uso de DSP/BRAM...). Lo único que se fija es lo que
# exige el flujo: VHDL-2008 sintetizable sin IP de Vivado, porque este flujo no
# genera IP (equivale a "usa la firma que se te da" en C++).
SYSTEM_PROMPT = """\
Eres un ingeniero experto en diseño digital RTL en VHDL para FPGA AMD/Xilinx
UltraScale+ con Vivado 2023.1. Escribes VHDL-2008 sintetizable, correcto y
optimizado.

Reglas de entrega:
- Devuelve UN ÚNICO bloque de código ```vhdl con el archivo kernel.vhd completo
  (todas las entidades, arquitecturas y paquetes propios que necesites).
- La entidad top debe tener EXACTAMENTE el nombre y los puertos que se te indican.
- Solo bibliotecas estándar IEEE (std_logic_1164, numeric_std, math_real,
  fixed_pkg, float_pkg...). No uses IP de Vivado ni primitivas del fabricante:
  el flujo no las genera.
- No incluyas testbench: el testbench ya existe.
- No expliques nada fuera del bloque de código.
"""


def spec_para_rtl(spec: dict) -> dict:
    s = copy.deepcopy(spec)
    s.get("restricciones", {}).pop("objetivo_ii", None)
    return s


def construir_prompt(spec: dict, part: str, periodo_ns: float) -> str:
    partes = [
        f"Especificación del bloque:\n{json.dumps(spec_para_rtl(spec), indent=2, ensure_ascii=False)}",
        "Entidad obligatoria (precedida de library ieee; use ieee.std_logic_1164.all; "
        f"use ieee.numeric_std.all;):\n{arnes_vhdl.entidad_vhdl(spec)}",
        arnes_vhdl.protocolo_interfaz(spec),
        f"Objetivo de síntesis: dispositivo {part}, periodo de reloj {periodo_ns} ns.",
    ]
    return "\n\n".join(partes)


def extraer_codigo(texto: str) -> str | None:
    bloques = re.findall(r"```(?:vhdl|vhd)?[ \t]*\n(.*?)```", texto, re.DOTALL | re.IGNORECASE)
    if not bloques:
        return None
    return max(bloques, key=len).strip() + "\n"


async def llamar_claude(prompt: str, modelo: str | None) -> dict:
    from claude_agent_sdk import AssistantMessage, ClaudeAgentOptions, ResultMessage, TextBlock, query

    opciones = ClaudeAgentOptions(system_prompt=SYSTEM_PROMPT, allowed_tools=[], permission_mode="dontAsk",
                                  **({"model": modelo} if modelo else {}))
    texto, uso = "", {}
    t0 = time.monotonic()
    try:
        async for msg in query(prompt=prompt, options=opciones):
            if isinstance(msg, AssistantMessage):
                for bloque in msg.content:
                    if isinstance(bloque, TextBlock):
                        texto += bloque.text
            elif isinstance(msg, ResultMessage):
                uso = {"duracion_ms": getattr(msg, "duration_ms", None), "usage": getattr(msg, "usage", None),
                       "total_cost_usd": getattr(msg, "total_cost_usd", None), "is_error": getattr(msg, "is_error", None)}
                if uso["is_error"]:
                    raise ErrorInfraestructura(f"ResultMessage con is_error=True: {getattr(msg, 'result', '')}")
    except ErrorInfraestructura:
        raise
    except Exception as e:  # noqa: BLE001 -- issue #1031 y similares
        raise ErrorInfraestructura(f"{type(e).__name__}: {e}") from e
    if not texto.strip():
        raise ErrorInfraestructura("Respuesta vacía del SDK (¿cuota agotada?)")
    return {"texto": texto, "uso": uso, "t_generacion_s": round(time.monotonic() - t0, 1)}


def validar_codigo(dir_intento: Path, codigo: str, spec: dict, vector: dict, args) -> dict:
    """Escribe archivos, simula y sintetiza. Separado de la llamada al modelo
    para poder probar el arnés con un kernel.vhd escrito a mano."""
    (dir_intento / "kernel.vhd").write_text(codigo)
    arnes_vhdl.escribir_vectores(spec, vector, dir_intento / "vectores_in.txt")
    arnes_vhdl.escribir_testbench(spec, dir_intento / "tb.vhd", args.max_ciclos)

    print(f"      GHDL (análisis + simulación, timeout {args.timeout_sim}s)...", flush=True)
    sim = arnes_vhdl.simular(dir_intento, args.timeout_sim)
    syn = None
    if not args.sin_sintesis and sim["analiza_kernel"]:
        arnes_vhdl.escribir_synth_tcl(spec, args.part, args.periodo_reloj, dir_intento / "synth.tcl")
        print(f"      Vivado (synth_design, timeout {args.timeout_sintesis}s)...", flush=True)
        syn = arnes_vhdl.sintetizar(dir_intento, args.timeout_sintesis)
    registro = arnes_vhdl.analizar(spec, dir_intento, sim, syn, vector["salidas"], args.tolerancia, args.periodo_reloj)
    # Se conservan kernel.vhd, tb.vhd, vectores_in.txt, salida.txt, logs e informes.
    for basura in ("ghdl_work", ".Xil"):
        shutil.rmtree(dir_intento / basura, ignore_errors=True)
    for f in ("tb", "e~tb.o", "utilizacion.rpt", "timing.rpt"):
        (dir_intento / f).unlink(missing_ok=True)
    return registro


async def ejecutar_run(dir_run: Path, spec: dict, vector: dict, args) -> dict:
    t0 = time.monotonic()
    dir_intento = dir_run / "intento_01"
    dir_intento.mkdir(parents=True, exist_ok=True)
    prompt = construir_prompt(spec, args.part, args.periodo_reloj)
    (dir_intento / "prompt.txt").write_text(prompt)

    gen = await llamar_claude(prompt, args.modelo)
    (dir_intento / "respuesta.txt").write_text(gen["texto"])
    codigo = extraer_codigo(gen["texto"])
    registro = {"t_generacion_s": gen["t_generacion_s"], "uso_sdk": gen["uso"], "codigo_extraido": codigo is not None}
    if codigo is None:
        registro.update({"etapa_fallo": "sin_codigo", "exito": False, "exito_estricto": False,
                         "funcional_ok": False, "sintesis_ok": False, "metricas": {}})
    else:
        registro.update(validar_codigo(dir_intento, codigo, spec, vector, args))
    return {"bloque": spec["bloque"], "lenguaje": "vhdl", "modo": "oneshot", "exito": registro["exito"],
            "n_intentos": 1, "t_total_s": round(time.monotonic() - t0, 1), "final": registro}


def parsear_args(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--spec", type=Path, default=SPEC_POR_DEFECTO)
    p.add_argument("--runs", type=int, default=20, help="Runs independientes (el LLM no es determinista)")
    p.add_argument("--tolerancia", type=float, default=TOLERANCIA_POR_DEFECTO)
    p.add_argument("--part", default=PART_POR_DEFECTO)
    p.add_argument("--periodo-reloj", type=float, default=PERIODO_RELOJ_NS_POR_DEFECTO)
    p.add_argument("--timeout-sim", type=int, default=arnes_vhdl.TIMEOUT_SIM_POR_DEFECTO)
    p.add_argument("--timeout-sintesis", type=int, default=TIMEOUT_VITIS_POR_DEFECTO)
    p.add_argument("--max-ciclos", type=int, default=arnes_vhdl.MAX_CICLOS_POR_DEFECTO)
    p.add_argument("--sin-sintesis", action="store_true", help="Solo GHDL (si Vivado no está instalado)")
    p.add_argument("--modelo", default=None, help="Por defecto el mismo que usa el pipeline (el del SDK)")
    p.add_argument("--salida", type=Path, default=DIR_RESULTADOS_BASELINE)
    p.add_argument("--probar-kernel", type=Path, default=None,
                   help="No llama al modelo: valida un kernel.vhd escrito a mano (para comprobar el arnés)")
    return p.parse_args(argv)


async def main():
    args = parsear_args()
    if not arnes_vhdl.ghdl_disponible():
        sys.exit("ghdl no está en el PATH. Instálalo con: sudo apt install ghdl")
    if not args.sin_sintesis and not arnes_vhdl.vivado_disponible():
        sys.exit("vivado no está en el PATH. Carga su entorno (source <Vivado>/settings64.sh) "
                 "o usa --sin-sintesis para medir solo corrección y latencia.")

    with open(args.spec) as f:
        spec = yaml.safe_load(f)
    vector = arnes.generar_vectores(spec, 1)[0]  # vector 0 = exactamente el de L2

    if args.probar_kernel:
        d = Path("prueba_arnes_vhdl")
        shutil.rmtree(d, ignore_errors=True)
        d.mkdir()
        r = validar_codigo(d, args.probar_kernel.read_text(), spec, vector, args)
        print(json.dumps(r, indent=2, ensure_ascii=False))
        return

    dir_config = args.salida / spec["bloque"] / "vhdl_oneshot"
    dir_config.mkdir(parents=True, exist_ok=True)
    (dir_config / "config.json").write_text(json.dumps({
        "spec_ruta": str(args.spec), "spec_enviada": spec_para_rtl(spec), "tolerancia": args.tolerancia,
        "part": args.part, "periodo_reloj_ns": args.periodo_reloj, "timeout_sim_s": args.timeout_sim,
        "timeout_sintesis_s": args.timeout_sintesis, "max_ciclos": args.max_ciclos, "sin_sintesis": args.sin_sintesis,
        "modelo": args.modelo or "(por defecto del SDK)", "system_prompt": SYSTEM_PROMPT,
    }, indent=2, ensure_ascii=False))

    print(f"Baseline VHDL {spec['bloque']} | oneshot | runs={args.runs}")
    print(f"Resultados en {dir_config}")
    for k in range(1, args.runs + 1):
        dir_run = dir_config / f"run_{k:02d}"
        if (dir_run / "resultado.json").exists():
            print(f"  run {k:02d}: ya hecho, se salta")
            continue
        if dir_run.exists():
            shutil.rmtree(dir_run)
        print(f"  run {k:02d} ({datetime.now():%H:%M:%S})", flush=True)
        try:
            resultado = await ejecutar_run(dir_run, spec, vector, args)
        except ErrorInfraestructura as e:
            if dir_run.exists():
                destino = dir_run.with_name(f"{dir_run.name}_descartado_{datetime.now():%Y%m%d_%H%M%S}")
                dir_run.rename(destino)
            print(f"\n[!] Fallo de infraestructura (no del modelo): {e}\n"
                  f"    El run {k:02d} NO se ha registrado. Relanza el mismo comando para reanudar.")
            sys.exit(2)
        resultado["fecha"] = datetime.now().isoformat(timespec="seconds")
        (dir_run / "resultado.json").write_text(json.dumps(resultado, indent=2, ensure_ascii=False))
        f = resultado["final"]
        m = f.get("metricas") or {}
        print(f"  run {k:02d}: {'ÉXITO' if resultado['exito'] else 'fallo'} etapa={f['etapa_fallo']} "
              f"lat={m.get('latencia_ciclos')} t_fft={m.get('t_fft_us')}us LUT={m.get('LUT')} ({resultado['t_total_s']}s)")
    print("\nHecho. Resumen: python3 resumir_vhdl.py")


if __name__ == "__main__":
    asyncio.run(main())
