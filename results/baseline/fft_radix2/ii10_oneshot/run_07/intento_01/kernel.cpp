#include <hls_math.h>

#define FFT_N      1024
#define FFT_LOGN   10
#define FFT_HALFN  512

// 10-bit bit-reversal (LOGN is a compile-time constant, loop fully unrolled)
static int bit_reverse(int x) {
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
    float real_buf[FFT_N];
    float imag_buf[FFT_N];
    float tw_real[FFT_HALFN];
    float tw_imag[FFT_HALFN];

#pragma HLS ARRAY_PARTITION variable=real_buf cyclic factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=imag_buf cyclic factor=2 dim=1

    const float PI = 3.14159265358979323846f;

    // Precompute the N/2 twiddle factors W_N^k = exp(-j*2*pi*k/N)
    twiddle_gen:
    for (int k = 0; k < FFT_HALFN; k++) {
#pragma HLS PIPELINE II=10
        float angle = -2.0f * PI * (float)k / (float)FFT_N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // Bit-reversal reorder of the input samples into the working buffers
    bitrev:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=10
        int r = bit_reverse(i);
        real_buf[r] = x_real[i];
        imag_buf[r] = x_imag[i];
    }

    // Iterative Cooley-Tukey radix-2 DIT FFT: log2(N) stages,
    // each with N/2 independent butterflies (pipelined, II<=10)
    stage_loop:
    for (int s = 0; s < FFT_LOGN; s++) {
        int half = 1 << s;          // butterfly half-distance for this stage
        int m    = half << 1;       // stage size
        int step = FFT_HALFN / half; // twiddle index stride (= N/m)

        butterfly_loop:
        for (int k = 0; k < FFT_HALFN; k++) {
#pragma HLS PIPELINE II=10
            int group = k / half;
            int j     = k - group * half;
            int idx1  = group * m + j;
            int idx2  = idx1 + half;
            int twid_idx = j * step;

            float wr = tw_real[twid_idx];
            float wi = tw_imag[twid_idx];

            float xr2 = real_buf[idx2];
            float xi2 = imag_buf[idx2];

            // complex multiply: (xr2 + j*xi2) * (wr + j*wi)
            float tr = xr2 * wr - xi2 * wi;
            float ti = xr2 * wi + xi2 * wr;

            float xr1 = real_buf[idx1];
            float xi1 = imag_buf[idx1];

            real_buf[idx1] = xr1 + tr;
            imag_buf[idx1] = xi1 + ti;
            real_buf[idx2] = xr1 - tr;
            imag_buf[idx2] = xi1 - ti;
        }
    }

    // Write the result to the outputs
    output_copy:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=10
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
