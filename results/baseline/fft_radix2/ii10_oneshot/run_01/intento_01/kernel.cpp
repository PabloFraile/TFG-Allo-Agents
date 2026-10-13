// kernel.cpp
// Radix-2 Cooley-Tukey FFT, N = 1024 points, in-place style I/O.
// Target: xcu280-fsvh2892-2L-e, clock period 3.33 ns, II <= 10 on every
// pipelined loop.

#include <cmath>

static const int N      = 1024;
static const int LOGN   = 10;      // log2(1024)
static const int HALFN  = 512;     // N/2 twiddle factors needed

// ---------------------------------------------------------------------------
// Bit-reversal of a LOGN-bit index (fully unrolled, trivial combinational
// logic).
// ---------------------------------------------------------------------------
static inline int bit_reverse(int x) {
    int r = 0;
    for (int i = 0; i < LOGN; i++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1);
        x >>= 1;
    }
    return r;
}

// ---------------------------------------------------------------------------
// One radix-2 DIT stage, fully specialized at compile time by STAGE
// (STAGE = 0 .. LOGN-1). half = 2^STAGE is the butterfly half-distance for
// this stage; the stage processes N/2 independent butterflies.
//
// src_* and dst_* must be two *different* buffers (ping-pong), so each
// buffer only ever needs 2 read ports or 2 write ports per cycle, which a
// dual-port BRAM provides directly -> II = 1 is achievable.
// ---------------------------------------------------------------------------
template <int STAGE>
static void fft_stage(const float src_r[N], const float src_i[N],
                       float dst_r[N], float dst_i[N],
                       const float twr[HALFN], const float twi[HALFN]) {
    const int half    = 1 << STAGE;
    const int twShift = (LOGN - 1) - STAGE; // twStep = HALFN / half = 2^twShift

    for (int i = 0; i < HALFN; i++) {
#pragma HLS PIPELINE II=1
        int j      = i & (half - 1);
        int group  = i >> STAGE;
        int k      = group << (STAGE + 1);
        int idx0   = k + j;
        int idx1   = idx0 + half;
        int twIdx  = j << twShift;

        float wr = twr[twIdx];
        float wi = twi[twIdx];

        float xr0 = src_r[idx0];
        float xi0 = src_i[idx0];
        float xr1 = src_r[idx1];
        float xi1 = src_i[idx1];

        float tr = xr1 * wr - xi1 * wi;
        float ti = xr1 * wi + xi1 * wr;

        dst_r[idx0] = xr0 + tr;
        dst_i[idx0] = xi0 + ti;
        dst_r[idx1] = xr0 - tr;
        dst_i[idx1] = xi0 - ti;
    }
}

// ---------------------------------------------------------------------------
// Top-level kernel
// ---------------------------------------------------------------------------
void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024])
{
    // Ping-pong buffers for the iterative FFT.
    float buf0_real[N], buf0_imag[N];
    float buf1_real[N], buf1_imag[N];

    // Twiddle factor table: W_N^i = exp(-2*pi*i/N), i = 0..N/2-1
    float twr[HALFN], twi[HALFN];

    const float PI = 3.14159265358979323846f;

TWIDDLE_GEN:
    for (int i = 0; i < HALFN; i++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * PI * (float)i / (float)N;
        twr[i] = cosf(angle);
        twi[i] = sinf(angle);
    }

    // Bit-reversal reorder of the input into buf0.
BITREV:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int ridx = bit_reverse(i);
        buf0_real[ridx] = x_real[i];
        buf0_imag[ridx] = x_imag[i];
    }

    // 10 butterfly stages, statically unrolled, ping-ponging between
    // buf0/buf1. After an even number of stages (10) the final result
    // lands back in buf0.
    fft_stage<0>(buf0_real, buf0_imag, buf1_real, buf1_imag, twr, twi);
    fft_stage<1>(buf1_real, buf1_imag, buf0_real, buf0_imag, twr, twi);
    fft_stage<2>(buf0_real, buf0_imag, buf1_real, buf1_imag, twr, twi);
    fft_stage<3>(buf1_real, buf1_imag, buf0_real, buf0_imag, twr, twi);
    fft_stage<4>(buf0_real, buf0_imag, buf1_real, buf1_imag, twr, twi);
    fft_stage<5>(buf1_real, buf1_imag, buf0_real, buf0_imag, twr, twi);
    fft_stage<6>(buf0_real, buf0_imag, buf1_real, buf1_imag, twr, twi);
    fft_stage<7>(buf1_real, buf1_imag, buf0_real, buf0_imag, twr, twi);
    fft_stage<8>(buf0_real, buf0_imag, buf1_real, buf1_imag, twr, twi);
    fft_stage<9>(buf1_real, buf1_imag, buf0_real, buf0_imag, twr, twi);

    // Final result resides in buf0 (LOGN = 10 stages -> even number of swaps).
COPY_OUT:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = buf0_real[i];
        y_imag[i] = buf0_imag[i];
    }
}
