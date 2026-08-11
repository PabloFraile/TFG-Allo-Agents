"""
Prueba de la mejora: confirmar que run_l3_equivalence() ya no se limita a
decir "revisa la salida/logs" cuando falla, sino que captura el diagnóstico
real de PAST (el verificador formal de Allo) en salida_cruda.

Ejecutar desde src/agentes/:
    python3 test_l3_captura_diff.py
"""

import asyncio
import json

from allo_tools import run_l3_equivalence


# Kernel "correcto" en el bloque KERNEL (copia simple). El bloque SCHEDULE,
# en vez de transformar ESE kernel, escribe su propia función con semántica
# distinta (+1) A DISCO -- igual que hace _cargar_kernel_desde_disco() en
# allo_tools.py -- y la customiza desde ahí. Es necesario escribirla a
# disco porque allo.customize() usa inspect.getsource() internamente, que
# no funciona con funciones definidas vía exec() en memoria (esto ya está
# documentado en allo_tools.py; lo confirmamos aquí de la peor manera --
# con un OSError: could not get source code -- al intentarlo sin pasar por
# disco). Esto no es una primitiva real de Allo rompiendo un schedule, mero
# truco de test, pero fuerza un s genuinamente distinto de s_orig, que es
# lo único que hace falta para ejercitar el camino ok=False del wrapper.
CODIGO_KERNEL_ROTO = """\
### KERNEL
import allo
from allo.ir.types import int32

def kernel(A: int32[10], B: int32[10]):
    for i in range(10):
        B[i] = A[i]

### SCHEDULE
import os as _os
import tempfile as _tempfile
import importlib.util as _importlib_util

_codigo_bug = (
    "import allo\\n"
    "from allo.ir.types import int32\\n"
    "\\n"
    "def kernel_bug(A: int32[10], B: int32[10]):\\n"
    "    for i in range(10):\\n"
    "        B[i] = A[i] + 1\\n"
)
_dir = _tempfile.mkdtemp(prefix="kernel_bug_")
_ruta = _os.path.join(_dir, "kernel_bug.py")
with open(_ruta, "w") as _f:
    _f.write(_codigo_bug)

_spec = _importlib_util.spec_from_file_location("kernel_bug_mod", _ruta)
_mod = _importlib_util.module_from_spec(_spec)
_spec.loader.exec_module(_mod)

s = allo.customize(_mod.kernel_bug)
"""


async def main():
    resultado = await run_l3_equivalence.handler({"codigo_allo": CODIGO_KERNEL_ROTO})
    datos = json.loads(resultado["content"][0]["text"])

    print(f"nivel={datos['nivel']} ok={datos['ok']} (esperado: False)\n")
    print("salida_cruda:")
    print(datos["salida_cruda"])

    contiene_diagnostico = any(
        marcador in datos["salida_cruda"]
        for marcador in ("Mismatch", "First difference", "NOT equivalent", "Diagnóstico de PAST")
    )

    if datos["ok"] is False and contiene_diagnostico:
        print("\n✅ salida_cruda contiene el diagnóstico real de PAST, no solo ok=False.")
    else:
        print("\n⚠️  salida_cruda NO parece contener el diagnóstico esperado -- revisar la captura de stdout.")


if __name__ == "__main__":
    asyncio.run(main())
