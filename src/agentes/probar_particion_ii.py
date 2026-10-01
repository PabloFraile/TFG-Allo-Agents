"""
Exploración aislada del factor de Partition.Cyclic necesario para un
objetivo_ii dado de la FFT radix-2, sin pasar por el bucle de 3 agentes
(Generador/Ejecutor/Validador) -- un script de apoyo para responder una
pregunta concreta de forma rápida y barata, no un reemplazo del pipeline
real del TFG.

Con el KERNEL ya verificado (kernel_verificado.txt, sin tocar) y variando
solo el factor de Partition.Cyclic sobre los 4 arrays de la mariposa
(twiddle_real, twiddle_imag, y_real, y_imag), un factor mayor de partición
da más puertos de acceso concurrente y permite bajar el II sin tocar el
pipeline. Sin partición, el acceso por defecto a BRAM de doble puerto
limita el II real con independencia de lo que se pida en s.pipeline().

Este script no llama al SDK de Claude en ningún momento -- no depende de
la red salvo la propia invocación de vitis_hls (que es local). Reutiliza
las mismas funciones de allo_tools.py (_extraer_bloques,
_cargar_kernel_desde_disco, _construir_schedule, _parsear_reporte_csynth)
que usa el Ejecutor real en producción, para que el resultado sea
directamente comparable/reutilizable en el catálogo.

Timeout por intento deliberadamente corto (ver TIMEOUT_INTENTO_SEGUNDOS
abajo): un schedule que va a converger lo hace en minutos, no en horas --
un intento que no ha terminado en 20 min es casi con toda seguridad un
diseño que nunca va a converger, no uno "a punto de cerrar".

Uso:
    source ~/tools/Vitis_HLS/2023.1/settings64.sh   # necesario, vitis_hls en PATH
    cd ~/TFG/src/agentes
    python3 -u probar_particion_ii.py

Cada intento se sintetiza en su propio directorio temporal (no toca
test_l4.prj/ ni el proyecto de ninguna corrida del orquestador). Los
resultados se van guardando incrementalmente en RUTA_RESULTADOS según se
completa cada factor, y también se imprimen por stdout sin buffer.
"""

import json
import subprocess
import sys
import tempfile
import time
from pathlib import Path

# Reutiliza exactamente la misma lógica que usa el Ejecutor real en
# producción (allo_tools.py), para que el resultado sea comparable y no
# haya dos implementaciones del mismo parseo de informe divergiendo con
# el tiempo.
from allo_tools import (
    NOMBRE_PROYECTO_VITIS,
    _construir_schedule,
    _cargar_kernel_desde_disco,
    _extraer_bloques,
    _parsear_reporte_csynth,
    _vitis_hls_disponible,
)

RUTA_KERNEL_VERIFICADO = "kernel_verificado.txt"
# Nombrado por objetivo_ii (no "resultados_particion_ii.json" a secas) para
# no pisar el resultado de una pasada anterior con otro objetivo_ii si
# hiciera falta volver a consultarlo.
RUTA_RESULTADOS = "resultados_particion_ii_ii5.json"

# Deliberadamente corto -- ver docstring del módulo. Si un factor concreto
# parece prometedor pero se queda corto de tiempo, subir esto solo para
# ese factor en una segunda pasada dirigida, no por defecto para todos.
TIMEOUT_INTENTO_SEGUNDOS = 1200  # 20 min

OBJETIVO_II = 5  # punto actual del barrido de objetivo_ii, ver specs/spec_example.yaml

# Factores de Partition.Cyclic a probar sobre los 4 arrays de la mariposa.
# 4 se incluye como control: es el factor que ya convergió para objetivos
# menos agresivos -- si este script no lo reproduce al menos igual de bien,
# algo en el harness (no en Allo/Vitis) está mal.
FACTORES_A_PROBAR = [4, 8, 16]


def _construir_texto_schedule(factor: int, ii_objetivo: int) -> str:
    """Genera el bloque SCHEDULE variando solo el factor de partición:
    Partition.Cyclic sobre los 4 arrays de la mariposa + pipeline
    individual del bucle dominante de cada una de las 10 etapas, todas con
    el mismo initiation_interval."""
    lineas_pipeline_etapas = "\n".join(
        f's.pipeline("{nombre}", initiation_interval={ii_objetivo})'
        for nombre in ["g1", "g2", "g3", "g4", "g5", "j6", "j7", "j8", "j9", "j10"]
    )
    return f"""from allo.customize import Partition

s = allo.customize(kernel)

s.partition("kernel:twiddle_real", partition_type=Partition.Cyclic, factor={factor})
s.partition("kernel:twiddle_imag", partition_type=Partition.Cyclic, factor={factor})
s.partition("kernel:y_real", partition_type=Partition.Cyclic, factor={factor})
s.partition("kernel:y_imag", partition_type=Partition.Cyclic, factor={factor})

s.pipeline("k", initiation_interval={ii_objetivo})
s.pipeline("i", initiation_interval={ii_objetivo})
{lineas_pipeline_etapas}
"""


def probar_un_factor(kernel_src: str, factor: int, ii_objetivo: int) -> dict:
    schedule_src = _construir_texto_schedule(factor, ii_objetivo)
    inicio = time.time()

    resultado_base = {
        "factor_particion": factor,
        "objetivo_ii": ii_objetivo,
        "schedule_probado": schedule_src,
    }

    try:
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
        s = _construir_schedule(kernel_fn, schedule_src)
        directorio_proyecto = Path(tempfile.mkdtemp(prefix=f"allo_l4_factor{factor}_"))
        s.build(target="vivado_hls", mode="csyn", project=str(directorio_proyecto))
    except Exception as e:  # noqa: BLE001 -- exploración aislada, capturar todo y seguir con el siguiente factor
        resultado_base.update(ok=False, error=f"{type(e).__name__}: {e}", segundos=time.time() - inicio)
        return resultado_base

    run_tcl = directorio_proyecto / "run.tcl"
    if not run_tcl.exists():
        resultado_base.update(ok=False, error=f"s.build() no generó run.tcl en {directorio_proyecto}",
                               segundos=time.time() - inicio)
        return resultado_base

    try:
        resultado = subprocess.run(
            ["vitis_hls", "-f", "run.tcl"],
            cwd=directorio_proyecto,
            capture_output=True,
            text=True,
            timeout=TIMEOUT_INTENTO_SEGUNDOS,
        )
    except subprocess.TimeoutExpired:
        resultado_base.update(ok=False, error=f"Síntesis excedió el timeout de {TIMEOUT_INTENTO_SEGUNDOS}s "
                                               f"(20 min) -- diseño probablemente no convergente para este factor",
                               segundos=time.time() - inicio)
        return resultado_base

    if resultado.returncode != 0:
        resultado_base.update(
            ok=False,
            error=f"vitis_hls devolvió código {resultado.returncode}:\n"
                  f"{resultado.stdout[-1500:]}\n{resultado.stderr[-1500:]}",
            segundos=time.time() - inicio,
        )
        return resultado_base

    ruta_xml = directorio_proyecto / NOMBRE_PROYECTO_VITIS / "solution1" / "syn" / "report" / "kernel_csynth.xml"
    if not ruta_xml.exists():
        resultado_base.update(ok=False, error=f"vitis_hls terminó (código 0) pero no se encontró {ruta_xml}",
                               segundos=time.time() - inicio)
        return resultado_base

    metricas = _parsear_reporte_csynth(ruta_xml)
    resultado_base.update(ok=True, metricas=metricas, segundos=time.time() - inicio,
                           proyecto_dir=str(directorio_proyecto))
    return resultado_base


def main():
    if not _vitis_hls_disponible():
        print("ERROR: vitis_hls no está en el PATH. ¿Has hecho 'source "
              "~/tools/Vitis_HLS/2023.1/settings64.sh' en esta terminal?")
        sys.exit(1)

    with open(RUTA_KERNEL_VERIFICADO) as f:
        kernel_src = f.read()
    print(f"Kernel cargado desde '{RUTA_KERNEL_VERIFICADO}' ({len(kernel_src)} caracteres). "
          f"Sin tocar -- solo se varía el factor de partición del schedule.\n")

    resultados = []
    for factor in FACTORES_A_PROBAR:
        print(f"=== Probando Partition.Cyclic(factor={factor}), objetivo_ii={OBJETIVO_II}, "
              f"timeout={TIMEOUT_INTENTO_SEGUNDOS}s ===")
        r = probar_un_factor(kernel_src, factor, OBJETIVO_II)
        resultados.append(r)

        if r["ok"]:
            m = r["metricas"]
            print(f"  -> OK en {r['segundos']:.0f}s: II={m['II']}, "
                  f"latencia={m['latencia_peor_caso']}, "
                  f"reloj={m['periodo_reloj_estimado_ns']}ns, "
                  f"BRAM={m['BRAM']} DSP={m['DSP']} LUT={m['LUT']} FF={m['FF']}")
        else:
            print(f"  -> FALLO en {r['segundos']:.0f}s: {r['error'][:300]}")

        with open(RUTA_RESULTADOS, "w") as f:
            json.dump(resultados, f, indent=2, ensure_ascii=False)
        print(f"  (resultados parciales guardados en {RUTA_RESULTADOS})\n")

    print("=== Resumen ===")
    for r in resultados:
        if r["ok"]:
            print(f"factor={r['factor_particion']:>3}: II={r['metricas']['II']} "
                  f"({r['segundos']:.0f}s)")
        else:
            print(f"factor={r['factor_particion']:>3}: FALLO ({r['segundos']:.0f}s) -- {r['error'][:120]}")


if __name__ == "__main__":
    main()
