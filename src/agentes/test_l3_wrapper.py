"""
Prueba de NIVEL 2: llama directamente a la herramienta run_l3_equivalence()
de allo_tools.py, con código en el formato exacto que produce el Generador
(cabeceras "### KERNEL" / "### SCHEDULE"). Objetivo: confirmar que el
parseo (_extraer_bloques, _cargar_kernel_desde_disco, _construir_schedule)
funciona bien end-to-end, sin esperar a una corrida completa de 6
iteraciones del orchestrator.

Ejecutar desde src/agentes/:
    python3 test_l3_wrapper.py
"""

import asyncio
import json

from allo_tools import run_l3_equivalence


# Kernel + schedule trivial (sin ninguna primitiva de transformación) ->
# se espera ok=True, porque s y s_orig deberían ser idénticos.
CODIGO_TRIVIAL = """\
### KERNEL
import allo
from allo.ir.types import int32

def kernel(A: int32[10], B: int32[10]):
    for i in range(10):
        B[i] = A[i]

### SCHEDULE
s = allo.customize(kernel)
"""

# Mismo kernel, pero con una primitiva de compute customization aplicada
# (unroll). Primitivas de compute como esta deberían preservar la semántica
# -> se sigue esperando ok=True. Sirve para probar que L3 no da falsos
# negativos ante transformaciones legítimas.
CODIGO_CON_UNROLL = """\
### KERNEL
import allo
from allo.ir.types import int32

def kernel(A: int32[10], B: int32[10]):
    for i in range(10):
        B[i] = A[i]

### SCHEDULE
s = allo.customize(kernel)
s.unroll("i", 2)
"""


async def _llamar(codigo: str) -> dict:
    # NOTA: el decorador @tool(...) de claude_agent_sdk NO devuelve la
    # función async tal cual -- devuelve un objeto SdkMcpTool (dataclass)
    # cuyo campo .handler es la función async real que definimos. Por eso
    # no se puede invocar run_l3_equivalence(...) directamente; hay que
    # llamar a su atributo .handler.
    resultado = await run_l3_equivalence.handler({"codigo_allo": codigo})
    texto = resultado["content"][0]["text"]
    return json.loads(texto)


async def main():
    r1 = await _llamar(CODIGO_TRIVIAL)
    print(f"[Trivial] nivel={r1['nivel']} ok={r1['ok']} (esperado: True)")
    print(f"  salida_cruda: {r1['salida_cruda']}\n")

    r2 = await _llamar(CODIGO_CON_UNROLL)
    print(f"[Con unroll] nivel={r2['nivel']} ok={r2['ok']} (esperado: True)")
    print(f"  salida_cruda: {r2['salida_cruda']}\n")

    if r1["ok"] and r2["ok"]:
        print("✅ El wrapper run_l3_equivalence integra bien el parseo del "
              "Generador con allo.verify().")
    else:
        print("⚠️  Alguno de los dos casos esperados dio ok=False -- revisar "
              "salida_cruda para diagnosticar antes de fiarse de L3.")


if __name__ == "__main__":
    asyncio.run(main())
