// kernel.cpp
// FFT radix-2 (Cooley-Tukey, Decimation-In-Time, iterativa) de N=1024 puntos.
// Implementada como una secuencia de "mariposas" radix-2 sobre arrays locales,
// con reordenado bit-reversal de la entrada y tabla de twiddle factors.

#include "hls_math.h"

static const int N    = 1024;
static const int LOGN = 10; // log2(1024)

// Inversion de bits de 'x' usando LOGN bits (combinacional, totalmente desenrollado)
static inline int bit_reverse(int x) {
#pragma HLS INLINE
    int r = 0;
    for (int i = 0; i < LOGN; i++) {
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
    float real[N];
    float imag[N];
    float tw_real[N / 2];
    float tw_imag[N / 2];

#pragma HLS BIND_STORAGE variable=real    type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=imag    type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=tw_real type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=tw_imag type=ram_1p impl=bram

    // 1) Reordenado bit-reversal de la entrada hacia los buffers de trabajo
    bitrev_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse(i);
        real[r] = x_real[i];
        imag[r] = x_imag[i];
    }

    // 2) Tabla de twiddle factors: W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1
    const float two_pi = 6.28318530717958647692f;
    twiddle_loop:
    for (int k = 0; k < N / 2; k++) {
#pragma HLS PIPELINE II=1
        float angle = -two_pi * (float)k / (float)N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // 3) Etapas de mariposas radix-2 (Cooley-Tukey DIT, in-place)
    stage_loop:
    for (int s = 1; s <= LOGN; s++) {
        int m    = 1 << s;   // tamano de sub-FFT en esta etapa
        int half = m >> 1;   // mitad del tamano -> numero de mariposas por bloque
        int step = N / m;    // paso en la tabla de twiddle

        butterfly_loop:
        for (int i = 0; i < N / 2; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT min=512 max=512
            int k = (i / half) * m;
            int j = i % half;

            int idx0   = k + j;
            int idx1   = idx0 + half;
            int tw_idx = j * step;

            float wr = tw_real[tw_idx];
            float wi = tw_imag[tw_idx];

            float xr1 = real[idx1];
            float xi1 = imag[idx1];

            float tr = xr1 * wr - xi1 * wi;
            float ti = xr1 * wi + xi1 * wr;

            float xr0 = real[idx0];
            float xi0 = imag[idx0];

            real[idx0] = xr0 + tr;
            imag[idx0] = xi0 + ti;
            real[idx1] = xr0 - tr;
            imag[idx1] = xi0 - ti;
        }
    }

    // 4) Escritura del resultado (orden natural) en las salidas
    output_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real[i];
        y_imag[i] = imag[i];
    }
}
