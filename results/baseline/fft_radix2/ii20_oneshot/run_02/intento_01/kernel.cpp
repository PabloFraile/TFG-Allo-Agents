// kernel.cpp
// Radix-2 Cooley-Tukey FFT (decimation in time, iterative, in-place per stage)
// N = 1024 points, complex input/output represented as separate real/imag arrays.
// Target: xcu280-fsvh2892-2L-e, clk period 3.33 ns, II <= 20 on every pipelined loop.

#include <hls_math.h>

static const int N    = 1024;
static const int LOGN = 10;          // log2(1024)

static const float PI_F = 3.14159265358979323846f;

// ---------------------------------------------------------------------------
// 10-bit index bit-reversal (fully unrolled, combinational)
// ---------------------------------------------------------------------------
static inline int bit_reverse10(int x) {
    int r = 0;
    for (int b = 0; b < LOGN; b++) {
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
#pragma HLS INTERFACE mode=ap_memory port=x_real
#pragma HLS INTERFACE mode=ap_memory port=x_imag
#pragma HLS INTERFACE mode=ap_memory port=y_real
#pragma HLS INTERFACE mode=ap_memory port=y_imag

    // -----------------------------------------------------------------------
    // Ping-pong buffers: re[0..1][N], im[0..1][N]
    // Each sub-buffer gets its own true dual-port BRAM (2 read + 2 write
    // accesses per cycle), which is exactly what one butterfly needs,
    // enabling II=1 pipelining of the butterfly loop.
    // -----------------------------------------------------------------------
    float re[2][N];
    float im[2][N];
#pragma HLS ARRAY_PARTITION variable=re complete dim=1
#pragma HLS ARRAY_PARTITION variable=im complete dim=1
#pragma HLS BIND_STORAGE variable=re type=RAM_2P impl=bram
#pragma HLS BIND_STORAGE variable=im type=RAM_2P impl=bram

    // Twiddle factor ROM: W[k] = exp(-j*2*pi*k/N), k = 0 .. N/2-1
    float W_re[N / 2];
    float W_im[N / 2];
#pragma HLS BIND_STORAGE variable=W_re type=RAM_1P impl=bram
#pragma HLS BIND_STORAGE variable=W_im type=RAM_1P impl=bram

    // -----------------------------------------------------------------------
    // Stage 0: precompute twiddle table
    // -----------------------------------------------------------------------
TWIDDLE_LOOP:
    for (int k = 0; k < N / 2; k++) {
#pragma HLS PIPELINE II=1
        float ang = -2.0f * PI_F * (float)k / (float)N;
        W_re[k] = hls::cosf(ang);
        W_im[k] = hls::sinf(ang);
    }

    // -----------------------------------------------------------------------
    // Stage 1: bit-reversal permutation of the input into buffer 0
    // -----------------------------------------------------------------------
BITREV_LOOP:
    for (int idx = 0; idx < N; idx++) {
#pragma HLS PIPELINE II=1
        int rv = bit_reverse10(idx);
        re[0][rv] = x_real[idx];
        im[0][rv] = x_imag[idx];
    }

    // -----------------------------------------------------------------------
    // Stage 2: LOGN butterfly stages, ping-ponging between buffer 0 and 1
    // -----------------------------------------------------------------------
STAGE_LOOP:
    for (int s = 0; s < LOGN; s++) {
        const int half   = 1 << s;
        const int len    = half << 1;
        const int stride = N >> (s + 1);   // N / len
        const int rbuf   = s & 1;
        const int wbuf   = 1 - rbuf;

    BUTTERFLY_LOOP:
        for (int idx = 0; idx < N / 2; idx++) {
#pragma HLS PIPELINE II=1
            int j       = idx & (half - 1);
            int i       = (idx >> s) << (s + 1);
            int base    = i + j;
            int partner = base + half;
            int w_idx   = j * stride;

            float u_re = re[rbuf][base];
            float u_im = im[rbuf][base];
            float v_re = re[rbuf][partner];
            float v_im = im[rbuf][partner];

            float w_re = W_re[w_idx];
            float w_im = W_im[w_idx];

            float t_re = v_re * w_re - v_im * w_im;
            float t_im = v_re * w_im + v_im * w_re;

            re[wbuf][base]    = u_re + t_re;
            im[wbuf][base]    = u_im + t_im;
            re[wbuf][partner] = u_re - t_re;
            im[wbuf][partner] = u_im - t_im;
        }
    }

    // -----------------------------------------------------------------------
    // Stage 3: copy final buffer out. After LOGN (=10, even) stages the
    // result lives in buffer 0 (rbuf/wbuf parity analysis: last stage s=9
    // writes to wbuf = 1 - (9 & 1) = 0).
    // -----------------------------------------------------------------------
    const int finalBuf = (LOGN % 2 == 0) ? 0 : 1;

OUTPUT_LOOP:
    for (int idx = 0; idx < N; idx++) {
#pragma HLS PIPELINE II=1
        y_real[idx] = re[finalBuf][idx];
        y_imag[idx] = im[finalBuf][idx];
    }
}
