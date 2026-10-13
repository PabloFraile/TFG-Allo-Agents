#include <hls_math.h>

// ---------------------------------------------------------------------
// FFT radix-2 (Cooley-Tukey, Decimation In Time) para N = 1024 puntos
// ---------------------------------------------------------------------
#define FFT_N     1024
#define FFT_LOGN  10
#define FFT_NH    (FFT_N / 2)

namespace {

// Inversión de bits de un índice de FFT_LOGN bits (para el reordenamiento
// bit-reversal del algoritmo DIT iterativo).
inline unsigned bit_reverse(unsigned x, int bits) {
#pragma HLS INLINE
    unsigned r = 0;
    for (int i = 0; i < bits; i++) {
#pragma HLS UNROLL
        r = (r << 1) | (x & 1u);
        x >>= 1;
    }
    return r;
}

} // namespace

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
) {

    // Buffers internos de trabajo (complejo entrelazado real/imag)
    float real_buf[FFT_N];
    float imag_buf[FFT_N];
#pragma HLS ARRAY_PARTITION variable=real_buf complete dim=1
#pragma HLS ARRAY_PARTITION variable=imag_buf complete dim=1

    // Tabla de factores twiddle: W_N^k = exp(-j*2*pi*k/N), k = 0..N/2-1
    float tw_real[FFT_NH];
    float tw_imag[FFT_NH];
#pragma HLS ARRAY_PARTITION variable=tw_real complete dim=1
#pragma HLS ARRAY_PARTITION variable=tw_imag complete dim=1

    const float TWO_PI = 6.283185307179586f;

    // -------------------------------------------------------------
    // 1) Generación de los factores twiddle
    // -------------------------------------------------------------
twiddle_gen:
    for (int i = 0; i < FFT_NH; i++) {
#pragma HLS PIPELINE II=1
        float angle = -TWO_PI * (float)i / (float)FFT_N;
        tw_real[i] = hls::cosf(angle);
        tw_imag[i] = hls::sinf(angle);
    }

    // -------------------------------------------------------------
    // 2) Reordenamiento bit-reversal de la entrada
    // -------------------------------------------------------------
bitrev_load:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        unsigned ridx = bit_reverse((unsigned)i, FFT_LOGN);
        real_buf[i] = x_real[ridx];
        imag_buf[i] = x_imag[ridx];
    }

    // -------------------------------------------------------------
    // 3) Etapas iterativas de mariposas radix-2 (Cooley-Tukey DIT)
    //    stage = 0 .. LOGN-1
    //    half  = tamano de la mitad de la sub-FFT en esta etapa
    //    m     = tamano total de la sub-FFT (= 2*half)
    // -------------------------------------------------------------
stage_loop:
    for (int stage = 0; stage < FFT_LOGN; stage++) {
        const int half      = 1 << stage;
        const int tw_stride = FFT_N >> (stage + 1);

    butterfly_loop:
        for (int i = 0; i < FFT_NH; i++) {
#pragma HLS PIPELINE II=5
            int j    = i & (half - 1);
            int k    = (i >> stage) << (stage + 1);
            int idx0 = k + j;
            int idx1 = idx0 + half;
            int twi  = j * tw_stride;

            float ar = real_buf[idx0];
            float ai = imag_buf[idx0];
            float br = real_buf[idx1];
            float bi = imag_buf[idx1];
            float wr = tw_real[twi];
            float wi = tw_imag[twi];

            // producto complejo: t = b * w
            float tr = br * wr - bi * wi;
            float ti = br * wi + bi * wr;

            // mariposa: a' = a + t ; b' = a - t
            real_buf[idx0] = ar + tr;
            imag_buf[idx0] = ai + ti;
            real_buf[idx1] = ar - tr;
            imag_buf[idx1] = ai - ti;
        }
    }

    // -------------------------------------------------------------
    // 4) Escritura del resultado
    // -------------------------------------------------------------
output_store:
    for (int i = 0; i < FFT_N; i++) {
#pragma HLS PIPELINE II=1
        y_real[i] = real_buf[i];
        y_imag[i] = imag_buf[i];
    }
}
