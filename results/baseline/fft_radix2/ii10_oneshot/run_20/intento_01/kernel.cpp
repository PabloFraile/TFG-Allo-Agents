//------------------------------------------------------------------------
// fft_radix2 : FFT Cooley-Tukey radix-2, decimation-in-time, N = 1024
// Entrada  : x_real[1024], x_imag[1024]
// Salida   : y_real[1024], y_imag[1024]
// Objetivo : II <= 10 en todos los bucles pipelineados (xcu280, 3.33 ns)
//------------------------------------------------------------------------
#include "hls_math.h"

#define N      1024
#define LOG2N  10
#define NH     (N/2)

static const float PI_F = 3.14159265358979323846f;

// Reversion de LOG2N bits (completamente desenrollado, coste trivial)
static inline int bit_reverse(int x) {
#pragma HLS INLINE
    int result = 0;
BITREV_BITS:
    for (int i = 0; i < LOG2N; i++) {
#pragma HLS UNROLL
        result = (result << 1) | (x & 1);
        x >>= 1;
    }
    return result;
}

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    // Buffers internos de trabajo (in-place entre etapas)
    float buf_re[N];
    float buf_im[N];

    // Tabla de factores de giro W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1
    float tw_re[NH];
    float tw_im[NH];

#pragma HLS BIND_STORAGE variable=buf_re type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=buf_im type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=tw_re  type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=tw_im  type=ram_1p impl=bram

    // ------------------------------------------------------------------
    // 1) Calculo de la tabla de factores de giro (tamaño fijo N/2)
    // ------------------------------------------------------------------
TWIDDLE_LOOP:
    for (int k = 0; k < NH; k++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * PI_F * (float)k / (float)N;
        tw_re[k] = hls::cosf(angle);
        tw_im[k] = hls::sinf(angle);
    }

    // ------------------------------------------------------------------
    // 2) Permutacion bit-reversed de la entrada hacia el buffer interno
    // ------------------------------------------------------------------
BITREV_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse(i);
        buf_re[i] = x_real[r];
        buf_im[i] = x_imag[r];
    }

    // ------------------------------------------------------------------
    // 3) LOG2N etapas de mariposas radix-2 (Cooley-Tukey, DIT)
    //    Cada etapa recorre exactamente N/2 mariposas usando solo
    //    desplazamientos/mascaras (potencias de 2), sin divisiones.
    // ------------------------------------------------------------------
STAGE_LOOP_OUTER:
    for (int s = 1; s <= LOG2N; s++) {
        const int half  = 1 << (s - 1);   // tamaño de la mitad de bloque
        const int shift = LOG2N - s;      // paso en la tabla de twiddles

    STAGE_LOOP_INNER:
        for (int k = 0; k < NH; k++) {
#pragma HLS PIPELINE II=1
#pragma HLS DEPENDENCE variable=buf_re inter false
#pragma HLS DEPENDENCE variable=buf_im inter false

            int group = k >> (s - 1);
            int j     = k & (half - 1);
            int idx1  = (group << s) | j;
            int idx2  = idx1 + half;
            int twIdx = j << shift;

            float wr = tw_re[twIdx];
            float wi = tw_im[twIdx];

            float ar = buf_re[idx1];
            float ai = buf_im[idx1];
            float br = buf_re[idx2];
            float bi = buf_im[idx2];

            // t = b * w  (multiplicacion compleja)
            float tr = br * wr - bi * wi;
            float ti = br * wi + bi * wr;

            // mariposa: a' = a + t ; b' = a - t
            buf_re[idx1] = ar + tr;
            buf_im[idx1] = ai + ti;
            buf_re[idx2] = ar - tr;
            buf_im[idx2] = ai - ti;
        }
    }

    // ------------------------------------------------------------------
    // 4) Escritura del resultado final
    // ------------------------------------------------------------------
OUT_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = buf_re[i];
        y_imag[i] = buf_im[i];
    }
}
