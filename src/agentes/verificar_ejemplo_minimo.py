"""
Version MINIMA de verificar_cascada_completa.py: FFT de 8 puntos en vez de
1024, para aislar si la cascada L1->L4 funciona de punta a punta cuando el
diseño es trivial de sintetizar (particion completa de 2 arrays de 8
elementos = 16 registros, nada que ver con 1024) -- si esto tambien se
queda colgado en L4, el problema NO es el tamano del diseno; si esto pasa
rapido, confirma que L1-L4 funcionan y que el problema con la FFT de 1024 es
puramente de escala/tiempo de sintesis, no de la tuberia en si.

Llama a las MISMAS funciones reales de allo_tools.py (nada de LLM, nada de
mock). golden_model_id, objetivo_ii y n_puntos van fijos aqui mismo -- no
lee specs/spec_example.yaml porque ese describe el bloque real de 1024
puntos, no este ejemplo reducido.

Uso (desde src/agentes/):
    source ~/tools/Vitis_HLS/2023.1/settings64.sh
    python3 verificar_ejemplo_minimo.py
"""

import asyncio
import json
import sys

from allo_tools import (
    run_l1_parse_types,
    run_l2_functional,
    run_l3_equivalence,
    run_l4_hls,
)

RUTA_DOCUMENTO = "kernel_minimo_n8.txt"
GOLDEN_MODEL_ID = "fft_radix2_numpy_reference"
N_PUNTOS = 8
OBJETIVO_II = 1  # diseno trivial, deberia cerrar sin problema

CASCADA = [
    ("L1", run_l1_parse_types, lambda codigo: {"codigo_allo": codigo}),
    ("L2", run_l2_functional, lambda codigo: {
        "codigo_allo": codigo, "golden_model_id": GOLDEN_MODEL_ID, "n_puntos": N_PUNTOS}),
    ("L3", run_l3_equivalence, lambda codigo: {"codigo_allo": codigo}),
    ("L4", run_l4_hls, lambda codigo: {"codigo_allo": codigo, "objetivo_ii": OBJETIVO_II}),
]


async def main() -> None:
    with open(RUTA_DOCUMENTO, encoding="utf-8") as f:
        codigo = f.read()

    print(f"Verificando '{RUTA_DOCUMENTO}' (FFT de {N_PUNTOS} puntos, "
          f"objetivo_ii={OBJETIVO_II}) contra la cascada real L1->L4\n")

    for nombre, herramienta, construir_args in CASCADA:
        print(f"--- {nombre} ---")
        resultado = await herramienta.handler(construir_args(codigo))
        datos = json.loads(resultado["content"][0]["text"])
        print(f"ok={datos['ok']}")
        print(datos["salida_cruda"][:4000])
        print()
        if not datos["ok"]:
            print(f"⚠️  Cascada detenida en {nombre}.")
            sys.exit(1)

    print("✅ L1-L4 pasaron TODOS contra el ejemplo minimo de 8 puntos. "
          "La tuberia funciona de punta a punta; el problema con la FFT de "
          "1024 es de escala/tiempo de sintesis, no de la cascada en si.")


if __name__ == "__main__":
    asyncio.run(main())
