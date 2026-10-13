// kernel.cpp
// Radix-2 Cooley-Tukey FFT (Decimation In Time), N = 1024 puntos.
// Implementación iterativa: permutación bit-reversed + 10 etapas de
// mariposas, usando doble buffer (ping-pong) para que cada etapa solo
// lea de un buffer y escriba en el otro, evitando conflictos de puertos
// de memoria y permitiendo II=1 en los bucles pipelineados.

#include "hls_math.h"

#define FFT_N    1024
#define FFT_LOGN 10

// Inversión de bits de un índice de FFT_LOGN bits (totalmente desenrollado).
static unsigned bit_reverse_idx(unsigned x) {
#pragma HLS INLINE
    unsigned r = 0;
    for (int i = 0; i < FFT_LOGN; i++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 0x1u);
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
    // Tabla de factores twiddle W_N^i = e^{-j*2*pi*i/N}, i = 0..N/2-1.
    // Se calcula una sola vez (estática) y se reutiliza en llamadas futuras.
    static float tw_real[FFT_N / 2];
    static float tw_imag[FFT_N / 2];
    static bool  tw_ready = false;

#pragma HLS BIND_STORAGE variable=tw_real type=RAM_1P impl=bram
#pragma HLS BIND_STORAGE variable=tw_imag type=RAM_1P impl=bram

    if (!tw_ready) {
        twiddle_init:
        for (int i = 0; i < FFT_N / 2; i++) {
#pragma HLS PIPELINE II=1
            float angle = -2.0f * 3.14159265358979323846f * (float)i / (float)FFT_N;
            tw_real[i] = hls::cosf(angle);
            tw_imag[i] = hls::sinf(angle);
        }
        tw_ready = true;
    }

    // Doble buffer de trabajo (complejo) para las etapas de mariposas.
    float A_real[FFT_N], A_imag[FFT_N];
    float B_real[FFT_N], B_imag[FFT_N];

#pragma HLS BIND_STORAGE variable=A_real type=RAM_2P impl=bram
#pragma HLS BIND_STORAGE variable=A_imag type=RAM_2P impl=bram
#pragma HLS BIND_STORAGE variable=B_real type=RAM_2P impl=bram
#pragma HLS BIND_STORAGE variable=B_imag type=RAM_2P impl=bram

    // 1) Permutación bit-reversed de la entrada hacia el buffer A.
    bitrev_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        unsigned r = bit_reverse_idx((unsigned)i);
        A_real[r] = x_real[i];
        A_imag[r] = x_imag[i];
    }

    // 2) FFT_LOGN etapas de mariposas radix-2 (DIT), ping-pong A<->B.
    //    En cada etapa se lee solo de un buffer y se escribe solo en el
    //    otro, de modo que cada BRAM recibe como máximo 2 accesos del
    //    mismo tipo (2 lecturas o 2 escrituras) por ciclo.
    for (int stage = 0; stage < FFT_LOGN; stage++) {
        int half       = 1 << stage;
        int shift_step = FFT_LOGN - 1 - stage;
        bool read_A    = ((stage & 1) == 0);

        if (read_A) {
            butterfly_loop_a:
            for (int t = 0; t < FFT_N / 2; t++) {
#pragma HLS PIPELINE II=1
                int j     = t & (half - 1);
                int k     = (t >> stage) << (stage + 1);
                int idx1  = k + j;
                int idx2  = idx1 + half;
                int twIdx = j << shift_step;

                float ar = A_real[idx1];
                float ai = A_imag[idx1];
                float br = A_real[idx2];
                float bi = A_imag[idx2];
                float wr = tw_real[twIdx];
                float wi = tw_imag[twIdx];

                float tr = br * wr - bi * wi;
                float ti = br * wi + bi * wr;

                B_real[idx1] = ar + tr;
                B_imag[idx1] = ai + ti;
                B_real[idx2] = ar - tr;
                B_imag[idx2] = ai - ti;
            }
        } else {
            butterfly_loop_b:
            for (int t = 0; t < FFT_N / 2; t++) {
#pragma HLS PIPELINE II=1
                int j     = t & (half - 1);
                int k     = (t >> stage) << (stage + 1);
                int idx1  = k + j;
                int idx2  = idx1 + half;
                int twIdx = j << shift_step;

                float ar = B_real[idx1];
                float ai = B_imag[idx1];
                float br = B_real[idx2];
                float bi = B_imag[idx2];
                float wr = tw_real[twIdx];
                float wi = tw_imag[twIdx];

                float tr = br * wr - bi * wi;
                float ti = br * wi + bi * wr;

                A_real[idx1] = ar + tr;
                A_imag[idx1] = ai + ti;
                A_real[idx2] = ar - tr;
                A_imag[idx2] = ai - ti;
            }
        }
    }

    // FFT_LOGN = 10 (par) -> tras la última etapa (stage=9, impar) el
    // resultado final queda en el buffer A.
    output_loop:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = A_real[i];
        y_imag[i] = A_imag[i];
    }
}
