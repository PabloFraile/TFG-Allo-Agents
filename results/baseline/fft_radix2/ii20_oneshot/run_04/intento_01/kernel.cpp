#include <hls_math.h>

// ---------------------------------------------------------------------
// Kernel: FFT radix-2 (Cooley-Tukey, decimation in tiempo), N = 1024
// Entrada/Salida: vectores de 1024 floats (parte real e imaginaria)
// ---------------------------------------------------------------------

#define FFT_N     1024
#define FFT_LOGN  10
#define FFT_HALF  (FFT_N / 2)
#define FFT_PI    3.14159265358979323846f

// Inversion de bits de un indice de FFT_LOGN bits (totalmente desenrollado)
static int bit_reverse(int x, int bits) {
#pragma HLS INLINE
    int r = 0;
    for (int i = 0; i < bits; i++) {
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
    float y_imag[1024]
) {
    float real[FFT_N];
    float imag[FFT_N];
    float wn_real[FFT_HALF];
    float wn_imag[FFT_HALF];

    // -------------------------------------------------------------
    // 1) Precalculo de los factores de giro (twiddle factors)
    //    wn[k] = exp(-2*pi*i*k / N)   k = 0 .. N/2-1
    // -------------------------------------------------------------
    TWIDDLE_LOOP:
    for (int k = 0; k < FFT_HALF; k++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * FFT_PI * (float)k / (float)FFT_N;
        wn_real[k] = hls::cosf(angle);
        wn_imag[k] = hls::sinf(angle);
    }

    // -------------------------------------------------------------
    // 2) Permutacion por inversion de bits (reordenamiento de entrada)
    // -------------------------------------------------------------
    BITREV_LOOP:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int ridx = bit_reverse(i, FFT_LOGN);
        real[i] = x_real[ridx];
        imag[i] = x_imag[ridx];
    }

    // -------------------------------------------------------------
    // 3) Etapas iterativas de mariposas radix-2 (Cooley-Tukey, DIT)
    // -------------------------------------------------------------
    STAGE_LOOP:
    for (int s = 1; s <= FFT_LOGN; s++) {
        int shift = s - 1;          // log2(half)
        int half  = 1 << shift;     // m/2
        int mstep = FFT_N >> s;     // N/m -> paso en la tabla de twiddles

        BUTTERFLY_LOOP:
        for (int f = 0; f < FFT_HALF; f++) {
#pragma HLS PIPELINE II=1
            int group = f >> shift;
            int pos   = f & (half - 1);
            int k     = group << s;
            int idx0  = k + pos;
            int idx1  = idx0 + half;
            int tw_idx = pos * mstep;

            float ar = real[idx0];
            float ai = imag[idx0];
            float br = real[idx1];
            float bi = imag[idx1];
            float wr = wn_real[tw_idx];
            float wi = wn_imag[tw_idx];

            float tr = br * wr - bi * wi;
            float ti = br * wi + bi * wr;

            real[idx0] = ar + tr;
            imag[idx0] = ai + ti;
            real[idx1] = ar - tr;
            imag[idx1] = ai - ti;
        }
    }

    // -------------------------------------------------------------
    // 4) Escritura del resultado
    // -------------------------------------------------------------
    OUT_LOOP:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real[i];
        y_imag[i] = imag[i];
    }
}
