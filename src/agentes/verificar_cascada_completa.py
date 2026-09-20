"""
Verificación DIRECTA (sin ningún LLM de por medio) de la cascada L1->L4 real
contra un kernel+schedule escritos a mano en 'kernel_y_schedule_verificado.txt'.

Por qué existe este script (19 de septiembre de 2026, ver docs/bitacora.md):
a día de hoy NINGUNA corrida del orquestador -- ni antes ni después del
cambio de arquitectura del 17 de septiembre -- ha visto jamás un
nivel_fallo=NINGUNO con metricas_hls reales. Todos los intentos que llegaron
a L4 (corridas de agosto) terminaron en timeout de síntesis o en II=null con
objetivo_ii=1; los de esta semana nunca pasaron de L1/L2 por inestabilidad
del Generador (o, en la iteración 5 contaminada, ni siquiera llegaron a
ejecutar la cascada de verdad). Así que segu​imos sin una sola confirmación
de que el camino de ÉXITO de L4 funcione de punta a punta contra la FFT real.

Este script cierra esa duda de la forma más directa posible: llama a las
MISMAS funciones que usa orchestrator.py (run_l1_parse_types,
run_l2_functional, run_l3_equivalence, run_l4_hls, importadas tal cual de
allo_tools.py) contra un kernel+schedule fijos, sin generación por LLM. Si
esto falla, el fallo es real (de Allo, de Vitis HLS, o del propio diseño del
schedule) -- no un artefacto de un Generador inestable ni de contaminación
de sesión.

El kernel es el mismo de 'kernel_verificado.txt' (tabla de twiddle factors
precomputada sin recurrencia, bit-reversal calculado in-kernel, límites de
bucle todos literales) -- ya evita los dos primeros de los tres motivos de
II=null documentados en la memoria del proyecto (recurrencia secuencial,
límites de bucle dependientes de variable). El schedule pipelinea TODOS los
bucles a II=20 (el objetivo_ii actual del spec, mucho más laxo que el
objetivo_ii=1 usado en las corridas de agosto que sí veían II=null) y
particiona por completo y_real/y_imag (se leen y escriben en dos índices
calculados por iteración -- más accesos de los que un BRAM de doble puerto
soporta sin partición).

Uso (desde este mismo directorio, src/agentes/):
    source ~/tools/Vitis_HLS/2023.1/settings64.sh   # si no lo tienes ya en el PATH
    python verificar_cascada_completa.py

Puede tardar varios minutos -- L4 lanza una síntesis HLS real. OJO: revisa
TIMEOUT_SINTESIS_L4_SEGUNDOS en allo_tools.py antes de lanzar esto -- se
detectó una posible discrepancia entre el comentario ("20 min") y el valor
real (600s = 10 min); si esto falla por timeout, ese es el primer sitio a
revisar antes de asumir que el schedule está mal.
"""

import asyncio
import json
import sys

import yaml

from allo_tools import (
    run_l1_parse_types,
    run_l2_functional,
    run_l3_equivalence,
    run_l4_hls,
)

RUTA_DOCUMENTO = "kernel_y_schedule_verificado.txt"
RUTA_SPEC = "../../specs/spec_example.yaml"

CASCADA = [
    ("L1", run_l1_parse_types,
     lambda codigo, spec: {"codigo_allo": codigo}),
    ("L2", run_l2_functional,
     lambda codigo, spec: {"codigo_allo": codigo, "golden_model_id": spec["golden_model_id"]}),
    ("L3", run_l3_equivalence,
     lambda codigo, spec: {"codigo_allo": codigo}),
    ("L4", run_l4_hls,
     lambda codigo, spec: {"codigo_allo": codigo, "objetivo_ii": spec["restricciones"]["objetivo_ii"]}),
]


async def main() -> None:
    with open(RUTA_DOCUMENTO, encoding="utf-8") as f:
        codigo = f.read()
    with open(RUTA_SPEC, encoding="utf-8") as f:
        spec = yaml.safe_load(f)

    print(
        f"Verificando '{RUTA_DOCUMENTO}' contra la cascada real L1->L4 "
        f"(golden_model_id={spec['golden_model_id']!r}, "
        f"objetivo_ii={spec['restricciones']['objetivo_ii']})\n"
    )

    for nombre, herramienta, construir_args in CASCADA:
        print(f"--- {nombre} ---")
        resultado = await herramienta.handler(construir_args(codigo, spec))
        datos = json.loads(resultado["content"][0]["text"])
        print(f"ok={datos['ok']}")
        print(datos["salida_cruda"][:4000])
        print()
        if not datos["ok"]:
            print(
                f"⚠️  Cascada detenida en {nombre}. Este es el primer nivel "
                f"real que falla para este kernel+schedule -- no es un fallo "
                f"de ningún LLM, es Allo/Vitis reportando esto de verdad."
            )
            sys.exit(1)

    print(
        "✅ L1-L4 pasaron TODOS de verdad contra este kernel+schedule fijo. "
        "Esto confirma que la tubería de validación (incluido L4 con síntesis "
        "HLS real) funciona de punta a punta para este diseño."
    )


if __name__ == "__main__":
    asyncio.run(main())
