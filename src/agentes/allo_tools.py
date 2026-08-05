"""
Herramientas del agente EJECUTOR.

Cada función de aquí abajo es una herramienta que el agente Ejecutor puede
llamar.

Estado actual:
  - run_l1_parse_types  -> CONECTADO A ALLO REAL (allo.customize())
  - run_l2_functional   -> todavía MOCKEADO
  - run_l3_equivalence  -> todavía MOCKEADO
  - run_l4_hls          -> todavía MOCKEADO

Para las que siguen mockeadas: sustituye el cuerpo de cada función `MOCK_*`
por la llamada real (se indica con un comentario "# TODO: reemplazar por").
La firma (nombre, descripción, parámetros) puede quedarse igual.
"""

import json
import os
import tempfile
import uuid
import importlib.util
from typing import Any

import allo
from claude_agent_sdk import tool, create_sdk_mcp_server


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

    # TODO: reemplazar por:
    #   kernel_src, schedule_src = _extraer_bloques(codigo)
    #   kernel_fn = _cargar_kernel_desde_disco(kernel_src)
    #   s = allo.customize(kernel_fn)
    #   (aplicar aquí el schedule_src sobre 's', p.ej. exec(schedule_src, {"s": s, "allo": allo}))
    #   mod = s.build(target="llvm")
    #   salida = mod(*vectores_test)
    #   comparar contra golden_model(*vectores_test) -> diff + índices discrepantes
    #   (pendiente: resolver golden_id contra un registro real, ver golden_models.py)
    ok = True  # MOCK: asumimos éxito para que el pipeline de ejemplo llegue al final
    salida = f"Ejecución funcional OK contra golden model '{golden_id}'"

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
    #   s = allo.customize(kernel_fn)
    #   (aplicar aquí el schedule_src sobre 's')
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
