// kernel.cpp
// Radix-2 Cooley-Tukey FFT (Decimation-In-Time), N = 1024, complex input/output.
// Forward transform: X[k] = sum_n x[n] * exp(-2*pi*i*k*n/N)  (matches numpy.fft.fft)
//
// Implementation: bit-reversal permutation into a local working buffer,
// followed by the standard iterative in-place DIT butterfly stages
// using a precomputed twiddle-factor table.

#include <hls_math.h>

#define FFT_N     1024
#define FFT_LOGN  10
#define FFT_NHALF 512

// Bit-reverse a FFT_LOGN-bit index. Small, fully unrolled.
static inline int bit_reverse(int x) {
#pragma HLS INLINE
    int r = 0;
BITREV_UNROLL:
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
    float tmp_real[FFT_N];
    float tmp_imag[FFT_N];

    float twiddle_real[FFT_NHALF];
    float twiddle_imag[FFT_NHALF];

    const float TWO_PI = 6.283185307179586f;

    // ---------------------------------------------------------------
    // Precompute twiddle factors: W_N^k = cos(2*pi*k/N) - i*sin(2*pi*k/N)
    // ---------------------------------------------------------------
TWIDDLE_LOOP:
    for (int k = 0; k < FFT_NHALF; k++) {
#pragma HLS PIPELINE II=1
        float angle = (TWO_PI * (float)k) / (float)FFT_N;
        twiddle_real[k] = hls::cosf(angle);
        twiddle_imag[k] = -hls::sinf(angle);
    }

    // ---------------------------------------------------------------
    // Bit-reversal permutation of the input into the working buffer
    // ---------------------------------------------------------------
BITREV_LOOP:
    for (int n = 0; n < FFT_N; n++) {
#pragma HLS PIPELINE II=1
#pragma HLS DEPENDENCE variable=tmp_real inter false
#pragma HLS DEPENDENCE variable=tmp_imag inter false
        int rn = bit_reverse(n);
        tmp_real[rn] = x_real[n];
        tmp_imag[rn] = x_imag[n];
    }

    // ---------------------------------------------------------------
    // Iterative in-place DIT butterfly stages
    // ---------------------------------------------------------------
STAGE_LOOP:
    for (int s = 0; s < FFT_LOGN; s++) {
        int half     = 1 << s;              // butterfly half-distance
        int halfMask = half - 1;
        int shiftAmt = FFT_LOGN - 1 - s;     // twStride = 2^shiftAmt

    BUTTERFLY_LOOP:
        for (int i = 0; i < FFT_NHALF; i++) {
#pragma HLS PIPELINE II=2
#pragma HLS DEPENDENCE variable=tmp_real inter false
#pragma HLS DEPENDENCE variable=tmp_imag inter false

            int group = i >> s;          // i / half
            int j     = i & halfMask;    // i % half

            int idx1 = (group << (s + 1)) + j; // group*step + j, step = half*2
            int idx2 = idx1 + half;

            int tIdx = j << shiftAmt;    // j * (N/step)

            float tr = twiddle_real[tIdx];
            float ti = twiddle_imag[tIdx];

            float ar = tmp_real[idx1];
            float ai = tmp_imag[idx1];
            float br = tmp_real[idx2];
            float bi = tmp_imag[idx2];

            float tre = br * tr - bi * ti;
            float tim = br * ti + bi * tr;

            tmp_real[idx1] = ar + tre;
            tmp_imag[idx1] = ai + tim;
            tmp_real[idx2] = ar - tre;
            tmp_imag[idx2] = ai - tim;
        }
    }

    // ---------------------------------------------------------------
    // Write result (natural order, since input was bit-reversed first)
    // ---------------------------------------------------------------
OUTPUT_LOOP:
    for (int n = 0; n < FFT_N; n++) {
#pragma HLS PIPELINE II=1
        y_real[n] = tmp_real[n];
        y_imag[n] = tmp_imag[n];
    }
}
