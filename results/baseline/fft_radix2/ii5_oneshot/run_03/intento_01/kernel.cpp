// kernel.cpp
// FFT radix-2 (Cooley-Tukey, decimation in time) sobre N=1024 puntos complejos.
// Convención igual a numpy.fft.fft: X[k] = sum_n x[n] * exp(-2*pi*i*k*n/N)

#include <cmath>

#define N     1024
#define LOGN  10

static const double PI_D = 3.14159265358979323846;

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    // Buffers internos (BRAM) donde se realiza la FFT in-place tras el reordenado
    float real_buf[N];
    float imag_buf[N];

    // Tabla de factores de giro: tw[k] = exp(-2*pi*i*k/N), k = 0..N/2-1
    float tw_real[N / 2];
    float tw_imag[N / 2];

#pragma HLS BIND_STORAGE variable=real_buf type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=imag_buf type=ram_2p impl=bram
#pragma HLS BIND_STORAGE variable=tw_real  type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=tw_imag  type=ram_1p impl=bram

    // ---------------------------------------------------------------
    // 1) Precálculo de la tabla de twiddle factors
    // ---------------------------------------------------------------
    twiddle_init:
    for (int k = 0; k < N / 2; k++) {
#pragma HLS PIPELINE II=5
        float angle = (float)(-2.0 * PI_D * (double)k / (double)N);
        tw_real[k] = cosf(angle);
        tw_imag[k] = sinf(angle);
    }

    // ---------------------------------------------------------------
    // 2) Carga de la entrada con reordenado bit-reverse
    // ---------------------------------------------------------------
    bitrev_load:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int rev = 0;
        int ii  = i;
        bitrev_bits:
        for (int b = 0; b < LOGN; b++) {
#pragma HLS UNROLL
            rev = (rev << 1) | (ii & 1);
            ii >>= 1;
        }
        real_buf[rev] = x_real[i];
        imag_buf[rev] = x_imag[i];
    }

    // ---------------------------------------------------------------
    // 3) Etapas iterativas radix-2 DIT (log2(N) etapas secuenciales,
    //    cada una con N/2 mariposas pipelineadas)
    // ---------------------------------------------------------------
    fft_stages:
    for (int stage = 0; stage < LOGN; stage++) {
        // len = 2^(stage+1) ; half = 2^stage ; tw_step = N / len = 2^(9-stage)
        const int half       = 1 << stage;
        const int len_shift  = stage + 1;     // log2(len)
        const int tw_shift   = (LOGN - 1) - stage; // log2(tw_step)
        const int mask       = half - 1;

        fft_butterflies:
        for (int idx = 0; idx < N / 2; idx++) {
#pragma HLS PIPELINE II=5
            int block = idx >> stage;   // idx / half
            int j     = idx & mask;     // idx % half

            int base = block << len_shift; // block * len
            int i0 = base + j;
            int i1 = i0 + half;

            int tw_idx = j << tw_shift; // j * tw_step

            float wr = tw_real[tw_idx];
            float wi = tw_imag[tw_idx];

            float xr = real_buf[i1];
            float xi = imag_buf[i1];

            float tr = xr * wr - xi * wi;
            float ti = xr * wi + xi * wr;

            float ar = real_buf[i0];
            float ai = imag_buf[i0];

            real_buf[i0] = ar + tr;
            imag_buf[i0] = ai + ti;
            real_buf[i1] = ar - tr;
            imag_buf[i1] = ai - ti;
        }
    }

    // ---------------------------------------------------------------
    // 4) Escritura de la salida
    // ---------------------------------------------------------------
    write_out:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
