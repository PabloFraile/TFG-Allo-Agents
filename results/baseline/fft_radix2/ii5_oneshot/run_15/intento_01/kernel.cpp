// kernel.cpp
// Radix-2 Cooley-Tukey FFT (Decimation-In-Time, iterative), N = 1024 points.
// Target: AMD/Xilinx Vitis HLS 2023.1, xcu280-fsvh2892-2L-e, clk period 3.33 ns.
// Pipelined loops are constrained to II <= 5 (objetivo_ii = 5).

#include <cmath>

static const int FFT_N    = 1024;
static const int FFT_LOGN = 10; // log2(1024)

// Reverses the lowest `bits` bits of x. Small combinational helper,
// fully unrolled and inlined into the caller's pipelined loop.
static inline int bit_reverse(int x, int bits) {
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
    const float PI = 3.14159265358979323846f;

    // Working buffers (in-place iterative FFT storage)
    float real_buf[FFT_N];
    float imag_buf[FFT_N];

    // Twiddle factor ROM: W_N^k = cos(-2*pi*k/N) + j*sin(-2*pi*k/N), k = 0..N/2-1.
    // Computed once (static) and reused across kernel invocations, so it does
    // not impact the II of the pipelined computational loops below.
    static float twCos[FFT_N / 2];
    static float twSin[FFT_N / 2];
    static bool  twInit = false;

    if (!twInit) {
        for (int k = 0; k < FFT_N / 2; k++) {
            float angle = -2.0f * PI * (float)k / (float)FFT_N;
            twCos[k] = std::cos(angle);
            twSin[k] = std::sin(angle);
        }
        twInit = true;
    }

    // Bit-reversal permutation: load inputs into working buffers.
    load_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse(i, FFT_LOGN);
        real_buf[i] = x_real[r];
        imag_buf[i] = x_imag[r];
    }

    // Iterative radix-2 DIT FFT: log2(N) stages, N/2 butterflies per stage.
    stage_loop:
    for (int s = 1; s <= FFT_LOGN; s++) {
        int m      = 1 << s;   // current butterfly span
        int half   = m >> 1;   // distance between paired elements
        int twStep = FFT_N >> s; // twiddle table stride for this stage

        butterfly_loop:
        for (int b = 0; b < FFT_N / 2; b++) {
#pragma HLS PIPELINE II=5
            int j    = b % half;
            int grp  = b / half;
            int idx1 = grp * m + j;
            int idx2 = idx1 + half;
            int twIdx = j * twStep;

            float cR  = twCos[twIdx];
            float cI  = twSin[twIdx];
            float xr2 = real_buf[idx2];
            float xi2 = imag_buf[idx2];

            // Complex multiply: t = W * X[idx2]
            float tr = cR * xr2 - cI * xi2;
            float ti = cR * xi2 + cI * xr2;

            float ur = real_buf[idx1];
            float ui = imag_buf[idx1];

            real_buf[idx1] = ur + tr;
            imag_buf[idx1] = ui + ti;
            real_buf[idx2] = ur - tr;
            imag_buf[idx2] = ui - ti;
        }
    }

    // Write results to outputs (natural order, thanks to input bit-reversal).
    store_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
