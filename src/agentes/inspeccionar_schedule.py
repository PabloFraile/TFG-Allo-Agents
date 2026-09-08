"""
Inspecciona la API real del objeto Schedule de tu instalación de Allo --
mismo espíritu que ya hicisteis con `help(allo.verify)` para L3.

Usa un kernel mínimo escrito en un .py real (no una lambda ni -c), porque
allo.customize() necesita inspect.getsource() para funcionar, y eso
requiere un archivo real en disco -- el mismo problema que ya documentasteis
para _cargar_kernel_desde_disco().
"""

import allo
from allo.ir.types import int32


def kernel(x: int32[16], y: int32[16]):
    for i in range(16):
        y[i] = x[i]


s = allo.customize(kernel)

print("=== Métodos disponibles en Schedule ===")
print([m for m in dir(s) if not m.startswith("_")])
print()
print("=== help(s.pipeline) ===")
help(s.pipeline)
print()
print("=== help(s.partition) ===")
help(s.partition)
print()
print("=== help(s.unroll) (si existe) ===")
if hasattr(s, "unroll"):
    help(s.unroll)
else:
    print("No existe el método 'unroll' en Schedule.")
