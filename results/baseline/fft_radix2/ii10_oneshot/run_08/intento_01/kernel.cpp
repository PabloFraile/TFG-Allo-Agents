// kernel.cpp
// FFT radix-2 (Cooley-Tukey), iterativa, in-place, N = 1024 puntos.
// Decimation-in-time: reordenamiento por bit-reversal seguido de
// log2(N) = 10 etapas de mariposas radix-2.

#include <ap_int.h>
#include <hls_math.h>

static const int FFT_N      = 1024;
static const int FFT_LOG2N  = 10;      // log2(1024)
static const int FFT_HALF_N = FFT_N / 2;

static const float PI_CONST = 3.14159265358979323846f;

// Inversion de los 10 bits de un indice 0..1023
static inline ap_uint<10> bitreverse10(ap_uint<10> x) {
#pragma HLS INLINE
    ap_uint<10> r = 0;
    for (int b = 0; b < FFT_LOG2N; b++) {
#pragma HLS UNROLL
        r[FFT_LOG2N - 1 - b] = x[b];
    }
    return r;
}

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    // Buffers de trabajo in-place (dominio de la FFT)
    float a_real[FFT_N];
    float a_imag[FFT_N];
#pragma HLS BIND_STORAGE variable=a_real type=RAM_2P impl=BRAM
#pragma HLS BIND_STORAGE variable=a_imag type=RAM_2P impl=BRAM

    // Tabla de factores de giro (twiddle factors) W_N^k = exp(-j*2*pi*k/N)
    // k = 0 .. N/2-1
    float tw_real[FFT_HALF_N];
    float tw_imag[FFT_HALF_N];
#pragma HLS BIND_STORAGE variable=tw_real type=RAM_1P impl=BRAM
#pragma HLS BIND_STORAGE variable=tw_imag type=RAM_1P impl=BRAM

    // ---- Precalculo de twiddle factors ----
twiddle_gen:
    for (int k = 0; k < FFT_HALF_N; k++) {
#pragma HLS PIPELINE II=1
        float angle = (-2.0f * PI_CONST * (float)k) / (float)FFT_N;
        tw_real[k] = hls::cosf(angle);
        tw_imag[k] = hls::sinf(angle);
    }

    // ---- Carga de entrada con reordenamiento bit-reversal ----
bitrev_load:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        ap_uint<10> br = bitreverse10((ap_uint<10>)i);
        a_real[br] = x_real[i];
        a_imag[br] = x_imag[i];
    }

    // ---- Etapas de mariposas radix-2 (Cooley-Tukey, DIT) ----
stage_loop:
    for (int s = 0; s < FFT_LOG2N; s++) {
        const int half_m = 1 << s;          // m/2
        const int step   = FFT_N >> (s + 1); // N / m  -> paso en la tabla de twiddles

    butterfly_loop:
        for (int i = 0; i < FFT_HALF_N; i++) {
#pragma HLS PIPELINE II=2
#pragma HLS DEPENDENCE variable=a_real type=inter dependent=false
#pragma HLS DEPENDENCE variable=a_imag type=inter dependent=false

            int j   = i & (half_m - 1);
            int g   = i >> s;
            int k   = g << (s + 1);
            int idx1 = k + j;
            int idx2 = idx1 + half_m;
            int tw_idx = j * step;

            float wr = tw_real[tw_idx];
            float wi = tw_imag[tw_idx];

            float ur = a_real[idx1];
            float ui = a_imag[idx1];
            float vr = a_real[idx2];
            float vi = a_imag[idx2];

            // t = W * v
            float tr = wr * vr - wi * vi;
            float ti = wr * vi + wi * vr;

            a_real[idx1] = ur + tr;
            a_imag[idx1] = ui + ti;
            a_real[idx2] = ur - tr;
            a_imag[idx2] = ui - ti;
        }
    }

    // ---- Escritura de la salida (ya en orden natural) ----
out_store:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = a_real[i];
        y_imag[i] = a_imag[i];
    }
}
