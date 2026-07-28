"""
Herramientas del agente EJECUTOR.

Cada función de aquí abajo es una herramienta que el agente Ejecutor puede
llamar. Ahora mismo están MOCKEADAS (simuladas) para que puedas correr el
pipeline completo sin tener el toolchain de Allo instalado todavía.

Cuando tengas Allo instalado, sustituye el cuerpo de cada función `MOCK_*`
por la llamada real (se indica con un comentario "# TODO: reemplazar por").
La firma (nombre, descripción, parámetros) puede quedarse igual.
"""

import json
from typing import Any
from claude_agent_sdk import tool, create_sdk_mcp_server


@tool(
    "run_l1_parse_types",
    "Nivel L1: compila el kernel Allo con allo.customize() y comprueba "
    "sintaxis y tipos. Devuelve ok=True si compila, o el error de MLIR traducido.",
    {"codigo_allo": str},
)
async def run_l1_parse_types(args: dict[str, Any]) -> dict[str, Any]:
    codigo = args["codigo_allo"]

    # TODO: reemplazar por:
    #   s = allo.customize(kernel_from(codigo))
    #   -> capturar excepción de MLIR y traducirla a texto legible
    ok = "def " in codigo and "return" in codigo  # MOCK: chequeo trivial
    salida = "Sintaxis y tipos OK" if ok else "Error MOCK: falta 'return' en el kernel"

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
    #   s = allo.customize(kernel_from(codigo))
    #   mod = s.build(target="llvm")
    #   salida = mod(*vectores_test)
    #   comparar contra golden_model(*vectores_test) -> diff + índices discrepantes
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

    # TODO: reemplazar por:
    #   allo.verify.check_equivalence(kernel_base, kernel_con_schedule)
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
    #   s = allo.customize(kernel_from(codigo))
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
# Esto es lo que se pasa a ClaudeAgentOptions(mcp_servers=[...]) del agente Ejecutor.
allo_tools_server = create_sdk_mcp_server(
    name="allo-tools",
    version="1.0.0",
    tools=[run_l1_parse_types, run_l2_functional, run_l3_equivalence, run_l4_hls],
)
