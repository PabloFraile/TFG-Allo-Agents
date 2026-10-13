#include <hls_math.h>

// -----------------------------------------------------------------------
// Radix-2 Cooley-Tukey FFT (decimation-in-time, iterative, in-place)
// N = 1024 points, complex input/output represented as separate
// real/imag float arrays.
// -----------------------------------------------------------------------

static const int FFT_N      = 1024;
static const int FFT_LOG2N  = 10;
static const int FFT_HALF_N = FFT_N / 2;
static const float FFT_PI   = 3.14159265358979323846f;

// Bit-reversal de un índice de FFT_LOG2N bits. El bucle interno tiene
// un trip-count constante en tiempo de compilación (10) y se
// desenrolla/inlinea por completo, por lo que no introduce ningún
// problema de pipeline extra en la función que lo llama.
static inline unsigned bit_reverse(unsigned x) {
#pragma HLS INLINE
    unsigned r = 0;
    for (int i = 0; i < FFT_LOG2N; i++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1u);
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

    // Buffers ping-pong para las etapas de mariposa, mapeados a BRAM
    // de doble puerto verdadero para que dos lecturas simultáneas
    // (del buffer "actual") y dos escrituras simultáneas (al buffer
    // "siguiente") puedan atenderse cada ciclo; esto es lo que permite
    // que el bucle interno de mariposa alcance II = 1 (muy por debajo
    // del objetivo II <= 10).
    static float realA[FFT_N];
    static float imagA[FFT_N];
    static float realB[FFT_N];
    static float imagB[FFT_N];
#pragma HLS BIND_STORAGE variable=realA type=ram_t2p impl=bram
#pragma HLS BIND_STORAGE variable=imagA type=ram_t2p impl=bram
#pragma HLS BIND_STORAGE variable=realB type=ram_t2p impl=bram
#pragma HLS BIND_STORAGE variable=imagB type=ram_t2p impl=bram

    // Tablas de factores de giro (twiddle): W_N^k = cos(-2*pi*k/N) +
    // j*sin(-2*pi*k/N) para k = 0 .. N/2-1. Se calculan una vez por
    // invocación; el bucle también está pipelineado para respetar el
    // objetivo II <= 10.
    static float cos_table[FFT_HALF_N];
    static float sin_table[FFT_HALF_N];

TWIDDLE_GEN:
    for (int i = 0; i < FFT_HALF_N; i++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * FFT_PI * (float)i / (float)FFT_N;
        cos_table[i] = hls::cosf(angle);
        sin_table[i] = hls::sinf(angle);
    }

    // Permutación bit-reversal de las muestras de entrada hacia el buffer A.
BITREV:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        unsigned j = bit_reverse((unsigned)i);
        realA[j] = x_real[i];
        imagA[j] = x_imag[i];
    }

    // Etapas iterativas de mariposa radix-2.
    float *curR = realA, *curI = imagA;
    float *nxtR = realB, *nxtI = imagB;

STAGE:
    for (int stage = 0; stage < FFT_LOG2N; stage++) {
        const int half = 1 << stage;           // mitad del tamaño de sub-FFT
        const int step = FFT_N >> (stage + 1); // paso del índice de twiddle

        if (stage % 2 == 0) {
            curR = realA; curI = imagA;
            nxtR = realB; nxtI = imagB;
        } else {
            curR = realB; curI = imagB;
            nxtR = realA; nxtI = imagA;
        }

    BUTTERFLY:
        for (int bfly = 0; bfly < FFT_HALF_N; bfly++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT min=512 max=512

            int j      = bfly & (half - 1);
            int kgroup = (bfly >> stage) << (stage + 1);
            int idx1   = kgroup + j;
            int idx2   = idx1 + half;
            int twIdx  = j * step;

            float tw_r = cos_table[twIdx];
            float tw_i = sin_table[twIdx];

            float a_r = curR[idx1];
            float a_i = curI[idx1];
            float b_r = curR[idx2];
            float b_i = curI[idx2];

            float t_r = b_r * tw_r - b_i * tw_i;
            float t_i = b_r * tw_i + b_i * tw_r;

            nxtR[idx1] = a_r + t_r;
            nxtI[idx1] = a_i + t_i;
            nxtR[idx2] = a_r - t_r;
            nxtI[idx2] = a_i - t_i;
        }
    }

    // Tras FFT_LOG2N (número par de) etapas, el resultado final queda
    // de nuevo en el buffer A (realA/imagA). Se copia a los puertos de salida.
OUTPUT_COPY:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = realA[i];
        y_imag[i] = imagA[i];
    }
}
