#include "hls_math.h"

#define FFT_N 1024
#define FFT_LOGN 10

// Synthesizable 10-bit bit-reversal (used for decimation-in-time reordering)
static int bit_reverse10(int x) {
#pragma HLS INLINE
    int r = 0;
    for (int b = 0; b < FFT_LOGN; b++) {
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
    float twr[FFT_N / 2];
    float twi[FFT_N / 2];

    const float PI = 3.14159265358979323846f;

    // ---------------------------------------------------------------
    // Precompute twiddle factors once: W_N^k = exp(-2*pi*i*k/N)
    // for k = 0 .. N/2-1 (covers every twiddle needed by every stage)
    // ---------------------------------------------------------------
    twiddle_loop:
    for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II=10
        float angle = (-2.0f * PI * (float)k) / (float)FFT_N;
        twr[k] = hls::cosf(angle);
        twi[k] = hls::sinf(angle);
    }

    // ---------------------------------------------------------------
    // Bit-reversal permutation of the input samples into local buffers
    // ---------------------------------------------------------------
    bitrev_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int ri = bit_reverse10(i);
        real[i] = x_real[ri];
        imag[i] = x_imag[ri];
    }

    // ---------------------------------------------------------------
    // Iterative Cooley-Tukey radix-2 decimation-in-time FFT.
    // Stage loop runs sequentially (in-place update, stage s+1 depends
    // on stage s), only the inner butterfly loop is pipelined.
    // All index arithmetic uses shifts/masks (half_m, strides are
    // powers of two) to avoid synthesizing dividers.
    // ---------------------------------------------------------------
    stage_loop:
    for (int s = 0; s < FFT_LOGN; s++) {
        int half_m   = 1 << s;              // m/2 for this stage
        int mask     = half_m - 1;
        int tw_shift = FFT_LOGN - 1 - s;    // twiddle index = j << tw_shift

        butterfly_loop:
        for (int idx = 0; idx < FFT_N / 2; idx++) {
#pragma HLS PIPELINE II=10
            int j     = idx & mask;
            int group = idx >> s;
            int k     = group << (s + 1);
            int idx1  = k + j;
            int idx2  = idx1 + half_m;
            int twidx = j << tw_shift;

            float wr = twr[twidx];
            float wi = twi[twidx];

            float xr2 = real[idx2];
            float xi2 = imag[idx2];
            float xr1 = real[idx1];
            float xi1 = imag[idx1];

            float tr = wr * xr2 - wi * xi2;
            float ti = wr * xi2 + wi * xr2;

            real[idx1] = xr1 + tr;
            imag[idx1] = xi1 + ti;
            real[idx2] = xr1 - tr;
            imag[idx2] = xi1 - ti;
        }
    }

    // ---------------------------------------------------------------
    // Write results out
    // ---------------------------------------------------------------
    output_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real[i];
        y_imag[i] = imag[i];
    }
}
