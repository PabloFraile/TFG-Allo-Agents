// Testbench generado por baseline/arnes.py -- NO lo escribe el LLM.
// Mismo golden model, mismos vectores y misma tolerancia que L2 del pipeline.
#include <cstdio>
#include <cstring>
#include <cmath>
#include "vectores.h"

void fft_radix2(
    const float x_real[1024],
    const float x_imag[1024],
    float y_real[1024],
    float y_imag[1024]
);

static const double TOL = 0.001;

int main() {
  int fallos = 0;
  for (int v = 0; v < N_VEC; v++) {
    static float x_real[1024];
    static float x_imag[1024];
    static float y_real[1024];
    static float y_imag[1024];
    std::memcpy(x_real, VEC_IN_x_real[v], sizeof(x_real));
    std::memcpy(x_imag, VEC_IN_x_imag[v], sizeof(x_imag));
    std::memset(y_real, 0, sizeof(y_real));
    std::memset(y_imag, 0, sizeof(y_imag));
    fft_radix2(x_real, x_imag, y_real, y_imag);
    {
      const float *plano = reinterpret_cast<const float *>(y_real);
      const int tam = (int)(sizeof(y_real) / sizeof(plano[0]));
      int malos = 0; double max_diff = 0.0;
      for (int i = 0; i < tam; i++) {
        double d = std::fabs((double)plano[i] - (double)VEC_REF_y_real[v][i]);
        if (!(d < TOL)) { malos++; }            // NaN cuenta como fallo
        if (d > max_diff || d != d) max_diff = d;
      }
      std::printf("BASELINE_VEC %d salida=y_real discrepantes=%d/%d max_abs_diff=%.6g tol=%g\n",
                  v, malos, tam, max_diff, TOL);
      if (malos) fallos++;
    }
    {
      const float *plano = reinterpret_cast<const float *>(y_imag);
      const int tam = (int)(sizeof(y_imag) / sizeof(plano[0]));
      int malos = 0; double max_diff = 0.0;
      for (int i = 0; i < tam; i++) {
        double d = std::fabs((double)plano[i] - (double)VEC_REF_y_imag[v][i]);
        if (!(d < TOL)) { malos++; }            // NaN cuenta como fallo
        if (d > max_diff || d != d) max_diff = d;
      }
      std::printf("BASELINE_VEC %d salida=y_imag discrepantes=%d/%d max_abs_diff=%.6g tol=%g\n",
                  v, malos, tam, max_diff, TOL);
      if (malos) fallos++;
    }
  }
  std::printf("BASELINE_RESULT %s\n", fallos ? "FAIL" : "PASS");
  return fallos ? 1 : 0;
}
