#include "hls_math.h"

// ---------------------------------------------------------------------------
// FFT radix-2 (Cooley-Tukey, decimation in time), N = 1024 puntos
// Implementa una FFT completa iterativa in-place:
//   1) tabla de factores "twiddle" W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1
//   2) reordenado bit-reversed de la entrada
//   3) log2(N) etapas de mariposas radix-2
//   4) copia del resultado a las salidas
// ---------------------------------------------------------------------------

static const int N    = 1024;
static const int LOGN = 10;     // log2(1024)
static const float TWO_PI = 6.28318530717958647692f;

// Inversión de los 10 bits de un índice (0..1023) -> usada para el
// reordenado bit-reversed de la entrada. Se sintetiza como lógica
// combinacional (totalmente desenrollada e inlineada).
static inline int bit_reverse10(int x)
{
#pragma HLS INLINE
    int r = 0;
    for (int b = 0; b < LOGN; b++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1);
        x >>= 1;
    }
    return r;
}

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024])
{
    // Buffers locales de trabajo (BRAM)
    float xr[N];
    float xi[N];

    // Tabla de factores twiddle: W_N^k para k = 0 .. N/2-1
    float tw_real[N / 2];
    float tw_imag[N / 2];

    // ---------------------------------------------------------------
    // 1) Cálculo de la tabla de twiddles
    // ---------------------------------------------------------------
    for (int k = 0; k < N / 2; k++) {
#pragma HLS PIPELINE II=1
        float angle = -TWO_PI * (float)k / (float)N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // ---------------------------------------------------------------
    // 2) Reordenado bit-reversed de la entrada hacia los buffers locales
    // ---------------------------------------------------------------
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse10(i);
        xr[i] = x_real[r];
        xi[i] = x_imag[r];
    }

    // ---------------------------------------------------------------
    // 3) Etapas de mariposas radix-2 (Cooley-Tukey, DIT)
    // ---------------------------------------------------------------
    for (int s = 0; s < LOGN; s++) {
        int half_m    = 1 << s;              // m/2 de la etapa actual
        int mask      = half_m - 1;          // para extraer j = i mod half_m
        int tw_stride = (N / 2) >> s;         // paso en la tabla de twiddles

        for (int i = 0; i < N / 2; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS DEPENDENCE variable=xr inter false
#pragma HLS DEPENDENCE variable=xi inter false

            int j     = i & mask;
            int k     = (i >> s) << (s + 1);
            int idx1  = k + j;
            int idx2  = idx1 + half_m;
            int twIdx = j * tw_stride;

            float tr = tw_real[twIdx];
            float ti = tw_imag[twIdx];

            float ur = xr[idx1];
            float ui = xi[idx1];
            float vr = xr[idx2];
            float vi = xi[idx2];

            // producto complejo: p = (tr + j*ti) * (vr + j*vi)
            float pr = vr * tr - vi * ti;
            float pi_ = vr * ti + vi * tr;

            xr[idx1] = ur + pr;
            xi[idx1] = ui + pi_;
            xr[idx2] = ur - pr;
            xi[idx2] = ui - pi_;
        }
    }

    // ---------------------------------------------------------------
    // 4) Escritura del resultado en las salidas
    // ---------------------------------------------------------------
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = xr[i];
        y_imag[i] = xi[i];
    }
}
