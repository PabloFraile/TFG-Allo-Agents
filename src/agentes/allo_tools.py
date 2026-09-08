"""
Herramientas del agente EJECUTOR.

Cada función de aquí abajo es una herramienta que el agente Ejecutor puede
llamar.

Estado actual:
  - run_l1_parse_types  -> CONECTADO A ALLO REAL (allo.customize())
  - run_l2_functional   -> CONECTADO A ALLO REAL (s.build(target='llvm') +
                            comparación contra golden model real)
  - run_l3_equivalence  -> CONECTADO A ALLO REAL (allo.verify(s, s_orig)).
                            Contrato confirmado con `help(allo.verify)` en el
                            entorno instalado: devuelve bool, y Allo mismo
                            escribe un diff del código generado si falla --
                            ese diagnóstico (PAST) sale por stdout durante
                            la llamada, y el wrapper lo captura y lo mete en
                            salida_cruda para que el Validador tenga contexto
                            real del mismatch, no solo un ok=False.
                            OJO (6 de agosto de 2026): ante un error fatal de
                            parseo interno, PAST puede abortar con SystemExit
                            en vez de una excepción Python normal -- ver
                            ERRORES_CAPTURABLES más abajo y el manejo
                            especial de SystemExit dentro de esta función.
  - run_l4_hls          -> CONECTADO A VITIS HLS REAL (síntesis csyn).
                            OJO (12 de agosto de 2026, ver docs/bitacora.md
                            y docs/SETUP_VITIS.md): NO se usa mod() tal cual
                            lo genera s.build(target="vivado_hls", ...) --
                            ese Makefile invoca un binario llamado
                            'vivado_hls', discontinuado por Xilinx desde
                            Vitis 2020.2+ (ahora se llama 'vitis_hls', con
                            una estructura interna distinta). En vez de eso,
                            se deja que s.build() genere el proyecto HLS en
                            disco (que NO requiere vitis_hls todavía) y
                            luego se lanza `vitis_hls -f run.tcl` nosotros
                            mismos con subprocess, saltándonos el Makefile
                            roto. Confirmado empíricamente contra una
                            síntesis real (kernel trivial de suma de
                            vectores) en Vitis HLS 2023.1.

Para las que siguen mockeadas: sustituye el cuerpo de cada función `MOCK_*`
por la llamada real (se indica con un comentario "# TODO: reemplazar por").
La firma (nombre, descripción, parámetros) puede quedarse igual.
"""

import json
import re
import os
import shutil
import subprocess
import tempfile
import traceback
import uuid
import importlib.util
import io
import contextlib
import xml.etree.ElementTree as ET
import subprocess
import sys
from pathlib import Path
from typing import Any

import numpy as np
import allo
from claude_agent_sdk import tool, create_sdk_mcp_server

from golden_models import GOLDEN_MODELS, generar_vectores_test


# ---------------------------------------------------------------------------
# IMPORTANTE -- descubierto el 6 de agosto de 2026 (ver docs/bitacora.md):
# algunos componentes internos de Allo (en concreto, se observó en el
# verificador PAST invocado por allo.verify() en L3, ante un error fatal de
# parseo del código C generado) NO lanzan una excepción Python normal ante
# un fallo -- llaman a algo equivalente a sys.exit(1), que produce un
# SystemExit. SystemExit hereda de BaseException, NO de Exception, así que
# un simple "except Exception as e:" lo deja pasar de largo: la excepción
# se propaga sin capturar y mata TODO el proceso de orchestrator.py (con un
# código de salida, sin traceback de Python visible -- así es como se
# detectó: un "echo $?" devolviendo 1 justo tras un cuelgue silencioso).
#
# Por eso las herramientas de la cascada capturan (Exception, SystemExit)
# en vez de solo Exception. Deliberadamente NO se captura BaseException a
# secas, para no absorber también KeyboardInterrupt (Ctrl+C) -- eso seguiría
# interrumpiendo el proceso si hace falta pararlo a mano.
# ---------------------------------------------------------------------------
ERRORES_CAPTURABLES = (Exception, SystemExit)


# ---------------------------------------------------------------------------
# Constantes de L4 (ver docs/SETUP_VITIS.md para el detalle completo de la
# instalación y el bache del binario 'vivado_hls' discontinuado)
# ---------------------------------------------------------------------------
NOMBRE_PROYECTO_VITIS = "out.prj"  # fijo -- así lo nombra Allo internamente,
                                     # independientemente del project= que le pasemos
TIMEOUT_SINTESIS_L4_SEGUNDOS = 600  # 20 min; subido de nuevo el 20 de agosto
                                      # de 2026 tras confirmar que 600s seguían
                                      # siendo insuficientes en el hardware
                                      # disponible (portátil de gama media) para
                                      # la síntesis completa de la FFT de 1024
                                      # puntos con objetivo_ii=1 -- ver
                                      # docs/bitacora.md. Si esto sigue sin
                                      # bastar, valorar relajar objetivo_ii a 2
                                      # como decisión de ingeniería documentada
                                      # en vez de seguir subiendo el timeout.


def _formatear_error(e: BaseException, log_stdout: str = "") -> str:
    """Da formato uniforme a un error capturado en cualquier nivel de la
    cascada (L1/L2), incluyendo el log de stdout de Python capturado durante
    la llamada (si lo hay).

    Nota importante (6 de agosto de 2026, ver docs/bitacora.md): cuando el
    error es un SystemExit, Allo suele haber impreso ya un panel de
    diagnóstico rico (el recuadro "Traceback (most recent call last):
    Line: N" con el código fuente resaltado que se ve en la consola). PERO
    ese panel puede escribirse a nivel de file descriptor nativo (C++), no
    a través de sys.stdout de Python -- en cuyo caso NO aparecerá en
    log_stdout aunque sí sea visible en la terminal real. Se documenta esto
    explícitamente en vez de fingir que siempre se captura.
    """
    if isinstance(e, SystemExit):
        base = (
            f"SystemExit(code={e.code}) -- probablemente un error fatal "
            "interno de Allo (parseo/verificación de tipos), no una "
            "excepción Python normal."
        )
    else:
        base = f"{type(e).__name__}: {e}\n{traceback.format_exc(limit=3)}"

    if log_stdout:
        base += (
            "\n\nLog de stdout de Python capturado durante la llamada "
            "(puede no incluir el panel de diagnóstico completo si Allo "
            "escribe a nivel de file descriptor nativo en vez de vía "
            "sys.stdout de Python):\n"
            f"{log_stdout[-4000:]}"
        )
    else:
        base += (
            "\n\n(No se capturó nada en sys.stdout durante la llamada -- si "
            "esperabas ver el panel de diagnóstico de Allo aquí, revisa la "
            "consola real donde corre orchestrator.py: es posible que Allo "
            "lo haya escrito a nivel de file descriptor nativo, fuera del "
            "alcance de contextlib.redirect_stdout.)"
        )
    return base


# ---------------------------------------------------------------------------
# Utilidades compartidas para pasar del texto crudo del Generador (con
# cabeceras "### KERNEL" / "### SCHEDULE") a objetos Python que Allo pueda
# procesar. Se reutilizan desde varios niveles de la cascada (L1, L2, ...).
#
# IMPORTANTE: allo.customize() usa inspect.getsource() internamente sobre la
# función del kernel. inspect.getsource() necesita un archivo .py real en
# disco -- una función creada con exec() en memoria no tiene ese respaldo y
# falla con "OSError: could not get source code". Por eso el kernel se
# escribe a un archivo temporal real y se importa como módulo, en vez de
# ejecutarlo directamente en un namespace en memoria.
#
# Convención asumida: el Generador SIEMPRE nombra la función del kernel
# 'kernel' (ver SYSTEM_PROMPT_GENERADOR en orchestrator.py). Si en algún
# momento el Generador empieza a fallar aquí de forma sistemática, lo primero
# a revisar es si sigue respetando esa convención.
# ---------------------------------------------------------------------------

def _extraer_bloques(codigo_texto: str) -> tuple[str, str]:
    """Separa el texto crudo del Generador en dos fragmentos de código Python
    ejecutables: (código del kernel, código del schedule). Quita fences de
    markdown (```python ... ```) si el modelo los ha metido.

    NUEVO (20 de agosto de 2026, ver docs/bitacora.md): _limpiar() ya no
    asume que las vallas de markdown están SOLO al principio/final del
    bloque -- se vio un caso real donde el Generador dejó una valla suelta
    en medio del archivo (probablemente narración o un fence adicional que
    no se depuró), lo que colaba una línea "```" literal en el .py escrito
    a disco y rompía la sintaxis Python en L1. Ahora se elimina CUALQUIER
    línea que sea puramente una valla de markdown (con o sin especificador
    de lenguaje, p.ej. "```" o "```python"), esté donde esté en el bloque."""
    if "### SCHEDULE" not in codigo_texto:
        raise ValueError("Falta la cabecera '### SCHEDULE' en la salida del Generador")
    antes, schedule_src = codigo_texto.split("### SCHEDULE", 1)
    if "### KERNEL" not in antes:
        raise ValueError("Falta la cabecera '### KERNEL' en la salida del Generador")
    kernel_src = antes.split("### KERNEL", 1)[1]

    _PATRON_VALLA = re.compile(r"^```[a-zA-Z]*\s*$")

    def _limpiar(bloque: str) -> str:
        lineas = bloque.split("\n")
        lineas_limpias = [ln for ln in lineas if not _PATRON_VALLA.match(ln.strip())]
        return "\n".join(lineas_limpias).strip()

    return _limpiar(kernel_src), _limpiar(schedule_src)


def _cargar_kernel_desde_disco(kernel_src: str):
    """Escribe el código del kernel a un archivo .py real en disco y lo
    importa como módulo, para que inspect.getsource() (usado internamente
    por allo.customize()) pueda encontrar su código fuente.

    El propio kernel_src ya trae sus imports (import allo, from
    allo.ir.types import ...) tal como los escribe el Generador, así que no
    hace falta inyectar ningún namespace extra aquí."""
    directorio = tempfile.mkdtemp(prefix="allo_kernel_")
    ruta = os.path.join(directorio, f"kernel_{uuid.uuid4().hex}.py")
    with open(ruta, "w") as f:
        f.write(kernel_src)

    nombre_modulo = os.path.splitext(os.path.basename(ruta))[0]
    spec = importlib.util.spec_from_file_location(nombre_modulo, ruta)
    modulo = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(modulo)

    if not hasattr(modulo, "kernel") or not callable(modulo.kernel):
        raise ValueError("El bloque KERNEL no define una función llamada 'kernel'")

    return modulo.kernel


def _construir_schedule(kernel_fn, schedule_src: str):
    """Ejecuta el bloque SCHEDULE sobre el kernel ya cargado desde disco y
    devuelve el Schedule resultante.

    CONVENCIÓN ASUMIDA (mismo espíritu que el nombre 'kernel' fijo para L1):
    el bloque SCHEDULE es código Python que ve la función del kernel bajo el
    nombre 'kernel' y el módulo 'allo' ya disponibles, y debe terminar
    dejando el Schedule final en una variable llamada 's'. Típicamente:

        s = allo.customize(kernel)
        s.split("i", factor=4)   # transformaciones opcionales del schedule

    Si el Generador no respeta esto (p. ej. no deja 's' definida, o espera
    que 'kernel' se llame de otra forma), esta función es el primer sitio
    donde revisar cuando L2 empiece a fallar de forma sistemática -- igual
    que la convención de 'kernel' lo es para L1.
    """
    namespace: dict[str, Any] = {"allo": allo, "kernel": kernel_fn}
    exec(schedule_src, namespace)

    if "s" not in namespace:
        raise ValueError(
            "El bloque SCHEDULE no define una variable 's' con el Schedule "
            "de Allo. Revisa el prompt del Generador (SYSTEM_PROMPT_GENERADOR)."
        )
    return namespace["s"]


@tool(
    "run_l1_parse_types",
    "Nivel L1: compila el kernel Allo con allo.customize() y comprueba "
    "sintaxis y tipos. Devuelve ok=True si compila, o el error de MLIR traducido.",
    {"codigo_allo": str},
)
async def run_l1_parse_types(args: dict[str, Any]) -> dict[str, Any]:
    codigo = args["codigo_allo"]
    log = io.StringIO()

    try:
        kernel_src, _ = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
        with contextlib.redirect_stdout(log):
            allo.customize(kernel_fn)  # aquí ocurre el parseo/type-check real de Allo
        ok, salida = True, "Sintaxis y tipos OK"
    except ERRORES_CAPTURABLES as e:  # noqa: BLE001 -- incluye SystemExit, ver nota arriba
        ok, salida = False, _formatear_error(e, log.getvalue())

    return {
        "content": [{"type": "text", "text": json.dumps({"nivel": "L1", "ok": ok, "salida_cruda": salida})}]
    }


@tool(
    "run_l2_functional",
    "Nivel L2: compila con s.build(target='llvm') y ejecuta el módulo contra "
    "el golden model sobre los vectores de test. Devuelve diff numérico si falla.",
    {"codigo_allo": str, "golden_model_id": str},
)
async def run_l2_functional(args: dict[str, Any]) -> dict[str, Any]:
    codigo = args["codigo_allo"]
    golden_id = args["golden_model_id"]
    log = io.StringIO()

    try:
        golden_fn = GOLDEN_MODELS.get(golden_id)
        if golden_fn is None:
            raise KeyError(
                f"golden_model_id '{golden_id}' no está registrado en "
                f"golden_models.GOLDEN_MODELS: {list(GOLDEN_MODELS.keys())}"
            )

        kernel_src, schedule_src = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
        with contextlib.redirect_stdout(log):
            s = _construir_schedule(kernel_fn, schedule_src)
            mod = s.build(target="llvm")

        x_real, x_imag = generar_vectores_test()
        y_real = np.zeros_like(x_real)
        y_imag = np.zeros_like(x_imag)

        # Asume firma kernel(x_real, x_imag, y_real, y_imag) -> None, con las
        # salidas escritas in-place (patrón habitual en Allo/HLS). Si tu
        # kernel en vez de eso RETORNA los arrays, cambia esta línea a
        # y_real, y_imag = mod(x_real, x_imag).
        mod(x_real, x_imag, y_real, y_imag)

        y_real_ref, y_imag_ref = golden_fn(x_real, x_imag)

        tol = 1e-3
        diff_real = np.abs(y_real - y_real_ref)
        diff_imag = np.abs(y_imag - y_imag_ref)
        ok = bool(np.all(diff_real < tol) and np.all(diff_imag < tol))

        if ok:
            salida = f"Ejecución funcional OK contra golden model '{golden_id}'"
        else:
            idx_discrepantes = np.where((diff_real >= tol) | (diff_imag >= tol))[0]
            salida = (
                f"Diff contra '{golden_id}': {len(idx_discrepantes)} índices "
                f"discrepantes de {len(x_real)}. Primeros 10: "
                f"{idx_discrepantes[:10].tolist()}. "
                f"max|diff_real|={diff_real.max():.4g}, "
                f"max|diff_imag|={diff_imag.max():.4g}, tol={tol}"
            )

    except ERRORES_CAPTURABLES as e:  # noqa: BLE001 -- igual que en L1, incluye SystemExit
        ok = False
        salida = _formatear_error(e, log.getvalue())

    return {
        "content": [{"type": "text", "text": json.dumps({"nivel": "L2", "ok": ok, "salida_cruda": salida})}]
    }


@tool(
    "run_l3_equivalence",
    "Nivel L3: verifica con el verificador formal de Allo (allo.verify) que "
    "el schedule propuesto preserva la semántica del kernel base.",
    {"codigo_allo": str},
)
async def run_l3_equivalence(args: dict[str, Any]) -> dict[str, Any]:
    """
    IMPORTANTE (15 de agosto de 2026, ver docs/bitacora.md): esta función
    YA NO llama a allo.verify() directamente en este proceso. El
    verificador PAST tiene reglas gramaticales sin implementar
    ("[PAST][Parser] Rule 7 not implemented!") que en ciertos kernels no
    solo producen un árbol incompleto, sino que además disparan un
    assert() de C++ ("core/past.c:2489: set_parent_pref: Assertion
    'n->rhs' failed.") que termina en abort() -- SIGABRT. Un SIGABRT mata
    el proceso Python ENTERO, no es capturable con try/except (ni con
    ERRORES_CAPTURABLES, que solo cubre excepciones de Python +
    SystemExit -- un abort() ni siquiera pasa por ahí). Sin aislamiento,
    un crash de PAST se llevaba por delante todo orchestrator.py y el
    progreso de las 6 iteraciones de golpe.

    Por eso allo.verify() se ejecuta ahora en un SUBPROCESO separado
    (l3_subproceso.py, en esta misma carpeta) vía subprocess.run(). Si el
    subproceso muere por señal (returncode negativo), se reporta como un
    fallo L3 controlado -- el proceso principal (y con él, el estado del
    orquestador) sigue vivo, y se puede decidir continuar/regenerar con
    normalidad en vez de morir con él.

    API real de fondo (confirmada contra `help(allo.verify)` el 5 de
    agosto de 2026): verify(schedule_a, schedule_b) -> bool. Ver
    l3_subproceso.py para el uso exacto.
    """
    codigo = args["codigo_allo"]

    directorio_tmp = Path(tempfile.mkdtemp(prefix="allo_l3_"))
    ruta_resultado = directorio_tmp / "resultado.json"

    try:
        resultado_bytes = subprocess.run(
            [sys.executable, "l3_subproceso.py", str(ruta_resultado)],
            input=codigo.encode("utf-8"),
            capture_output=True,
            timeout=180,  # ajustar si kernels reales tardan más en verificar
        )
    except subprocess.TimeoutExpired:
        return {
            "content": [{"type": "text", "text": json.dumps(
                {"nivel": "L3", "ok": False,
                 "salida_cruda": "allo.verify() excedió el timeout de 180s en el subproceso aislado."})}]
        }

    # NUEVO (16 de agosto de 2026, ver docs/bitacora.md): ya NO se
    # intenta parsear el JSON desde stdout del subproceso -- el panel de
    # diagnóstico nativo de PAST (C++) puede mezclarse de forma
    # impredecible con cualquier salida de Python en el mismo stream,
    # produciendo JSON corrupto incluso cuando la verificación en sí tuvo
    # éxito (visto el 15/16 de agosto: el log crudo mostraba
    # "[PAST][AI][Equivalence] Success" pero el parseo fallaba igualmente
    # por bytes intercalados). l3_subproceso.py ahora escribe su
    # resultado a un ARCHIVO dedicado (ruta_resultado), completamente
    # aislado de stdout/stderr.
    stdout_str = resultado_bytes.stdout.decode("utf-8", errors="replace")
    stderr_str = resultado_bytes.stderr.decode("utf-8", errors="replace")

    if resultado_bytes.returncode != 0:
        # returncode negativo == terminado por señal (p.ej. -6 == SIGABRT,
        # el crash de PAST ya documentado). positivo != 0 == excepción no
        # capturada dentro del propio l3_subproceso.py.
        salida = (
            f"El subproceso de verificación L3 terminó de forma anómala "
            f"(returncode={resultado_bytes.returncode}"
            f"{' -- probablemente SIGABRT, crash nativo de PAST, ver docs/bitacora.md 15 de agosto' if resultado_bytes.returncode < 0 else ''}"
            f").\nstderr (últimas líneas):\n{stderr_str[-2000:]}"
        )
        return {
            "content": [{"type": "text", "text": json.dumps(
                {"nivel": "L3", "ok": False, "salida_cruda": salida})}]
        }

    if not ruta_resultado.exists():
        return {
            "content": [{"type": "text", "text": json.dumps(
                {"nivel": "L3", "ok": False,
                 "salida_cruda": f"El subproceso L3 terminó con código 0 pero no escribió "
                                  f"{ruta_resultado}. stdout:\n{stdout_str[-2000:]}\nstderr:\n{stderr_str[-2000:]}"})}]
        }

    with open(ruta_resultado, "r", encoding="utf-8") as f:
        datos = json.load(f)

    return {
        "content": [{"type": "text", "text": json.dumps(
            {"nivel": "L3", "ok": datos["ok"], "salida_cruda": datos["salida_cruda"]})}]
    }


def _vitis_hls_disponible() -> bool:
    return shutil.which("vitis_hls") is not None


def _parsear_reporte_csynth(ruta_xml: Path) -> dict:
    """Parsea el informe XML de síntesis (<project>/out.prj/solution1/syn/
    report/kernel_csynth.xml). Etiquetas confirmadas contra una síntesis
    real en Vitis HLS 2023.1 el 12 de agosto de 2026 (ver docs/bitacora.md)
    -- NO son las que trae la documentación oficial para otras versiones,
    que puede variar ligeramente."""
    root = ET.parse(ruta_xml).getroot()

    def _texto(path, default=None):
        el = root.find(path)
        return el.text if el is not None else default

    # Puede haber varios bucles con su propio PipelineII bajo
    # SummaryOfLoopLatency (uno por cada <nombre_de_bucle> anidado como
    # etiqueta dinámica) -- cogemos el mínimo, asumiendo que el bucle
    # crítico/interno es el que nos interesa para objetivo_ii.
    iis = [int(el.text) for el in root.findall(".//SummaryOfLoopLatency//PipelineII")
           if el.text is not None]
    ii_minimo = min(iis) if iis else None

    return {
        "II": ii_minimo,
        "latencia_peor_caso": _texto(".//SummaryOfOverallLatency/Worst-caseLatency"),
        "periodo_reloj_estimado_ns": _texto(".//SummaryOfTimingAnalysis/EstimatedClockPeriod"),
        "BRAM": _texto(".//AreaEstimates/Resources/BRAM_18K"),
        "DSP": _texto(".//AreaEstimates/Resources/DSP"),
        "LUT": _texto(".//AreaEstimates/Resources/LUT"),
        "FF": _texto(".//AreaEstimates/Resources/FF"),
    }


@tool(
    "run_l4_hls",
    "Nivel L4: sintetiza con Vitis HLS (target='vivado_hls', mode='csyn') y "
    "extrae II, latencia, BRAM/DSP/LUT del informe de síntesis real.",
    {"codigo_allo": str, "objetivo_ii": int},
)
async def run_l4_hls(args: dict[str, Any]) -> dict[str, Any]:
    """
    OJO (12 de agosto de 2026, ver docs/bitacora.md y docs/SETUP_VITIS.md
    para el detalle completo): esta función NO llama a mod() tal cual lo
    devuelve s.build(target="vivado_hls", mode="csyn", ...). Ese mod()
    dispara un Makefile generado por Allo que invoca literalmente el
    binario 'vivado_hls' -- discontinuado por Xilinx desde Vitis 2020.2+ (el
    binario actual se llama 'vitis_hls' y tiene una estructura interna de
    instalación distinta; un symlink vivado_hls -> vitis_hls NO basta,
    porque vitis_hls intenta localizar un ejecutable "unwrapped" en una
    subcarpeta que ya no existe en su propio árbol de instalación).

    En vez de eso:
      1. Se deja que s.build() genere el proyecto HLS en disco (run.tcl,
         kernel.cpp, etc.) -- este paso NO requiere vitis_hls todavía.
      2. Se lanza `vitis_hls -f run.tcl` nosotros mismos con subprocess,
         saltándonos el Makefile roto.
      3. El proyecto real de Vitis queda anidado en
         <project_dir>/out.prj/ -- Allo usa ese nombre fijo internamente,
         independientemente del project= que le pasemos.
      4. El informe de síntesis está en
         <project_dir>/out.prj/solution1/syn/report/kernel_csynth.xml

    Confirmado empíricamente contra una síntesis real (kernel trivial de
    suma de vectores) en Vitis HLS 2023.1 antes de integrarlo aquí.
    """
    codigo = args["codigo_allo"]
    objetivo_ii = args["objetivo_ii"]

    if not _vitis_hls_disponible():
        salida = (
            "vitis_hls no está en el PATH. ¿Has hecho 'source "
            "~/tools/Vitis_HLS/2023.1/settings64.sh' antes de arrancar "
            "el orquestador? (ver docs/SETUP_VITIS.md)"
        )
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    # --- Paso 1: generar el proyecto HLS (no requiere vitis_hls todavía) ---
    try:
        kernel_src, schedule_src = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
        s = _construir_schedule(kernel_fn, schedule_src)

        directorio_proyecto = Path(tempfile.mkdtemp(prefix="allo_l4_"))
        s.build(target="vivado_hls", mode="csyn", project=str(directorio_proyecto))
    except ERRORES_CAPTURABLES as e:  # noqa: BLE001 -- mismo patrón que L1-L3
        salida = _formatear_error(e)
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    run_tcl = directorio_proyecto / "run.tcl"
    if not run_tcl.exists():
        salida = f"s.build() no generó run.tcl en {directorio_proyecto}"
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    # --- Paso 2: lanzar vitis_hls directamente sobre run.tcl, saltándonos
    #             el Makefile roto de Allo (ver docstring de esta función) ---
    try:
        resultado = subprocess.run(
            ["vitis_hls", "-f", "run.tcl"],
            cwd=directorio_proyecto,
            capture_output=True,
            text=True,
            timeout=TIMEOUT_SINTESIS_L4_SEGUNDOS,
        )
    except subprocess.TimeoutExpired:
        salida = f"Síntesis excedió el timeout de {TIMEOUT_SINTESIS_L4_SEGUNDOS}s"
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    if resultado.returncode != 0:
        salida = (
            f"vitis_hls devolvió código {resultado.returncode}:\n"
            f"{resultado.stdout[-2000:]}\n{resultado.stderr[-2000:]}"
        )
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    # --- Paso 3: parsear el informe real de síntesis ---
    ruta_xml = directorio_proyecto / NOMBRE_PROYECTO_VITIS / "solution1" / "syn" / "report" / "kernel_csynth.xml"
    if not ruta_xml.exists():
        salida = f"vitis_hls terminó (código 0) pero no se encontró el informe en {ruta_xml}"
        return {
            "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": False, "salida_cruda": salida})}]
        }

    metricas = _parsear_reporte_csynth(ruta_xml)
    ii_conseguido = metricas["II"]
    ok = ii_conseguido is not None and ii_conseguido <= objetivo_ii
    salida = json.dumps(metricas)

    return {
        "content": [{"type": "text", "text": json.dumps({"nivel": "L4", "ok": ok, "salida_cruda": salida, "metricas": metricas})}]
    }


# Empaqueta todas las herramientas en un servidor MCP en proceso.
# Esto es lo que se pasa a ClaudeAgentOptions(mcp_servers={"allo-tools": ...})
# del agente Ejecutor.
allo_tools_server = create_sdk_mcp_server(
    name="allo-tools",
    version="1.0.0",
    tools=[run_l1_parse_types, run_l2_functional, run_l3_equivalence, run_l4_hls],
)
