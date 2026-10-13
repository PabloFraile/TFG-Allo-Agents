"""
Arnés de validación del baseline: lo que sustituye a L1-L4 cuando el código
no es Allo sino HLS C++ escrito directamente por Claude.

  - L1+L2 (compila y es funcionalmente correcto) -> C simulation (csim) de
    Vitis HLS con un testbench generado AQUÍ (no por Claude) que compara
    contra el mismo golden model, los mismos vectores y la misma tolerancia
    que L2 del pipeline.
  - L3 (equivalencia formal del schedule) -> no existe equivalente en HLS
    C++. Es una diferencia cualitativa y se documenta como tal.
  - L4 (síntesis) -> csynth_design con el mismo part, reloj y flow_target que
    el run.tcl que genera Allo, y el mismo criterio de II (máximo PipelineII
    entre el informe top y los de los submódulos).

csim y csynth se ejecutan siempre los dos (cada uno dentro de un `catch`),
aunque falle el primero: así se puede medir cuántas veces el código
sintetiza aunque sea funcionalmente incorrecto.
"""

import os
import re
import shutil
import signal
import subprocess
import time
import xml.etree.ElementTree as ET
from pathlib import Path

import numpy as np

from comun import dims_cpp, firma_cpp, importar_golden_models, nombre_top, tipo_cpp, tipo_numpy

MARCA_RESULTADO = "BASELINE_RESULT"
MARCA_VECTOR = "BASELINE_VEC"
MARCA_CSIM_ERROR = "BASELINE_CSIM_ERROR"
MARCA_CSIM_FIN = "BASELINE_CSIM_DONE"
MARCA_CSYNTH_ERROR = "BASELINE_CSYNTH_ERROR"
MARCA_CSYNTH_FIN = "BASELINE_CSYNTH_DONE"

# Vitis HLS 2023.1 trae su propio ld (binutils 2.37), que no sabe leer la
# libm de glibc >= 2.38 (Ubuntu 24.04: sección .relr.dyn) y hace que TODA
# csim falle al enlazar, sea cual sea el código. -B/usr/bin/ hace que el gcc
# de Vitis use el ld del sistema. Solo afecta a csim, no a csynth.
CSIM_LDFLAGS = "-B/usr/bin/"

# Firmas de fallos de csim que son del entorno, no del código generado.
# Si aparecen, el run no se puede atribuir al modelo.
FIRMAS_FALLO_ENTORNO_CSIM = [
    "unknown type [0x13] section",
    "skipping incompatible /lib",
    "cannot find /lib/x86_64-linux-gnu/",
]


# ---------------------------------------------------------------------------
# Vectores de test + golden model
# ---------------------------------------------------------------------------

def generar_vectores(spec: dict, n_vectores: int) -> list[dict]:
    """Devuelve [{'entradas': {nombre: array}, 'salidas': {nombre: array}}].

    El vector 0 es EXACTAMENTE el que usa L2 (generar_vectores_test con
    seed=0); los adicionales usan seed=1, 2, ...
    """
    gm = importar_golden_models()
    golden_id = spec["golden_model_id"]
    if golden_id not in gm.GOLDEN_MODELS:
        raise KeyError(f"golden_model_id '{golden_id}' no está en golden_models.GOLDEN_MODELS")
    golden = gm.GOLDEN_MODELS[golden_id]

    entradas_spec = spec["entradas"]
    formas = [tuple(p["forma"]) for p in entradas_spec]
    usar_generador_l2 = (
        len(entradas_spec) == 2
        and len(set(formas)) == 1
        and all(tipo_numpy(p) == "float32" for p in entradas_spec)
    )

    vectores = []
    for seed in range(n_vectores):
        if usar_generador_l2:
            arrays = gm.generar_vectores_test(forma=formas[0], seed=seed)
        else:
            rng = np.random.default_rng(seed)
            arrays = [rng.standard_normal(f).astype(tipo_numpy(p)) for p, f in zip(entradas_spec, formas)]
        entradas = {p["nombre"]: np.asarray(a) for p, a in zip(entradas_spec, arrays)}
        ref = golden(*[entradas[p["nombre"]] for p in entradas_spec])
        if not isinstance(ref, (tuple, list)):
            ref = (ref,)
        salidas = {p["nombre"]: np.asarray(r, dtype=tipo_numpy(p)) for p, r in zip(spec["salidas"], ref)}
        vectores.append({"entradas": entradas, "salidas": salidas})
    return vectores


def _array_c(nombre: str, ctype: str, datos: list[np.ndarray]) -> str:
    n = datos[0].size
    filas = []
    for d in datos:
        valores = ", ".join(f"{float(v):.9g}" if "float" in str(d.dtype) else str(int(v)) for v in d.ravel())
        filas.append("  {" + valores + "}")
    return f"static const {ctype} {nombre}[N_VEC][{n}] = {{\n" + ",\n".join(filas) + "\n};\n"


def escribir_vectores_h(spec: dict, vectores: list[dict], ruta: Path) -> None:
    partes = ["// Generado por baseline/arnes.py -- NO editar a mano.\n#pragma once\n",
              f"#define N_VEC {len(vectores)}\n"]
    for p in spec["entradas"]:
        partes.append(_array_c(f"VEC_IN_{p['nombre']}", tipo_cpp(p), [v["entradas"][p["nombre"]] for v in vectores]))
    for p in spec["salidas"]:
        partes.append(_array_c(f"VEC_REF_{p['nombre']}", tipo_cpp(p), [v["salidas"][p["nombre"]] for v in vectores]))
    ruta.write_text("\n".join(partes))


def escribir_testbench(spec: dict, tolerancia: float, ruta: Path) -> None:
    """Testbench fijo (no lo escribe Claude). Criterio idéntico a L2:
    |y - ref| < tol en todos los elementos de todas las salidas."""
    top = nombre_top(spec)
    decl_locales, copias, comparaciones = [], [], []
    for p in spec["entradas"]:
        n = p["nombre"]
        decl_locales.append(f"    static {tipo_cpp(p)} {n}{dims_cpp(p)};")
        copias.append(f"    std::memcpy({n}, VEC_IN_{n}[v], sizeof({n}));")
    for p in spec["salidas"]:
        n = p["nombre"]
        decl_locales.append(f"    static {tipo_cpp(p)} {n}{dims_cpp(p)};")
        copias.append(f"    std::memset({n}, 0, sizeof({n}));")
        comparaciones.append(f"""\
    {{
      const {tipo_cpp(p)} *plano = reinterpret_cast<const {tipo_cpp(p)} *>({n});
      const int tam = (int)(sizeof({n}) / sizeof(plano[0]));
      int malos = 0; double max_diff = 0.0;
      for (int i = 0; i < tam; i++) {{
        double d = std::fabs((double)plano[i] - (double)VEC_REF_{n}[v][i]);
        if (!(d < TOL)) {{ malos++; }}            // NaN cuenta como fallo
        if (d > max_diff || d != d) max_diff = d;
      }}
      std::printf("{MARCA_VECTOR} %d salida={n} discrepantes=%d/%d max_abs_diff=%.6g tol=%g\\n",
                  v, malos, tam, max_diff, TOL);
      if (malos) fallos++;
    }}""")
    args = ", ".join(p["nombre"] for p in spec["entradas"] + spec["salidas"])
    codigo = f"""\
// Testbench generado por baseline/arnes.py -- NO lo escribe el LLM.
// Mismo golden model, mismos vectores y misma tolerancia que L2 del pipeline.
#include <cstdio>
#include <cstring>
#include <cmath>
#include "vectores.h"

{firma_cpp(spec)};

static const double TOL = {tolerancia!r};

int main() {{
  int fallos = 0;
  for (int v = 0; v < N_VEC; v++) {{
{chr(10).join(decl_locales)}
{chr(10).join(copias)}
    {top}({args});
{chr(10).join(comparaciones)}
  }}
  std::printf("{MARCA_RESULTADO} %s\\n", fallos ? "FAIL" : "PASS");
  return fallos ? 1 : 0;
}}
"""
    ruta.write_text(codigo)


# ---------------------------------------------------------------------------
# Vitis HLS
# ---------------------------------------------------------------------------

def escribir_run_tcl(spec: dict, part: str, periodo_ns: float, flow_target: str, ruta: Path,
                     csim_ldflags: str = CSIM_LDFLAGS) -> None:
    opt_ld = f" -ldflags {{{csim_ldflags}}}" if csim_ldflags else ""
    tcl = f"""\
# Generado por baseline/arnes.py. Mismo part / reloj / flow_target que el
# run.tcl que genera Allo para L4; csim añadido para validar funcionalmente.
open_project proj -reset
open_solution -reset solution1 -flow_target {flow_target}
set_top {nombre_top(spec)}
add_files kernel.cpp
add_files -tb tb.cpp
add_files -tb vectores.h
set_part {{{part}}}
create_clock -period {periodo_ns}

if {{[catch {{csim_design{opt_ld}}} msg]}} {{
  puts "{MARCA_CSIM_ERROR}: $msg"
}} else {{
  puts "{MARCA_CSIM_FIN}"
}}

if {{[catch {{csynth_design}} msg]}} {{
  puts "{MARCA_CSYNTH_ERROR}: $msg"
}} else {{
  puts "{MARCA_CSYNTH_FIN}"
}}

exit
"""
    ruta.write_text(tcl)


def vitis_hls_disponible() -> bool:
    return shutil.which("vitis_hls") is not None


def ejecutar_vitis(directorio: Path, timeout_s: int) -> dict:
    """Lanza `vitis_hls -f run.tcl` en `directorio`. Mata el grupo de procesos
    entero si se pasa del timeout (vitis_hls lanza hijos que si no quedan
    huérfanos consumiendo CPU)."""
    ruta_log = directorio / "vitis.log"
    t0 = time.monotonic()
    timeout = False
    with open(ruta_log, "w") as log:
        proc = subprocess.Popen(
            ["vitis_hls", "-f", "run.tcl"],
            cwd=directorio, stdout=log, stderr=subprocess.STDOUT, start_new_session=True,
        )
        try:
            proc.wait(timeout=timeout_s)
        except subprocess.TimeoutExpired:
            timeout = True
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait()
    return {
        "timeout": timeout,
        "codigo_salida": proc.returncode,
        "duracion_s": round(time.monotonic() - t0, 1),
        "log": ruta_log.read_text(errors="replace"),
    }


def parsear_informe_csynth(dir_report: Path, top: str) -> dict | None:
    """Mismo criterio que allo_tools._parsear_reporte_csynth: II = máximo
    PipelineII entre el informe top y los de todos los submódulos.
    Además guarda el intervalo del top (útil si Claude usa DATAFLOW o no
    pipelinea ningún bucle, casos en que no hay PipelineII)."""
    ruta_top = dir_report / f"{top}_csynth.xml"
    if not ruta_top.exists():
        return None
    root = ET.parse(ruta_top).getroot()

    def texto(path):
        el = root.find(path)
        return el.text if el is not None else None

    iis = []
    for ruta in sorted(dir_report.glob("*_csynth.xml")):
        try:
            r = ET.parse(ruta).getroot()
        except ET.ParseError:
            continue
        iis += [int(el.text) for el in r.findall(".//SummaryOfLoopLatency//PipelineII")
                if el.text is not None and el.text.strip().lstrip("-").isdigit()]

    return {
        "II": max(iis) if iis else None,
        "latencia_peor_caso": texto(".//SummaryOfOverallLatency/Worst-caseLatency"),
        "periodo_reloj_estimado_ns": texto(".//SummaryOfTimingAnalysis/EstimatedClockPeriod"),
        "BRAM": texto(".//AreaEstimates/Resources/BRAM_18K"),
        "DSP": texto(".//AreaEstimates/Resources/DSP"),
        "LUT": texto(".//AreaEstimates/Resources/LUT"),
        "FF": texto(".//AreaEstimates/Resources/FF"),
        "intervalo_top": texto(".//SummaryOfOverallLatency/Interval-max"),
        "n_bucles_pipelineados": len(iis),
    }


def analizar_ejecucion(ejec: dict, directorio: Path, spec: dict, objetivo_ii: int,
                       periodo_objetivo_ns: float | None = None) -> dict:
    """Traduce log + informes en el registro de un intento."""
    log = ejec["log"]
    top = nombre_top(spec)
    dir_report = directorio / "proj" / "solution1" / "syn" / "report"

    lineas_vec = [l.strip() for l in log.splitlines() if l.strip().startswith(MARCA_VECTOR)]
    resultado_tb = re.search(rf"{MARCA_RESULTADO} (PASS|FAIL)", log)
    csim_ejecuto_tb = resultado_tb is not None
    csim_ok = bool(resultado_tb and resultado_tb.group(1) == "PASS" and MARCA_CSIM_FIN in log)

    # Si el testbench no llegó a ejecutarse, csim falló al compilar/enlazar.
    # Un 'undefined reference' al top = firma distinta de la pedida.
    interfaz_ok = not re.search(rf"undefined reference to [`']{re.escape(top)}", log)

    metricas = parsear_informe_csynth(dir_report, top)
    sintesis_ok = bool(metricas) and MARCA_CSYNTH_FIN in log and not ejec["timeout"]
    cumple_ii = bool(sintesis_ok and metricas["II"] is not None and metricas["II"] <= objetivo_ii)
    fallo_entorno_csim = [f for f in FIRMAS_FALLO_ENTORNO_CSIM if f in log]
    # No entra en 'exito' (tampoco lo comprueba L4), pero se registra: con un
    # reloj estimado peor que el objetivo, el II en ciclos no cuenta toda la
    # historia del throughput real.
    reloj = None
    try:
        reloj = float(metricas["periodo_reloj_estimado_ns"]) if metricas else None
    except (TypeError, ValueError):
        pass
    cumple_reloj = None if (reloj is None or periodo_objetivo_ns is None) else reloj <= periodo_objetivo_ns

    if not csim_ejecuto_tb and fallo_entorno_csim:
        etapa_fallo = "entorno_csim"
    elif not csim_ejecuto_tb:
        etapa_fallo = "interfaz" if not interfaz_ok else "compilacion"
    elif not csim_ok:
        etapa_fallo = "funcional"
    elif ejec["timeout"]:
        etapa_fallo = "timeout_sintesis"
    elif not sintesis_ok:
        etapa_fallo = "sintesis"
    elif not cumple_ii:
        etapa_fallo = "ii"
    else:
        etapa_fallo = None

    # Copia los informes (pequeños) junto al intento antes de borrar el proyecto.
    if dir_report.exists():
        destino = directorio / "informes_csynth"
        destino.mkdir(exist_ok=True)
        for f in dir_report.glob("*_csynth.*"):
            shutil.copy2(f, destino / f.name)

    return {
        "csim_compila": csim_ejecuto_tb,
        "interfaz_ok": interfaz_ok,
        "csim_ok": csim_ok,
        "csim_detalle": lineas_vec,
        "sintesis_ok": sintesis_ok,
        "timeout_sintesis": ejec["timeout"],
        "t_vitis_s": ejec["duracion_s"],
        "metricas_hls": metricas,
        "cumple_ii": cumple_ii,
        "cumple_reloj_estimado": cumple_reloj,
        "fallo_entorno_csim": fallo_entorno_csim,
        "exito": csim_ok and cumple_ii,
        "etapa_fallo": etapa_fallo,
    }


def run_contaminado_por_entorno(dir_run: Path) -> bool:
    """True si algún intento del run falló la csim por el entorno (p. ej. runs
    hechos antes de añadir CSIM_LDFLAGS). Esos runs no son atribuibles al
    modelo y hay que repetirlos."""
    for log in dir_run.glob("intento_*/vitis.log"):
        texto = log.read_text(errors="replace")
        if MARCA_RESULTADO not in texto and any(f in texto for f in FIRMAS_FALLO_ENTORNO_CSIM):
            return True
    return False


def resumen_errores_para_feedback(analisis: dict, log: str, objetivo_ii: int, max_lineas: int = 40) -> str:
    """Mensaje que se le devuelve a Claude en modo feedback: solo lo que
    vería un usuario en la salida de Vitis, sin interpretación (no hay
    Validador)."""
    partes = []
    if not analisis["csim_compila"]:
        errores, vistos = [], set()
        for l in log.splitlines():
            ls = l.strip()
            if re.search(r"error", ls, re.IGNORECASE) and not ls.startswith("BASELINE_") and ls not in vistos:
                vistos.add(ls)
                errores.append(ls)
        partes.append("La C simulation no compiló/enlazó. Errores de Vitis HLS:\n" + "\n".join(errores[:max_lineas]))
    elif not analisis["csim_ok"]:
        partes.append("La C simulation compiló pero el resultado NO coincide con la referencia:\n"
                      + "\n".join(analisis["csim_detalle"]))
    if analisis["timeout_sintesis"]:
        partes.append("La síntesis (csynth_design) no terminó dentro del tiempo límite.")
    elif not analisis["sintesis_ok"]:
        errores = list(dict.fromkeys(l.strip() for l in log.splitlines() if "ERROR" in l))
        partes.append("La síntesis falló:\n" + "\n".join(errores[:max_lineas]))
    elif not analisis["cumple_ii"]:
        m = analisis["metricas_hls"]
        partes.append(f"La síntesis terminó pero el peor II de los bucles pipelineados es {m['II']} "
                      f"(objetivo: II <= {objetivo_ii}). Métricas: {m}")
    return "\n\n".join(partes)
