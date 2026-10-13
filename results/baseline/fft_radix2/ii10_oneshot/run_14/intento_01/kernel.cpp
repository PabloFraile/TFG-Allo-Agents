// kernel.cpp
// FFT radix-2 (Cooley-Tukey, Decimation-In-Time) iterativa, N = 1024 puntos.
// Entrada: x_real/x_imag (orden natural). Salida: y_real/y_imag (orden natural).
//
// Algoritmo clásico: permutación bit-reversed de la entrada seguida de
// log2(N) = 10 etapas de mariposas radix-2, usando una tabla de factores de
// giro (twiddle factors) precalculada una sola vez por invocación.

#include "hls_math.h"

static const int N     = 1024;
static const int LOGN  = 10;   // log2(1024)
static const int NHALF = 512;  // N/2

static const float PI_F = 3.14159265358979323846f;

// Reversión de los 10 bits de un índice (0..1023).
static inline int bit_reverse10(int x) {
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
    float real_buf[N];
    float imag_buf[N];
    float tw_real[NHALF];
    float tw_imag[NHALF];

    // ------------------------------------------------------------------
    // 1) Permutación bit-reversed de la entrada hacia los buffers locales.
    // ------------------------------------------------------------------
PERM_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse10(i);
        real_buf[i] = x_real[r];
        imag_buf[i] = x_imag[r];
    }

    // ------------------------------------------------------------------
    // 2) Tabla de factores de giro W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1.
    //    Se calcula una sola vez; cada etapa accede a ella con un stride.
    // ------------------------------------------------------------------
TWIDDLE_LOOP:
    for (int k = 0; k < NHALF; k++) {
#pragma HLS PIPELINE II=1
        float angle = (-2.0f * PI_F * (float)k) / (float)N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // ------------------------------------------------------------------
    // 3) Etapas de mariposas radix-2 (DIT), en el propio buffer (in-place).
    //    Tras procesar todas las etapas el resultado queda en orden natural.
    // ------------------------------------------------------------------
STAGE_LOOP:
    for (int s = 0; s < LOGN; s++) {
#pragma HLS LOOP_TRIPCOUNT min=10 max=10
        int half_m = 1 << s;     // tamaño de la mitad de bloque en esta etapa
        int m      = half_m << 1;
        int stride = N / m;      // paso dentro de la tabla de twiddles

    BUTTERFLY_LOOP:
        for (int i = 0; i < NHALF; i++) {
#pragma HLS PIPELINE II=10
            int j     = i & (half_m - 1); // posición dentro de la mitad de bloque
            int block = i >> s;           // número de bloque (i / half_m)
            int k0    = block * m;        // índice base del bloque
            int idx1  = k0 + j;
            int idx2  = idx1 + half_m;
            int tidx  = j * stride;

            float wr = tw_real[tidx];
            float wi = tw_imag[tidx];

            float ur = real_buf[idx1];
            float ui = imag_buf[idx1];
            float vr = real_buf[idx2];
            float vi = imag_buf[idx2];

            float tr = wr * vr - wi * vi;
            float ti = wr * vi + wi * vr;

            real_buf[idx1] = ur + tr;
            imag_buf[idx1] = ui + ti;
            real_buf[idx2] = ur - tr;
            imag_buf[idx2] = ui - ti;
        }
    }

    // ------------------------------------------------------------------
    // 4) Volcado del resultado a las salidas.
    // ------------------------------------------------------------------
OUT_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
