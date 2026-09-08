"""
Reproduce de forma aislada el ValueError visto repetidamente en L2 al
llamar a s.partition() sobre un array 1D -- para ver el traceback COMPLETO
real de Python (no el resumen recortado y parafraseado que ve el
Validador), y así confirmar si el problema está en partition() en sí.
"""

import allo
from allo.ir.types import float32
from allo.customize import Partition


def kernel(x_real: float32[1024], y_real: float32[1024]):
    for i in range(1024):
        y_real[i] = x_real[i]


s = allo.customize(kernel)

print("Probando s.partition('x_real', ...) -- formato viejo, sabemos que falla:")
try:
    s.partition("x_real", partition_type=Partition.Complete)
    print("OK (inesperado)")
except ValueError as e:
    print(f"Falló como se esperaba: {e}")

print()
print("Probando s.partition('kernel:x_real', ...) -- formato 'funcion:buffer':")
s.partition("kernel:x_real", partition_type=Partition.Complete)
print("OK -- si ves esto, el formato 'kernel:x_real' es el correcto.")
