// kernel.cpp
// Radix-2 Cooley-Tukey FFT (Decimation-In-Time, iterative, in-place via
// ping-pong buffering) for N = 1024 complex points.
//
// Algorithm:
//   1) Bit-reverse the input ordering while loading into buffer A.
//   2) Run log2(N) = 10 butterfly stages, alternating between two full
//      buffers (A/B) each stage so that every stage reads one memory and
//      writes the other -> no read/write port conflicts, full II=1
//      pipelining of every butterfly loop (well under the II<=20 budget).
//   3) After 10 (even) stages the result lands back in buffer A, in
//      natural (non bit-reversed) order; copy it to the outputs.
//
// Twiddle factors W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1, are computed once
// per call with the HLS floating point sin/cos cores (hls_math.h).

#include "hls_math.h"

#define FFT_N    1024
#define FFT_LOGN 10

// One radix-2 DIT butterfly stage. S is a compile-time stage index
// (0 .. FFT_LOGN-1), so half_m/shift_t/mask collapse to constants and all
// index arithmetic becomes pure shifts/masks.
template <int S>
static void fft_stage(const float src_real[FFT_N], const float src_imag[FFT_N],
                       float dst_real[FFT_N], float dst_imag[FFT_N],
                       const float tw_real[FFT_N / 2], const float tw_imag[FFT_N / 2]) {
#pragma HLS INLINE
    const int half_m  = 1 << S;
    const int shift_t = FFT_LOGN - 1 - S;
    const int mask    = half_m - 1;

FFT_BUTTERFLY:
    for (int idx = 0; idx < FFT_N / 2; idx++) {
#pragma HLS PIPELINE II = 1
        int j = idx & mask;
        int k = (idx >> S) << (S + 1);
        int t = j << shift_t;

        int idx1 = k + j;
        int idx2 = idx1 + half_m;

        float wr = tw_real[t];
        float wi = tw_imag[t];

        float ur = src_real[idx1];
        float ui = src_imag[idx1];
        float vr = src_real[idx2];
        float vi = src_imag[idx2];

        // (vr + j*vi) * (wr + j*wi)
        float tr = vr * wr - vi * wi;
        float ti = vr * wi + vi * wr;

        dst_real[idx1] = ur + tr;
        dst_imag[idx1] = ui + ti;
        dst_real[idx2] = ur - tr;
        dst_imag[idx2] = ui - ti;
    }
}

void fft_radix2(const float x_real[1024], const float x_imag[1024], float y_real[1024],
                 float y_imag[1024]) {
    float bufA_real[FFT_N];
    float bufA_imag[FFT_N];
    float bufB_real[FFT_N];
    float bufB_imag[FFT_N];
    float tw_real[FFT_N / 2];
    float tw_imag[FFT_N / 2];

    const float TWO_PI = 6.28318530717958647692f;

    // Precompute twiddle factors W_N^k = cos(-2*pi*k/N) + j*sin(-2*pi*k/N)
TWIDDLE_INIT:
    for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II = 1
        float ang   = -TWO_PI * (float)k / (float)FFT_N;
        tw_real[k]  = hls::cosf(ang);
        tw_imag[k]  = hls::sinf(ang);
    }

    // Load input into buffer A applying the bit-reversal permutation
BITREV_LOAD:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II = 1
        unsigned int idx = (unsigned int)i;
        unsigned int rev = 0;
    BITREV_BITS:
        for (int b = 0; b < FFT_LOGN; b++) {
#pragma HLS UNROLL
            rev = (rev << 1) | (idx & 1u);
            idx >>= 1;
        }
        bufA_real[rev] = x_real[i];
        bufA_imag[rev] = x_imag[i];
    }

    // 10 radix-2 DIT stages, ping-ponging between bufA and bufB so each
    // stage only ever reads one buffer and writes the other.
    fft_stage<0>(bufA_real, bufA_imag, bufB_real, bufB_imag, tw_real, tw_imag);
    fft_stage<1>(bufB_real, bufB_imag, bufA_real, bufA_imag, tw_real, tw_imag);
    fft_stage<2>(bufA_real, bufA_imag, bufB_real, bufB_imag, tw_real, tw_imag);
    fft_stage<3>(bufB_real, bufB_imag, bufA_real, bufA_imag, tw_real, tw_imag);
    fft_stage<4>(bufA_real, bufA_imag, bufB_real, bufB_imag, tw_real, tw_imag);
    fft_stage<5>(bufB_real, bufB_imag, bufA_real, bufA_imag, tw_real, tw_imag);
    fft_stage<6>(bufA_real, bufA_imag, bufB_real, bufB_imag, tw_real, tw_imag);
    fft_stage<7>(bufB_real, bufB_imag, bufA_real, bufA_imag, tw_real, tw_imag);
    fft_stage<8>(bufA_real, bufA_imag, bufB_real, bufB_imag, tw_real, tw_imag);
    fft_stage<9>(bufB_real, bufB_imag, bufA_real, bufA_imag, tw_real, tw_imag);
    // FFT_LOGN = 10 (even) stages => final result sits in bufA, in natural order.

WRITE_BACK:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II = 1
        y_real[i] = bufA_real[i];
        y_imag[i] = bufA_imag[i];
    }
}
