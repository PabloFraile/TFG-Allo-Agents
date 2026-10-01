"""
Golden models de referencia (NumPy puro) contra los que el nivel L2 compara
la salida funcional del kernel Allo generado.

Este módulo le da contenido real al campo `golden_model_id` del spec de
cada bloque: un diccionario id -> función callable que el Ejecutor usa
para comparar.
"""

import numpy as np


def fft_numpy_reference(x_real: np.ndarray, x_imag: np.ndarray):
    """Referencia: FFT completa vía np.fft.fft sobre la señal compleja
    reconstruida a partir de sus partes real e imaginaria por separado.

    Devuelve (y_real, y_imag) como arrays float32, en el mismo formato de
    E/S que se espera del kernel Allo generado (que no puede usar complex64
    nativo si el subconjunto restringido del DSL no lo soporta).

    Es agnóstica al radix: compara solo el resultado numérico final de la
    FFT, no la descomposición algorítmica interna del kernel. Un kernel
    radix-2, radix-4 o con cualquier otra estrategia que calcule la FFT
    correcta pasa L2 igual de bien contra esta misma referencia.
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
