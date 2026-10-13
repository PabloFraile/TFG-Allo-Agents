// kernel.cpp
// FFT radix-2 (Cooley-Tukey, Decimation-In-Time, iterativa) para N = 1024 puntos.
// Entrada/salida complejas separadas en parte real e imaginaria.
// Objetivo: II <= 5 en todos los bucles pipelineados (Vitis HLS 2023.1, xcu280, 3.33 ns).

#include <hls_math.h>

static const int   FFT_N    = 1024;
static const int   FFT_LOGN = 10;      // log2(1024)
static const int   HALF_N   = 512;     // FFT_N / 2
static const float PI_CONST = 3.14159265358979323846f;

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
)
{
    // Buffers internos de trabajo (in-place a lo largo de las etapas).
    // Particionado completo: en cada ciclo de la mariposa se necesitan
    // 2 lecturas + 2 escrituras simultaneas sobre el mismo array, lo cual
    // excede los puertos de una BRAM TDP; con partición completa cada
    // elemento es un registro independiente y no hay conflicto de puertos.
    float re[FFT_N];
    float im[FFT_N];
#pragma HLS ARRAY_PARTITION variable=re complete dim=1
#pragma HLS ARRAY_PARTITION variable=im complete dim=1

    // Tabla de factores de giro (twiddle factors): TW[k] = exp(-j*2*pi*k/N)
    // Solo lectura durante las mariposas (1 lectura/ciclo por array) -> no
    // necesita partición.
    float tw_re[HALF_N];
    float tw_im[HALF_N];

    const float ang_step = -2.0f * PI_CONST / (float)FFT_N;

compute_twiddle:
    for (int k = 0; k < HALF_N; k++) {
#pragma HLS PIPELINE II=5
        float angle = ang_step * (float)k;
        tw_re[k] = hls::cosf(angle);
        tw_im[k] = hls::sinf(angle);
    }

    // Carga de la entrada aplicando permutación por inversión de bits
    // (requisito de la FFT iterativa "decimation in time").
bitrev_load:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=5
        int rev = 0;
        int v   = i;
    bitrev_bits:
        for (int b = 0; b < FFT_LOGN; b++) {
            rev = (rev << 1) | (v & 1);
            v >>= 1;
        }
        re[i] = x_real[rev];
        im[i] = x_imag[rev];
    }

    // 10 etapas de mariposas radix-2 (Cooley-Tukey, geometria in-place).
stage_loop:
    for (int stage = 0; stage < FFT_LOGN; stage++) {
        int half      = 1 << stage;       // distancia media de la mariposa
        int len       = half << 1;        // tamaño de bloque de la etapa
        int tw_stride = FFT_N / len;       // paso en la tabla de twiddles

    butterfly_loop:
        for (int idx = 0; idx < HALF_N; idx++) {
#pragma HLS PIPELINE II=5
            int group = idx / half;
            int j     = idx % half;
            int base  = group * len;
            int tidx  = j * tw_stride;

            int a = base + j;
            int b = base + j + half;

            float ar = re[a];
            float ai = im[a];
            float br = re[b];
            float bi = im[b];
            float wr = tw_re[tidx];
            float wi = tw_im[tidx];

            // t = w * b
            float tr = br * wr - bi * wi;
            float ti = br * wi + bi * wr;

            re[a] = ar + tr;
            im[a] = ai + ti;
            re[b] = ar - tr;
            im[b] = ai - ti;
        }
    }

    // Escritura de la salida.
write_out:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=5
        y_real[i] = re[i];
        y_imag[i] = im[i];
    }
}
