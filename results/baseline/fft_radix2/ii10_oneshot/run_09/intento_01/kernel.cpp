#include "hls_math.h"

// ===========================================================================
// fft_radix2 : 1024-point, radix-2, decimation-in-time Cooley-Tukey FFT
//
// Algorithm (iterative, in-place, classic Cormen-style iterative FFT):
//   1) bit-reverse permutation of the input samples.
//   2) log2(N) = 10 butterfly stages, each performing N/2 independent
//      butterflies. Stages ping-pong between two physically separate
//      buffers (buf[0]/buf[1]) so that, within a stage, all reads come
//      from one buffer and all writes go to the other buffer -> no
//      RAW/WAR hazards inside the pipelined butterfly loop, which lets
//      the tool close II=1 on every butterfly loop.
//
// Twiddle factors W_N^k = exp(-j*2*pi*k/N) are evaluated on the fly with
// the Vitis HLS floating point math library (hls::cosf / hls::sinf),
// which is fully pipelineable, instead of storing a precomputed ROM.
//
// Matches numpy.fft.fft (unnormalized forward transform) used as the
// golden reference (fft_numpy_reference).
// ===========================================================================

#define FFT_N     1024
#define FFT_LOGN  10

static const float TWO_PI_OVER_N = 6.283185307179586f / (float)FFT_N;

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024])
{
    // Ping-pong working buffers. Partitioning dim=1 (size 2) completely
    // turns buf_r[0]/buf_r[1] (and buf_i[0]/buf_i[1]) into two separate
    // physical memories, so a stage can read one and write the other
    // using independent memory ports, which is what allows II=1 on the
    // butterfly loop below (4 accesses/cycle split across 2 memories).
    float buf_r[2][FFT_N];
    float buf_i[2][FFT_N];
#pragma HLS ARRAY_PARTITION variable=buf_r dim=1 complete
#pragma HLS ARRAY_PARTITION variable=buf_i dim=1 complete

    // -----------------------------------------------------------------
    // Stage 0: bit-reversal reorder of the input samples into buf[0]
    // -----------------------------------------------------------------
bitrev_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int rev = 0;
        int v   = i;
    bitrev_unroll:
        for (int b = 0; b < FFT_LOGN; b++) {
#pragma HLS UNROLL
            rev = (rev << 1) | (v & 1);
            v   = v >> 1;
        }
        buf_r[0][i] = x_real[rev];
        buf_i[0][i] = x_imag[rev];
    }

    // -----------------------------------------------------------------
    // log2(N) butterfly stages
    // -----------------------------------------------------------------
stage_loop:
    for (int stage = 0; stage < FFT_LOGN; stage++) {
        const int src    = stage & 1;
        const int dst     = 1 - src;
        const int half_m  = 1 << stage;              // half the current block size
        const int mask    = half_m - 1;
        const int step     = (FFT_N >> 1) >> stage;   // twiddle index stride

    butterfly_loop:
        for (int b = 0; b < (FFT_N >> 1); b++) {
#pragma HLS PIPELINE II=1
            int group = b >> stage;     // which block of size (2*half_m)
            int j     = b & mask;       // position inside the half-block
            int k     = group << (stage + 1);
            int idx   = j * step;       // 0 .. FFT_N/2-1

            int p = k + j;
            int q = p + half_m;

            float angle = idx * TWO_PI_OVER_N;
            float wr =  hls::cosf(angle);
            float wi = -hls::sinf(angle);

            float qr = buf_r[src][q];
            float qi = buf_i[src][q];

            float tr = qr * wr - qi * wi;
            float ti = qr * wi + qi * wr;

            float ur = buf_r[src][p];
            float ui = buf_i[src][p];

            buf_r[dst][p] = ur + tr;
            buf_i[dst][p] = ui + ti;
            buf_r[dst][q] = ur - tr;
            buf_i[dst][q] = ui - ti;
        }
    }

    // -----------------------------------------------------------------
    // Copy final buffer (index = FFT_LOGN & 1) to the outputs
    // -----------------------------------------------------------------
    const int final_buf = FFT_LOGN & 1;
output_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = buf_r[final_buf][i];
        y_imag[i] = buf_i[final_buf][i];
    }
}
