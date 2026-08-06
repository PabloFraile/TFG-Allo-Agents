"""
Herramientas del agente EJECUTOR.

Cada función de aquí abajo es una herramienta que el agente Ejecutor puede
llamar.

Estado actual:
  - run_l1_parse_types  -> CONECTADO A ALLO REAL (allo.customize())
  - run_l2_functional   -> CONECTADO A ALLO REAL (s.build(target='llvm') +
                            comparación contra golden model real)
  - run_l3_equivalence  -> todavía MOCKEADO
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
from typing import Any

import numpy as np
import allo
from claude_agent_sdk import tool, create_sdk_mcp_server

from golden_models import GOLDEN_MODELS, generar_vectores_test


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

    try:
        kernel_src, _ = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
        allo.customize(kernel_fn)  # aquí ocurre el parseo/type-check real de Allo
        ok, salida = True, "Sintaxis y tipos OK"
    except Exception as e:  # noqa: BLE001 -- cualquier fallo (Python o MLIR) se traduce a ok=False
        ok, salida = False, f"{type(e).__name__}: {e}"

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

    try:
        golden_fn = GOLDEN_MODELS.get(golden_id)
        if golden_fn is None:
            raise KeyError(
                f"golden_model_id '{golden_id}' no está registrado en "
                f"golden_models.GOLDEN_MODELS: {list(GOLDEN_MODELS.keys())}"
            )

        kernel_src, schedule_src = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)
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

    except Exception as e:  # noqa: BLE001 -- igual que en L1, cualquier fallo se traduce a ok=False
        ok = False
        salida = f"{type(e).__name__}: {e}\n{traceback.format_exc(limit=3)}"

    return {
        "content": [{"type": "text", "text": json.dumps({"nivel": "L2", "ok": ok, "salida_cruda": salida})}]
    }


@tool(
    "run_l3_equivalence",
    "Nivel L3: verifica con el verificador formal de Allo que el schedule "
    "propuesto preserva la semántica del kernel base.",
    {"codigo_allo": str},
)
async def run_l3_equivalence(args: dict[str, Any]) -> dict[str, Any]:
    codigo = args["codigo_allo"]

    # TODO: reemplazar por la API real de verificación formal de Allo.
    #   Confirmar el nombre exacto contra el código fuente instalado
    #   (external/allo) o docs/source/dive/ del propio repo -- no dar por
    #   buena la firma "allo.verify.check_equivalence(...)" sin comprobarla.
    ok = True  # MOCK
    salida = "Equivalencia de schedule verificada (MOCK)"

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
