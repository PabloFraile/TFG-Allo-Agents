"""
Prueba de NIVEL 1: llama a allo.verify() directamente, sin pasar por
run_l3_equivalence ni por el resto del pipeline. Objetivo: confirmar que la
propia librería Allo distingue correctamente entre schedules equivalentes y
no equivalentes, antes de fiarnos de nuestro wrapper.

Ejecutar desde src/agentes/ (o ajustar el import de 'allo' si hace falta):
    python3 test_l3_directo.py
"""

import allo
from allo.ir.types import int32


# --- Caso A: mismo schedule comparado consigo mismo -> se espera True ---
# Es la prueba más básica posible: si esto no da True, algo está mal
# configurado en el entorno, no en tu lógica de negocio.

def kernel_copia(A: int32[10], B: int32[10]):
    for i in range(10):
        B[i] = A[i]


def test_identico_da_true():
    s_orig = allo.customize(kernel_copia)
    s = allo.customize(kernel_copia)
    ok = allo.verify(s, s_orig)
    print(f"[Caso A] mismo kernel sin transformar -> allo.verify = {ok!r} "
          f"(esperado: valor truthy, p. ej. 1)")
    # NOTA: allo.verify() devuelve 1/0 (o similar), no el booleano True/False
    # de Python -- por eso comparamos con bool(ok) en vez de "is True".
    assert bool(ok) is True, "Un schedule comparado consigo mismo debería ser equivalente"


# --- Caso B: dos kernels con la MISMA firma pero semántica distinta ---
# Esto no es "un schedule que rompe la semántica" (el escenario real que L3
# protege), pero sirve para confirmar que allo.verify() SÍ es capaz de
# detectar una diferencia real y no da siempre True por defecto.

def kernel_suma(A: int32[10], B: int32[10]):
    for i in range(10):
        B[i] = A[i] + 1  # <-- semántica distinta a kernel_copia


def test_diferente_da_false():
    s_orig = allo.customize(kernel_copia)
    s_bug = allo.customize(kernel_suma)
    ok = allo.verify(s_bug, s_orig)
    print(f"[Caso B] kernels con semántica distinta -> allo.verify = {ok!r} "
          f"(esperado: valor falsy, p. ej. 0)")
    assert bool(ok) is False, "Dos kernels con semántica distinta no deberían ser equivalentes"


if __name__ == "__main__":
    test_identico_da_true()
    test_diferente_da_false()
    print("\n✅ allo.verify() distingue correctamente equivalente / no-equivalente.")
