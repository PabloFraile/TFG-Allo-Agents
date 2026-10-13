// kernel.cpp
// FFT radix-2 (Cooley-Tukey, decimation in time), N = 1024, iterativa.
// Firma impuesta por el testbench.

#include <hls_math.h>

#define FFT_N     1024
#define FFT_LOGN  10

static const float FFT_PI = 3.14159265358979323846f;

// Inversion de bits de 10 bits (log2(1024)) totalmente desenrollada:
// se usa dentro de un bucle pipelineado, por lo que debe resolverse
// de forma puramente combinacional (sin recursos secuenciales extra).
static int bit_reverse10(int x) {
#pragma HLS INLINE
    int result = 0;
    for (int i = 0; i < FFT_LOGN; i++) {
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
    float y_imag[1024])
{
    // Buffers de trabajo internos (BRAM) y tabla de factores de giro (twiddles).
    float real_buf[FFT_N];
    float imag_buf[FFT_N];
    float tw_real[FFT_N / 2];
    float tw_imag[FFT_N / 2];

    // -----------------------------------------------------------------
    // 1) Reordenado bit-reversal de la entrada hacia los buffers internos
    // -----------------------------------------------------------------
    bitrev_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse10(i);
        real_buf[i] = x_real[r];
        imag_buf[i] = x_imag[r];
    }

    // -----------------------------------------------------------------
    // 2) Tabla de factores de giro W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1
    //    (convencion de FFT directa, compatible con numpy.fft.fft)
    // -----------------------------------------------------------------
    tw_loop:
    for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * FFT_PI * (float)k / (float)FFT_N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // -----------------------------------------------------------------
    // 3) Etapas iterativas de mariposas radix-2 (Cooley-Tukey, DIT)
    //    Todas las divisiones/multiplicaciones por potencias de 2 se
    //    implementan como desplazamientos/mascaras para facilitar un
    //    II bajo en el bucle interno.
    // -----------------------------------------------------------------
    stage_loop:
    for (int s = 1; s <= FFT_LOGN; s++) {
        const int shift    = s - 1;          // log2(half_m)
        const int half_m   = 1 << shift;     // tamano medio de sub-FFT
        const int tw_shift = FFT_LOGN - s;   // log2(step) del twiddle

        butterfly_loop:
        for (int idx = 0; idx < FFT_N / 2; idx++) {
#pragma HLS PIPELINE II=1
            int k      = (idx >> shift) << (shift + 1);
            int j      = idx & (half_m - 1);
            int tw_idx = j << tw_shift;

            int idx1 = k + j;
            int idx2 = idx1 + half_m;

            float wr = tw_real[tw_idx];
            float wi = tw_imag[tw_idx];

            float xr2 = real_buf[idx2];
            float xi2 = imag_buf[idx2];

            // producto complejo: (xr2 + j*xi2) * (wr + j*wi)
            float tr = xr2 * wr - xi2 * wi;
            float ti = xr2 * wi + xi2 * wr;

            float xr1 = real_buf[idx1];
            float xi1 = imag_buf[idx1];

            real_buf[idx1] = xr1 + tr;
            imag_buf[idx1] = xi1 + ti;
            real_buf[idx2] = xr1 - tr;
            imag_buf[idx2] = xi1 - ti;
        }
    }

    // -----------------------------------------------------------------
    // 4) Escritura del resultado final
    // -----------------------------------------------------------------
    out_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
