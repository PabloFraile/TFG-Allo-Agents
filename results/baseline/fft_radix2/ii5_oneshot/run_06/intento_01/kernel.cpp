#include <hls_math.h>

#define FFT_N    1024
#define FFT_LOGN 10
#define FFT_HALF (FFT_N / 2)

// ---------------------------------------------------------------------------
// Bit-reversal de un indice de FFT_LOGN bits. Totalmente desenrollado,
// puramente combinacional.
// ---------------------------------------------------------------------------
static inline int bit_reverse(int x) {
#pragma HLS INLINE
    int r = 0;
BIT_REV:
    for (int i = 0; i < FFT_LOGN; i++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1);
        x >>= 1;
    }
    return r;
}

// ---------------------------------------------------------------------------
// fft_radix2: FFT radix-2 Cooley-Tukey, decimacion en tiempo (DIT),
// iterativa, in-place, de 1024 puntos complejos. Transformada directa,
// consistente con el convenio de numpy.fft.fft:
//   X[k] = sum_n x[n] * exp(-j*2*pi*k*n/N)
// ---------------------------------------------------------------------------
void fft_radix2(
    const float x_real[FFT_N],
    const float x_imag[FFT_N],
    float y_real[FFT_N],
    float y_imag[FFT_N])
{
    // Tablas de factores de giro (twiddle factors):
    //   W_N^k = cos(2*pi*k/N) - j*sin(2*pi*k/N)
    // Se calculan una unica vez (de forma perezosa, en la primera
    // invocacion) y permanecen residentes en registros entre llamadas:
    // no forman parte de ningun bucle pipelineado, por lo que no
    // afectan al II reportado del diseno ni al throughput en regimen
    // estacionario.
    static float tw_cos[FFT_HALF];
    static float tw_sin[FFT_HALF];
    static bool  tw_ready = false;

    if (!tw_ready) {
    TW_INIT:
        for (int k = 0; k < FFT_HALF; k++) {
            float theta = (2.0f * 3.14159265358979323846f * (float)k) / (float)FFT_N;
            tw_cos[k] = hls::cosf(theta);
            tw_sin[k] = hls::sinf(theta);
        }
        tw_ready = true;
    }

    // Buffers de trabajo, completamente particionados: cada elemento se
    // comporta como un registro independiente, de modo que las etapas de
    // mariposa nunca compiten por un puerto de memoria. Esto es lo que
    // permite que el bucle interno se pipeline con II=1.
    float a_real[FFT_N];
    float a_imag[FFT_N];
#pragma HLS ARRAY_PARTITION variable=a_real complete dim=1
#pragma HLS ARRAY_PARTITION variable=a_imag complete dim=1

    // Carga de la entrada directamente en orden bit-invertido.
LOAD:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        int r = bit_reverse(i);
        a_real[i] = x_real[r];
        a_imag[i] = x_imag[r];
    }

    // log2(N) etapas de mariposa.
STAGE:
    for (int s = 0; s < FFT_LOGN; s++) {
        int half_m = 1 << s;          // distancia entre elementos de la mariposa
        int m      = half_m << 1;     // tamano de la sub-DFT combinada en esta etapa
        int step   = FFT_HALF >> s;   // paso de indexacion en la tabla de twiddles

    BUTTERFLY:
        for (int idx = 0; idx < FFT_HALF; idx++) {
#pragma HLS PIPELINE II=1
            int j     = idx & (half_m - 1);
            int group = idx >> s;
            int k     = group * m;
            int i0    = k + j;
            int i1    = i0 + half_m;
            int tidx  = j * step;

            float wr = tw_cos[tidx];
            float wi = tw_sin[tidx];

            float ar1 = a_real[i1];
            float ai1 = a_imag[i1];

            // t = (wr - j*wi) * (ar1 + j*ai1)
            float tr = ar1 * wr + ai1 * wi;
            float ti = ai1 * wr - ar1 * wi;

            float ur = a_real[i0];
            float ui = a_imag[i0];

            a_real[i0] = ur + tr;
            a_imag[i0] = ui + ti;
            a_real[i1] = ur - tr;
            a_imag[i1] = ui - ti;
        }
    }

    // Almacenamiento del resultado (ya en orden natural).
STORE:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = a_real[i];
        y_imag[i] = a_imag[i];
    }
}
