// kernel.cpp
// Radix-2 Cooley-Tukey FFT (iterative, decimation-in-time), N = 1024.
// Target: AMD/Xilinx Vitis HLS 2023.1, xcu280-fsvh2892-2L-e, clk=3.33ns, II<=5.

#include <hls_math.h>
#include <cmath>

static const int FFT_N      = 1024;
static const int FFT_LOG2N  = 10;      // log2(1024)
static const int FFT_HALF_N = 512;     // N/2

// -----------------------------------------------------------------------
// Fully-unrolled combinational bit-reversal for a 10-bit index.
// -----------------------------------------------------------------------
static inline int bit_reverse(int x) {
    int r = 0;
#pragma HLS UNROLL
    for (int b = 0; b < FFT_LOG2N; b++) {
        r = (r << 1) | (x & 0x1);
        x >>= 1;
    }
    return r;
}

// -----------------------------------------------------------------------
// Top-level kernel: single-call full FFT of 1024 complex points.
// -----------------------------------------------------------------------
void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
)
{
    // Working buffers (BRAM). Need simultaneous access to two distinct
    // indices per butterfly (idx_a, idx_b) -> use true-dual-port BRAM.
    float a_real[FFT_N];
    float a_imag[FFT_N];
#pragma HLS BIND_STORAGE variable=a_real type=RAM_T2P impl=bram
#pragma HLS BIND_STORAGE variable=a_imag type=RAM_T2P impl=bram

    // Twiddle-factor tables: W_N^k = exp(-j*2*pi*k/N), k = 0 .. N/2-1
    float cos_tab[FFT_HALF_N];
    float sin_tab[FFT_HALF_N];
#pragma HLS BIND_STORAGE variable=cos_tab type=RAM_1P impl=bram
#pragma HLS BIND_STORAGE variable=sin_tab type=RAM_1P impl=bram

    const float two_pi_over_n = (float)(2.0 * M_PI / (double)FFT_N);

twiddle_gen:
    for (int k = 0; k < FFT_HALF_N; k++) {
#pragma HLS PIPELINE II=1
        float angle = -two_pi_over_n * (float)k;
        cos_tab[k] = hls::cosf(angle);
        sin_tab[k] = hls::sinf(angle);
    }

    // ---------------------------------------------------------------
    // Stage 0: load input with bit-reversal reordering.
    // ---------------------------------------------------------------
bitrev_load:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse(i);
        a_real[i] = x_real[r];
        a_imag[i] = x_imag[r];
    }

    // ---------------------------------------------------------------
    // log2(N) butterfly stages (constant-geometry addressing via
    // shifts/masks instead of variable divides/multiplies).
    // ---------------------------------------------------------------
stage_loop:
    for (int s = 1; s <= FFT_LOG2N; s++) {
        int log2_half_m = s - 1;          // half_m = 1 << log2_half_m
        int half_m      = 1 << log2_half_m;
        int tw_shift     = FFT_LOG2N - s; // tw_step = 1 << tw_shift

    butterfly_loop:
        for (int i = 0; i < FFT_HALF_N; i++) {
#pragma HLS PIPELINE II=5
            int group  = i >> log2_half_m;
            int j      = i & (half_m - 1);
            int k      = group << s;          // k = group * (2*half_m)
            int idx_a  = k | j;                // k + j (disjoint bits)
            int idx_b  = idx_a + half_m;
            int tw_idx = j << tw_shift;        // j * (N / (2*half_m))

            float wr = cos_tab[tw_idx];
            float wi = sin_tab[tw_idx];

            float br = a_real[idx_b];
            float bi = a_imag[idx_b];

            float tr = wr * br - wi * bi;
            float ti = wr * bi + wi * br;

            float ar = a_real[idx_a];
            float ai = a_imag[idx_a];

            a_real[idx_a] = ar + tr;
            a_imag[idx_a] = ai + ti;
            a_real[idx_b] = ar - tr;
            a_imag[idx_b] = ai - ti;
        }
    }

    // ---------------------------------------------------------------
    // Write results out.
    // ---------------------------------------------------------------
store_out:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = a_real[i];
        y_imag[i] = a_imag[i];
    }
}
