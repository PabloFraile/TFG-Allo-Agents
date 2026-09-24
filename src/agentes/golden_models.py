"""
Golden models de referencia (NumPy puro) contra los que el nivel L2 compara
la salida funcional del kernel Allo generado.

Hasta ahora `golden_model_id` viajaba por el pipeline como un simple string
sin nada detrás. Este módulo es lo que le da contenido real: un diccionario
id -> función callable que el Ejecutor usa para comparar.
"""

import numpy as np


def fft_numpy_reference(x_real: np.ndarray, x_imag: np.ndarray):
    """Referencia: FFT completa vía np.fft.fft sobre la señal compleja
    reconstruida a partir de sus partes real e imaginaria por separado.

    Devuelve (y_real, y_imag) como arrays float32, en el mismo formato de
    E/S que se espera del kernel Allo generado (que no puede usar complex64
    nativo si el subconjunto restringido del DSL no lo soporta).

    Renombrada desde 'fft_radix2_numpy_reference' (24 de septiembre de
    2026): el nombre anterior sugería que la referencia era específica de
    radix-2, pero es completamente agnóstica al radix -- es np.fft.fft sin
    más, así que L2 pasa igual de bien con un kernel radix-2, radix-4 o
    cualquier otra descomposición que calcule la FFT correcta. El nombre
    anterior confundía al propio LLM Validador, que llegó a describir un
    kernel radix-4 como "el kernel FFT radix-2" en su informe (ver spec
    fft_radix4.yaml, prueba de generalización). Los resultados guardados
    antes de este cambio (results/catalogo/*.json, docs/bitacora.md) siguen
    citando el id antiguo tal cual se usó entonces -- no se han reescrito,
    son evidencia histórica.
    """
    x = x_real.astype(np.float64) + 1j * x_imag.astype(np.float64)
    y = np.fft.fft(x)
    return y.real.astype(np.float32), y.imag.astype(np.float32)


# Registro de golden models disponibles, indexado por el mismo id que
# aparece en los specs (`golden_model_id: fft_numpy_reference`)
GOLDEN_MODELS = {
    "fft_numpy_reference": fft_numpy_reference,
}


def generar_vectores_test(forma: tuple = (1024,), seed: int = 0):
    """Genera un par (x_real, x_imag) determinista (misma seed = mismos
    vectores en cada iteración, para que los fallos de L2 sean reproducibles
    y comparables entre iteraciones del bucle)."""
    rng = np.random.default_rng(seed)
    x_real = rng.standard_normal(forma).astype(np.float32)
    x_imag = rng.standard_normal(forma).astype(np.float32)
    return x_real, x_imag
