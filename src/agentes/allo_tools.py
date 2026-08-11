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
  - run_l4_hls          -> todavía MOCKEADO

Para las que siguen mockeadas: sustituye el cuerpo de cada función `MOCK_*`
por la llamada real (se indica con un comentario "# TODO: reemplazar por").
La firma (nombre, descripción, parámetros) puede quedarse igual.
"""

import json
import os
import tempfile
import traceback
import uuid
import importlib.util
import io
import contextlib
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
    markdown (```python ... ```) si el modelo los ha metido."""
    if "### SCHEDULE" not in codigo_texto:
        raise ValueError("Falta la cabecera '### SCHEDULE' en la salida del Generador")
    antes, schedule_src = codigo_texto.split("### SCHEDULE", 1)
    if "### KERNEL" not in antes:
        raise ValueError("Falta la cabecera '### KERNEL' en la salida del Generador")
    kernel_src = antes.split("### KERNEL", 1)[1]

    def _limpiar(bloque: str) -> str:
        bloque = bloque.strip()
        if bloque.startswith("```"):
            bloque = bloque.split("\n", 1)[1]
        if bloque.endswith("```"):
            bloque = bloque.rsplit("```", 1)[0]
        return bloque.strip()

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
    API real -- confirmada contra `help(allo.verify)` en el entorno instalado
    (5 de agosto de 2026), no solo contra el ejemplo del paper PLDI'24:

        verify(schedule_a, schedule_b)
            Run PAST verifier on the two schedules, returning whether they
            are equivalent. If equivalence fails, output a diff of the
            generated code files to help diagnose the source of the mismatch.

    Es decir: allo.verify() devuelve directamente un booleano, y si la
    equivalencia falla, Allo mismo escribe/imprime un diff del código
    generado para ayudar a localizar el mismatch. Confirmado empíricamente
    (5 de agosto de 2026): ese diagnóstico sale por stdout DURANTE la
    llamada, no como parte del valor de retorno -- por eso este wrapper
    captura stdout con contextlib.redirect_stdout mientras se ejecuta
    allo.verify() y mete el log (recortado) en salida_cruda, en vez de
    dejar que se pierda en la consola del proceso.

    Uso (mismo patrón que Fig. 6a del paper de Allo):
        s_orig = allo.customize(kernel)   # schedule "antes" -- SIN transformaciones
        s = allo.customize(kernel)
        s.<primitivas...>                 # schedule "después" -- lo que trae el Generador
        ok = allo.verify(s, s_orig)

    Restricción documentada por Allo (SICF -- Statically Interpretable
    Control-Flow): el tamaño del problema debe ser conocido en tiempo de
    compilación; no soporta análisis paramétrico de bucles. Para la FFT
    radix-2 de spec_example.yaml (N=1024 fijo) esto se cumple.
    """
    codigo = args["codigo_allo"]
    log_verify = io.StringIO()  # captura el stdout que PAST imprime durante allo.verify()

    try:
        kernel_src, schedule_src = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)

        # Schedule "antes": el kernel base, sin ninguna primitiva aplicada.
        s_orig = allo.customize(kernel_fn)

        # Schedule "después": el mismo kernel con las transformaciones que
        # trae el bloque SCHEDULE del Generador.
        s = _construir_schedule(kernel_fn, schedule_src)

        # PAST (el verificador formal de Allo) imprime su diagnóstico por
        # stdout durante la propia llamada -- confirmado empíricamente el
        # 5 de agosto de 2026 (ver docs/bitacora.md): al fallar, imprime en
        # qué nodo del árbol de cómputo difieren los programas y un diff
        # unificado del código generado para cada schedule. Lo capturamos
        # aquí en vez de dejar que se pierda en la consola del proceso.
        with contextlib.redirect_stdout(log_verify):
            ok = bool(allo.verify(s, s_orig))

        if ok:
            salida = "Equivalencia de schedule verificada por allo.verify(s, s_orig)"
        else:
            # Recortamos a los últimos ~4000 caracteres: es donde PAST
            # imprime su diagnóstico final ("First difference...",
            # "Mismatch...", el diff unificado del código generado). Un log
            # completo sin recortar podría acercarse al límite de salida de
            # las herramientas MCP (~25K tokens por defecto).
            salida = (
                "allo.verify(s, s_orig) devolvió False -- NO equivalente.\n"
                "Diagnóstico de PAST (verificador formal de Allo):\n"
                f"{log_verify.getvalue()[-4000:]}"
            )

    except ERRORES_CAPTURABLES as e:  # noqa: BLE001 -- mismo patrón que L1/L2, incluye SystemExit
        ok = False
        if isinstance(e, SystemExit):
            # Caso observado el 6 de agosto de 2026: algún componente
            # interno invocado por allo.verify() (aparentemente PAST, el
            # verificador formal) puede abortar con SystemExit ante un
            # error fatal de parseo, en vez de lanzar una excepción Python
            # normal. El diagnóstico detallado de PAST (p. ej.
            # "PASTFULLPARSER| Line N: syntax error...") se imprime
            # aparentemente a nivel de file descriptor nativo (C++), NO a
            # través de sys.stdout de Python -- por eso NO aparece en
            # log_verify (que solo captura sys.stdout) aunque sí sea
            # visible en la consola real del proceso. Se deja constancia
            # explícita de esta limitación en vez de fingir que se capturó
            # el detalle.
            salida = (
                f"SystemExit(code={e.code}) durante allo.verify(s, s_orig) -- "
                "probablemente un error fatal de parseo interno de PAST sobre "
                "el código C generado (no de Python). El mensaje detallado NO "
                "se pudo capturar aquí porque PAST parece escribir a stdout a "
                "nivel de proceso nativo, no a través de sys.stdout de Python "
                "-- revisa la consola donde corre orchestrator.py para verlo."
            )
        else:
            salida = f"{type(e).__name__}: {e}\n{traceback.format_exc(limit=3)}"
        log_parcial = log_verify.getvalue()
        if log_parcial:
            salida += f"\n\nLog parcial de PAST antes del error:\n{log_parcial[-2000:]}"

    return {
        "content": [{"type": "text", "text": json.dumps({"nivel": "L3", "ok": ok, "salida_cruda": salida})}]
    }


@tool(
    "run_l4_hls",
    "Nivel L4: sintetiza con s.build(target='vitis_hls', mode='csyn') y "
    "extrae II, latencia, BRAM/DSP/LUT del informe de síntesis.",
    {"codigo_allo": str, "objetivo_ii": int},
)
async def run_l4_hls(args: dict[str, Any]) -> dict[str, Any]:
    codigo = args["codigo_allo"]
    objetivo_ii = args["objetivo_ii"]

    # TODO: reemplazar por:
    #   kernel_src, schedule_src = _extraer_bloques(codigo)
    #   kernel_fn = _cargar_kernel_desde_disco(kernel_src)
    #   s = _construir_schedule(kernel_fn, schedule_src)
    #   mod = s.build(target="vitis_hls", mode="csyn")
    #   parsear el informe de síntesis -> II, latencia, BRAM, DSP, LUT
    ii_conseguido = objetivo_ii  # MOCK: asumimos que se cumple el objetivo
    ok = ii_conseguido <= objetivo_ii
    metricas = {"II": ii_conseguido, "latencia": 42, "BRAM": 4, "DSP": 8, "LUT": 1200}
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
