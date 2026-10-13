#include <cmath>

// -----------------------------------------------------------------------
// fft_radix2
//
// FFT iterativa radix-2 Cooley-Tukey (decimation-in-time), N = 1024
// puntos, entrada/salida compleja en orden natural (compatible con la
// convencion de numpy.fft.fft: X[k] = sum_n x[n] * exp(-2j*pi*k*n/N)).
//
// Algoritmo:
//   1) Reordenamiento bit-reversal de la entrada hacia un buffer interno.
//   2) log2(N) = 10 etapas de mariposas radix-2 in-place.
//   3) Copia del resultado (ya en orden natural) a las salidas.
//
// Los twiddle factors se calculan "on the fly" con std::cos/std::sin
// (sintetizables en Vitis HLS como nucleos de coma flotante en pipeline),
// evitando divisiones en tiempo de ejecucion mediante una constante
// precalculada (-2*pi/N) y desplazamientos de bits para N/m.
//
// Los buffers internos se particionan por completo para permitir acceso
// simultaneo a las dos posiciones de cada mariposa (idx1, idx2) y así
// alcanzar II=1 (<=10 exigido) en los tres bucles pipelineados.
// -----------------------------------------------------------------------
void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    const int N    = 1024;
    const int LOGN = 10;

    // Factor de escala: -2*pi/N, precalculado para evitar divisiones
    // en tiempo de ejecucion dentro del bucle de mariposas.
    const float TWO_PI_OVER_N_NEG = -6.28318530717958647692f / 1024.0f;

    float data_real[1024];
    float data_imag[1024];
#pragma HLS ARRAY_PARTITION variable=data_real complete dim=1
#pragma HLS ARRAY_PARTITION variable=data_imag complete dim=1

    // -------------------------------------------------------------
    // 1) Carga con reordenamiento bit-reversal
    // -------------------------------------------------------------
bitrev_load:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int r  = 0;
        int ii = i;
        for (int b = 0; b < LOGN; b++) {
            r = (r << 1) | (ii & 1);
            ii >>= 1;
        }
        data_real[i] = x_real[r];
        data_imag[i] = x_imag[r];
    }

    // -------------------------------------------------------------
    // 2) Etapas de mariposas radix-2 (Cooley-Tukey, DIT)
    // -------------------------------------------------------------
stage_loop:
    for (int s = 1; s <= LOGN; s++) {
        const int m      = 1 << s;          // tamano de sub-FFT en esta etapa
        const int half_m = m >> 1;          // mitad del tamano de sub-FFT
        const int step   = 1 << (LOGN - s); // N / m, via shift (sin division)

        int k = 0; // indice de inicio de bloque (multiplo de m)
        int j = 0; // indice dentro del medio-bloque [0, half_m)

    butterfly_loop:
        for (int t = 0; t < N / 2; t++) {
#pragma HLS PIPELINE II=1
            const int idx1 = k + j;
            const int idx2 = idx1 + half_m;

            // Angulo del twiddle factor: theta = -2*pi*(j*step)/N
            const float theta = TWO_PI_OVER_N_NEG * (float)(j * step);
            const float wr = std::cos(theta);
            const float wi = std::sin(theta);

            const float xr2 = data_real[idx2];
            const float xi2 = data_imag[idx2];

            // T = W * data[idx2]  (complejo)
            const float tr = xr2 * wr - xi2 * wi;
            const float ti = xr2 * wi + xi2 * wr;

            const float xr1 = data_real[idx1];
            const float xi1 = data_imag[idx1];

            data_real[idx1] = xr1 + tr;
            data_imag[idx1] = xi1 + ti;
            data_real[idx2] = xr1 - tr;
            data_imag[idx2] = xi1 - ti;

            j++;
            if (j == half_m) {
                j = 0;
                k += m;
            }
        }
    }

    // -------------------------------------------------------------
    // 3) Escritura de resultados (orden natural)
    // -------------------------------------------------------------
store_output:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = data_real[i];
        y_imag[i] = data_imag[i];
    }
}
