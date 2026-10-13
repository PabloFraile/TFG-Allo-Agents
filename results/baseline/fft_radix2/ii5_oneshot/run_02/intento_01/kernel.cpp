// kernel.cpp
// FFT radix-2 (Cooley-Tukey, Decimation-In-Time) de 1024 puntos, complejo -> complejo.
// Implementacion iterativa in-place con permutacion bit-reversed y tabla de
// factores "twiddle" precalculada en hardware (loop dedicado), pensada para
// Vitis HLS 2023.1 / xcu280-fsvh2892-2L-e @ 3.33 ns, con II <= 5 en todos los
// bucles pipelinizados.

#include <cmath>

static const int FFT_N    = 1024;
static const int FFT_LOGN = 10;              // log2(1024)
static const float PI_F   = 3.14159265358979323846f;

// Inversion de bits de un indice de FFT_LOGN bits. Al ser FFT_LOGN una
// constante en tiempo de compilacion, HLS despliega este bucle por completo
// y lo sintetiza como logica combinacional (sin impacto en II).
static inline unsigned bit_reverse(unsigned x) {
#pragma HLS INLINE
    unsigned r = 0;
    for (int i = 0; i < FFT_LOGN; i++) {
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
    // Buffers internos in-place para las muestras complejas.
    float real[FFT_N];
    float imag[FFT_N];
#pragma HLS ARRAY_PARTITION variable=real complete dim=1
#pragma HLS ARRAY_PARTITION variable=imag complete dim=1

    // Tabla de factores twiddle W_N^k = cos(-2*pi*k/N) + j*sin(-2*pi*k/N),
    // k = 0 .. N/2-1 (suficiente para todas las etapas, indexando con stride).
    float w_real[FFT_N / 2];
    float w_imag[FFT_N / 2];

    // --- Carga inicial con permutacion bit-reversed ---
bitrev_load:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        unsigned r = bit_reverse((unsigned)i);
        real[i] = x_real[r];
        imag[i] = x_imag[r];
    }

    // --- Precalculo de la tabla de twiddles ---
twiddle_gen:
    for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II=1
        float angle = (-2.0f * PI_F * (float)k) / (float)FFT_N;
        w_real[k] = cosf(angle);
        w_imag[k] = sinf(angle);
    }

    // --- Etapas de la FFT iterativa (Cooley-Tukey, DIT) ---
    // s = 1 .. log2(N); en cada etapa el tamano de "mariposa" es m = 2^s.
stages:
    for (int s = 1; s <= FFT_LOGN; s++) {
        const int shift = s - 1;          // log2(half)
        const int half  = 1 << shift;     // m/2
        const int tstep = FFT_LOGN - s;    // exponente del stride en la tabla

    butterflies:
        for (int k = 0; k < FFT_N / 2; k++) {
#pragma HLS PIPELINE II=5
            int group = k >> shift;            // indice del grupo de mariposas
            int j     = k & (half - 1);         // posicion dentro del grupo
            int idx1  = (group << s) | j;       // elemento superior
            int idx2  = idx1 | half;            // elemento inferior (idx1+half)
            int widx  = j << tstep;             // j * (N/m)

            float wr = w_real[widx];
            float wi = w_imag[widx];

            float xr2 = real[idx2];
            float xi2 = imag[idx2];

            // Producto complejo: t = x[idx2] * W
            float tr = xr2 * wr - xi2 * wi;
            float ti = xr2 * wi + xi2 * wr;

            float xr1 = real[idx1];
            float xi1 = imag[idx1];

            real[idx1] = xr1 + tr;
            imag[idx1] = xi1 + ti;
            real[idx2] = xr1 - tr;
            imag[idx2] = xi1 - ti;
        }
    }

    // --- Escritura de resultados ---
write_out:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real[i];
        y_imag[i] = imag[i];
    }
}
