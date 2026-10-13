// kernel.cpp
// FFT radix-2 (Cooley-Tukey), iterativa, decimacion en tiempo (DIT),
// N=1024 puntos, entrada/salida complejas en arreglos separados real/imag.
//
// Firma de top obligatoria:
//   void fft_radix2(const float x_real[1024], const float x_imag[1024],
//                    float y_real[1024], float y_imag[1024])
//
// Objetivo: xcu280-fsvh2892-2L-e, periodo de reloj 3.33 ns, II <= 5 en todos
// los bucles pipelineados.

#include <cmath>

#define FFT_N    1024
#define FFT_LOGN 10

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {
    // Buffers internos de trabajo (in-place en memoria interna).
    float real[FFT_N];
    float imag[FFT_N];

    // Tabla de factores de giro (twiddle factors) W_N^k, k = 0..N/2-1.
    float twiddle_re[FFT_N / 2];
    float twiddle_im[FFT_N / 2];

    // Particionado para permitir las 2 lecturas + 2 escrituras por
    // iteracion de la mariposa sin colapsar a un unico puerto de BRAM,
    // manteniendo el II de los bucles de mariposa dentro del objetivo (<=5).
    #pragma HLS ARRAY_PARTITION variable=real cyclic factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=imag cyclic factor=2 dim=1

    const float PI = 3.14159265358979323846f;

    // ---------------------------------------------------------------
    // 1) Generacion de la tabla de factores de giro.
    // ---------------------------------------------------------------
    for (int k = 0; k < FFT_N / 2; k++) {
        #pragma HLS PIPELINE II=1
        float angle = -2.0f * PI * (float)k / (float)FFT_N;
        twiddle_re[k] = cosf(angle);
        twiddle_im[k] = sinf(angle);
    }

    // ---------------------------------------------------------------
    // 2) Carga de la entrada con permutacion bit-reversed (requerida
    //    por el algoritmo DIT iterativo para producir salida en orden
    //    natural al finalizar las etapas).
    // ---------------------------------------------------------------
    for (int i = 0; i < FFT_N; i++) {
        #pragma HLS PIPELINE II=1
        unsigned int idx = 0;
        unsigned int ii = (unsigned int)i;
        for (int b = 0; b < FFT_LOGN; b++) {
            #pragma HLS UNROLL
            idx = (idx << 1) | (ii & 1u);
            ii >>= 1;
        }
        real[idx] = x_real[i];
        imag[idx] = x_imag[i];
    }

    // ---------------------------------------------------------------
    // 3) Etapas de mariposas radix-2 (Cooley-Tukey, DIT).
    //    log2(N) etapas secuenciales, cada una con N/2 mariposas
    //    independientes que se procesan en un bucle pipelineado.
    // ---------------------------------------------------------------
    for (int s = 1; s <= FFT_LOGN; s++) {
        const int half_m = 1 << (s - 1);   // tamano de medio bloque
        const int shift  = s - 1;
        const int step   = FFT_N >> s;     // paso en la tabla de twiddles

        for (int i = 0; i < FFT_N / 2; i++) {
            #pragma HLS PIPELINE II=1

            int j    = i & (half_m - 1);        // indice dentro del bloque
            int k    = (i >> shift) << s;        // base del bloque
            int idx1 = k + j;
            int idx2 = idx1 + half_m;

            float tw_re = twiddle_re[j * step];
            float tw_im = twiddle_im[j * step];

            float ure = real[idx2];
            float uim = imag[idx2];

            // t = u * W
            float tre = ure * tw_re - uim * tw_im;
            float tim = ure * tw_im + uim * tw_re;

            float are = real[idx1];
            float aim = imag[idx1];

            // mariposa: a' = a + t ; b' = a - t
            real[idx1] = are + tre;
            imag[idx1] = aim + tim;
            real[idx2] = are - tre;
            imag[idx2] = aim - tim;
        }
    }

    // ---------------------------------------------------------------
    // 4) Escritura de resultados (orden natural tras DIT con entrada
    //    bit-reversed).
    // ---------------------------------------------------------------
    for (int i = 0; i < FFT_N; i++) {
        #pragma HLS PIPELINE II=1
        y_real[i] = real[i];
        y_imag[i] = imag[i];
    }
}
