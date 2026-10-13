#include "hls_math.h"

#define FFT_N   1024
#define FFT_LOGN 10

static const float FFT_PI = 3.14159265358979323846f;

// ---------------------------------------------------------------------------
// Bit reversal of a FFT_LOGN-bit index (fully combinational, small loop
// unrolled so it can be inlined inside a pipelined loop with II=1).
// ---------------------------------------------------------------------------
static int bit_reverse_idx(int x) {
#pragma HLS INLINE
    int result = 0;
BITREV_UNROLL:
    for (int b = 0; b < FFT_LOGN; b++) {
#pragma HLS UNROLL
        result = (result << 1) | (x & 1);
        x >>= 1;
    }
    return result;
}

// ---------------------------------------------------------------------------
// Precompute twiddle factors W_N^k = exp(-j*2*pi*k/N), k = 0 .. N/2-1
// ---------------------------------------------------------------------------
static void compute_twiddles(float cos_t[FFT_N / 2], float sin_t[FFT_N / 2]) {
#pragma HLS INLINE off
TWIDDLE_LOOP:
    for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * FFT_PI * (float)k / (float)FFT_N;
        cos_t[k] = hls::cosf(angle);
        sin_t[k] = hls::sinf(angle);
    }
}

// ---------------------------------------------------------------------------
// One radix-2 DIT stage.
// src_* : input buffer for this stage (read only)
// dst_* : output buffer for this stage (write only)
// s     : stage index 0 .. FFT_LOGN-1   (m2 = 2^s, m = 2^(s+1))
// Reused sequentially for every stage -> no loop-carried dependency inside
// the inner loop, so II=1 is achievable regardless of FP latency.
// ---------------------------------------------------------------------------
static void fft_stage(const float src_r[FFT_N], const float src_i[FFT_N],
                       float dst_r[FFT_N], float dst_i[FFT_N],
                       const float cos_t[FFT_N / 2], const float sin_t[FFT_N / 2],
                       int s) {
#pragma HLS INLINE off
    const int m2    = 1 << s;
    const int shift = FFT_LOGN - 1 - s;

BUTTERFLY_LOOP:
    for (int i = 0; i < FFT_N / 2; i++) {
#pragma HLS PIPELINE II=1
        int k    = (i >> s) << (s + 1);
        int j    = i & (m2 - 1);
        int idx1 = k + j;
        int idx2 = idx1 + m2;
        int tw_idx = j << shift;

        float tw_re = cos_t[tw_idx];
        float tw_im = sin_t[tw_idx];

        float ur  = src_r[idx1];
        float ui  = src_i[idx1];
        float vr0 = src_r[idx2];
        float vi0 = src_i[idx2];

        float vr = vr0 * tw_re - vi0 * tw_im;
        float vi = vr0 * tw_im + vi0 * tw_re;

        dst_r[idx1] = ur + vr;
        dst_i[idx1] = ui + vi;
        dst_r[idx2] = ur - vr;
        dst_i[idx2] = ui - vi;
    }
}

// ---------------------------------------------------------------------------
// Top-level kernel: 1024-point radix-2 Cooley-Tukey FFT
// ---------------------------------------------------------------------------
void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    float cos_t[FFT_N / 2];
    float sin_t[FFT_N / 2];

    float bufA_r[FFT_N];
    float bufA_i[FFT_N];
    float bufB_r[FFT_N];
    float bufB_i[FFT_N];

    compute_twiddles(cos_t, sin_t);

    // Bit-reversal permutation of the input into bufA (acts as "stage -1" output)
BITREV_LOOP:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse_idx(i);
        bufA_r[i] = x_real[r];
        bufA_i[i] = x_imag[r];
    }

    // FFT_LOGN butterfly stages, ping-ponging between bufA and bufB.
    // After the last stage (s = FFT_LOGN-1, odd) the result resides in bufA.
STAGE_LOOP:
    for (int s = 0; s < FFT_LOGN; s++) {
        if ((s & 1) == 0) {
            fft_stage(bufA_r, bufA_i, bufB_r, bufB_i, cos_t, sin_t, s);
        } else {
            fft_stage(bufB_r, bufB_i, bufA_r, bufA_i, cos_t, sin_t, s);
        }
    }

OUTPUT_LOOP:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = bufA_r[i];
        y_imag[i] = bufA_i[i];
    }
}
