#include <hls_math.h>

#define FFT_N    1024
#define FFT_LOGN 10

// Reverse the lowest FFT_LOGN bits of x (used for the bit-reversal
// permutation at the input of the iterative radix-2 DIT FFT).
static inline int bit_reverse10(int x) {
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
    float y_imag[1024])
{
    float xr[FFT_N];
    float xi[FFT_N];
#pragma HLS ARRAY_PARTITION variable=xr cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=xi cyclic factor=4 dim=1

    static const float PI = 3.14159265358979323846f;

    // --- Stage 0: bit-reversal permutation (gather input samples) ---
bitrev_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int ridx = bit_reverse10(i);
        xr[ridx] = x_real[i];
        xi[ridx] = x_imag[i];
    }

    // --- Iterative radix-2 Cooley-Tukey DIT FFT, log2(N) stages ---
stage_loop:
    for (int s = 0; s < FFT_LOGN; s++) {
        int m2 = 1 << s;        // half the current butterfly span
        int m  = m2 << 1;       // current butterfly span (DFT size of this stage)

    butterfly_loop:
        for (int i = 0; i < FFT_N / 2; i++) {
#pragma HLS PIPELINE II=16
            int block  = i >> s;                 // which DFT block of size m
            int offset = i - (block << s);        // position within the block (0..m2-1)

            int u = (block << (s + 1)) + offset;  // "upper" index
            int t = u + m2;                       // "lower" index

            float angle = -PI * (float)offset / (float)m2;
            float wr = hls::cosf(angle);
            float wi = hls::sinf(angle);

            float xr_t = xr[t];
            float xi_t = xi[t];
            float xr_u = xr[u];
            float xi_u = xi[u];

            float tr = wr * xr_t - wi * xi_t;
            float ti = wr * xi_t + wi * xr_t;

            xr[t] = xr_u - tr;
            xi[t] = xi_u - ti;
            xr[u] = xr_u + tr;
            xi[u] = xi_u + ti;
        }
    }

    // --- Write-back results ---
output_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = xr[i];
        y_imag[i] = xi[i];
    }
}
