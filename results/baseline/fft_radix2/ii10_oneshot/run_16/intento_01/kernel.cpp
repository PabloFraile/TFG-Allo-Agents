#include <hls_math.h>

#define FFT_N     1024
#define FFT_LOGN  10
#define FFT_HALF  (FFT_N / 2)

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// Reversa de los FFT_LOGN bits menos significativos de x (combinacional, totalmente desenrollado)
static inline int bit_reverse(int x, int bits) {
#pragma HLS INLINE
    int r = 0;
    for (int b = 0; b < bits; b++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1);
        x >>= 1;
    }
    return r;
}

void fft_radix2(
    const float x_real[FFT_N],
    const float x_imag[FFT_N],
    float y_real[FFT_N],
    float y_imag[FFT_N])
{
    float real_buf[FFT_N];
    float imag_buf[FFT_N];
    float Wr[FFT_HALF];
    float Wi[FFT_HALF];

    // 1. Precalculo de los factores de twiddle: W_N^k = exp(-2*pi*i*k/N)
    for (int k = 0; k < FFT_HALF; k++) {
#pragma HLS PIPELINE
        float angle = -2.0f * (float)M_PI * (float)k / (float)FFT_N;
        Wr[k] = hls::cosf(angle);
        Wi[k] = hls::sinf(angle);
    }

    // 2. Reordenacion bit-reversed de la entrada hacia los buffers locales
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE
        int ridx = bit_reverse(i, FFT_LOGN);
        real_buf[ridx] = x_real[i];
        imag_buf[ridx] = x_imag[i];
    }

    // 3. FFT radix-2 Cooley-Tukey iterativa (DIT), FFT_LOGN etapas de mariposas
    for (int stage = 0; stage < FFT_LOGN; stage++) {
        int half    = 1 << stage;               // tamano de cada mitad de grupo
        int tw_step = FFT_N >> (stage + 1);     // paso dentro de la tabla de twiddles

        for (int i = 0; i < FFT_HALF; i++) {
#pragma HLS PIPELINE
            int block = i >> stage;
            int pos   = i & (half - 1);
            int idx1  = (block << (stage + 1)) + pos;
            int idx2  = idx1 + half;
            int tw    = pos * tw_step;

            float wr = Wr[tw];
            float wi = Wi[tw];

            float xr1 = real_buf[idx1];
            float xi1 = imag_buf[idx1];
            float xr2 = real_buf[idx2];
            float xi2 = imag_buf[idx2];

            // Producto complejo: t = x2 * W
            float tr = xr2 * wr - xi2 * wi;
            float ti = xr2 * wi + xi2 * wr;

            // Mariposa: y1 = x1 + t ; y2 = x1 - t
            real_buf[idx1] = xr1 + tr;
            imag_buf[idx1] = xi1 + ti;
            real_buf[idx2] = xr1 - tr;
            imag_buf[idx2] = xi1 - ti;
        }
    }

    // 4. Escritura de resultados en las salidas
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
