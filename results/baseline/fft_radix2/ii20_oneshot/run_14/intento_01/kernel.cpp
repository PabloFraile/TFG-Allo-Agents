// kernel.cpp
// FFT radix-2 (Cooley-Tukey), decimacion en el tiempo (DIT), N = 1024 puntos.
// Precision en punto flotante (float), tabla de twiddle factors precalculada
// y doble buffer (ping-pong) por etapa para permitir pipelining con II bajo
// en cada etapa de mariposas.

#include <hls_math.h>

#define N 1024
#define LOGN 10          // log2(1024)
#define PI_CONST 3.14159265358979323846f

// Inversion de bits de 'x' usando LOGN bits. Se fuerza desenrollado total
// (LOGN=10, constante) para que quede como logica combinacional pura y no
// afecte al pipeline del bucle que lo invoca.
static inline unsigned bit_reverse(unsigned x) {
    unsigned r = 0;
BITREV:
    for (int i = 0; i < LOGN; i++) {
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
    float y_imag[1024])
{
    // Tabla de twiddle factors: W_N^i = exp(-j*2*pi*i/N), i = 0..N/2-1
    float tw_real[N / 2];
    float tw_imag[N / 2];

    // Doble buffer (ping-pong) para las N muestras complejas, por etapa.
    // La particion completa en dim=1 crea dos memorias independientes:
    // en cada etapa una se usa solo de lectura (src) y la otra solo de
    // escritura (dst), lo que permite 2 lecturas / 2 escrituras por ciclo
    // en una BRAM de doble puerto -> II=1 alcanzable en el bucle interno.
    float bufR[2][N];
    float bufI[2][N];
#pragma HLS ARRAY_PARTITION variable=bufR complete dim=1
#pragma HLS ARRAY_PARTITION variable=bufI complete dim=1

    // --- Precalculo de twiddle factors ---
TWIDDLE_LOOP:
    for (int i = 0; i < N / 2; i++) {
#pragma HLS PIPELINE II=1
        float angle = -2.0f * PI_CONST * (float)i / (float)N;
        tw_real[i] = hls::cosf(angle);
        tw_imag[i] = hls::sinf(angle);
    }

    // --- Reordenado por inversion de bits (bit-reversal) hacia buffer 0 ---
BITREV_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        unsigned ri = bit_reverse((unsigned)i);
        bufR[0][i] = x_real[ri];
        bufI[0][i] = x_imag[ri];
    }

    // --- Etapas de mariposas radix-2 (Cooley-Tukey, DIT) ---
STAGE_LOOP:
    for (int s = 0; s < LOGN; s++) {
        const int half_m = 1 << s;        // tamano de medio bloque en esta etapa
        const int step   = N >> (s + 1);  // paso dentro de la tabla de twiddles
        const int src    = s & 1;
        const int dst    = 1 - src;

    BUTTERFLY_LOOP:
        for (int idx = 0; idx < N / 2; idx++) {
#pragma HLS PIPELINE II=1
            int j     = idx & (half_m - 1);   // posicion dentro del medio bloque
            int group = idx >> s;             // indice de bloque (idx / half_m)
            int k     = group << (s + 1);     // inicio del bloque (group * m)
            int a     = k + j;
            int b     = a + half_m;
            int tw_idx = j * step;

            float wr = tw_real[tw_idx];
            float wi = tw_imag[tw_idx];

            float xr = bufR[src][b];
            float xi = bufI[src][b];

            float tr = wr * xr - wi * xi;
            float ti = wr * xi + wi * xr;

            float ur = bufR[src][a];
            float ui = bufI[src][a];

            bufR[dst][a] = ur + tr;
            bufI[dst][a] = ui + ti;
            bufR[dst][b] = ur - tr;
            bufI[dst][b] = ui - ti;
        }
    }

    // Tras LOGN=10 etapas (par), el resultado final queda en el buffer 0.
OUTPUT_LOOP:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = bufR[0][i];
        y_imag[i] = bufI[0][i];
    }
}
