// kernel.cpp
// FFT radix-2 (Cooley-Tukey, decimation-in-time) iterativa, N = 1024 puntos
// complejos. Implementa la DFT directa (sin normalizar), compatible con
// numpy.fft.fft como modelo "golden".
//
// Target: xcu280-fsvh2892-2L-e, periodo de reloj 3.33 ns, II <= 20 en todos
// los bucles pipelineados.

#include "hls_math.h"

static const int N    = 1024;
static const int LOGN = 10;              // log2(1024)

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024])
{
    // Memorias de trabajo internas (mapean a BRAM)
    float data_real[N];
    float data_imag[N];
    float tw_real[N / 2];
    float tw_imag[N / 2];

    // -----------------------------------------------------------------
    // 1) Reordenamiento bit-reversal de la entrada (requisito de la FFT
    //    decimation-in-time iterativa)
    // -----------------------------------------------------------------
    bitrev_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        int rev = 0;
        int tmp = i;
        bitrev_bits:
        for (int b = 0; b < LOGN; b++) {
#pragma HLS UNROLL
            rev = (rev << 1) | (tmp & 1);
            tmp >>= 1;
        }
        data_real[i] = x_real[rev];
        data_imag[i] = x_imag[rev];
    }

    // -----------------------------------------------------------------
    // 2) Tabla de factores de giro (twiddle factors):
    //    W_N^p = exp(-j*2*pi*p/N), p = 0 .. N/2-1
    //    Esta tabla única se reutiliza en todas las etapas indexando con
    //    tw_index = j * (N/m)
    // -----------------------------------------------------------------
    const float PI_F = 3.14159265358979323846f;

    twiddle_loop:
    for (int p = 0; p < N / 2; p++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT min=512 max=512
        float angle = -2.0f * PI_F * (float)p / (float)N;
        tw_real[p] = hls::cosf(angle);
        tw_imag[p] = hls::sinf(angle);
    }

    // -----------------------------------------------------------------
    // 3) Etapas de la FFT iterativa radix-2 DIT (log2(N) etapas,
    //    cada una con N/2 mariposas)
    // -----------------------------------------------------------------
    stage_loop:
    for (int stage = 1; stage <= LOGN; stage++) {
        const int m           = 1 << stage;      // tamaño del grupo (span)
        const int half_m       = m >> 1;          // mitad del grupo
        const int num_groups   = N / m;           // número de grupos
        const int log_half_m   = stage - 1;       // log2(half_m)

        butterfly_loop:
        for (int idx = 0; idx < N / 2; idx++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT min=1 max=512

            // Descomposición de idx en (grupo, posición dentro del grupo)
            int j     = idx & (half_m - 1);   // posición dentro del grupo [0, half_m)
            int group = idx >> log_half_m;    // índice de grupo
            int k     = group << stage;       // inicio del grupo (group * m)

            int idx1 = k + j;
            int idx2 = idx1 + half_m;

            int tw_index = j * num_groups;    // = j * (N/m), en [0, N/2)

            float wr = tw_real[tw_index];
            float wi = tw_imag[tw_index];

            float ar = data_real[idx1];
            float ai = data_imag[idx1];
            float br = data_real[idx2];
            float bi = data_imag[idx2];

            // t = b * W
            float tr = br * wr - bi * wi;
            float ti = br * wi + bi * wr;

            data_real[idx1] = ar + tr;
            data_imag[idx1] = ai + ti;
            data_real[idx2] = ar - tr;
            data_imag[idx2] = ai - ti;
        }
    }

    // -----------------------------------------------------------------
    // 4) Escritura del resultado (orden natural, DIT no requiere
    //    reordenamiento final)
    // -----------------------------------------------------------------
    output_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = data_real[i];
        y_imag[i] = data_imag[i];
    }
}
