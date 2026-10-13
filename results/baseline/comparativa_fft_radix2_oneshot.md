# Baseline vs pipeline — fft_radix2 (oneshot)

Baseline: Claude escribe HLS C++ directamente, sin agentes; 20 runs independientes por objetivo. Pipeline: el kernel de `results/catalogo/` para ese objetivo. Dispositivo y reloj objetivo idénticos (3.33 ns).

## 1. Fiabilidad del baseline (embudo por etapas)

| Etapa | II ≤ 20 | II ≤ 10 | II ≤ 5 |
|---|---|---|---|
| Funcionalmente correcto (csim vs golden) | 20/20 (100 %; IC95 84–100 %) | 20/20 (100 %; IC95 84–100 %) | 20/20 (100 %; IC95 84–100 %) |
| Síntesis termina (< 30 min) | 17/20 (85 %; IC95 64–95 %) | 15/20 (75 %; IC95 53–89 %) | 14/20 (70 %; IC95 48–85 %) |
| **Éxito (criterio L4: correcto + II ≤ objetivo)** | **16/20 (80 %; IC95 58–92 %)** | **6/20 (30 %; IC95 15–52 %)** | **4/20 (20 %; IC95 8–42 %)** |
| Éxito estricto (+ cierra timing + latencia acotada) | 5/20 (25 %; IC95 11–47 %) | 3/20 (15 %; IC95 5–36 %) | 4/20 (20 %; IC95 8–42 %) |
| Timeout de síntesis | 3/20 (15 %; IC95 5–36 %) | 5/20 (25 %; IC95 11–47 %) | 6/20 (30 %; IC95 15–52 %) |
| Sintetizados que NO cierran timing | 10/17 | 8/15 | 10/14 |
| Sintetizados con latencia no acotada | 3/17 | 4/15 | 1/14 |
| Diseño más repetido (II, reloj est.) y frecuencia | II=14, 4.405 ns: 9/20 | II=14, 4.405 ns: 6/20 | II=14, 4.405 ns: 10/20 |

## 2. Calidad del diseño (QoR): pipeline vs baseline

Baseline: mediana [P25–P75] sobre los runs con éxito (criterio L4), y el mejor de ellos (menor t_FFT). t_FFT en µs; ver definición al final.

### Objetivo II ≤ 20

| Métrica | Pipeline (catálogo) | Baseline, mediana [IQR] (n=16) | Baseline, mejor run |
|---|---|---|---|
| II (peor bucle) | 20 | 14 [2–14] | 1 |
| Latencia (ciclos) | 73 205 | 73 741 [13 100–73 741] | 7 405 |
| Reloj estimado (ns) | 2.846 | 4.405 [2.419–4.405] | 2.400 |
| **t_FFT (µs)** | 243.8 | 324.8 [43.6–324.8] | 24.7 |
| LUT | 16 299 | 2 041 [1 951–2 309] | 7 040 |
| FF | 17 542 | 1 666 [1 460–2 999] | 10 314 |
| DSP | 19 | 12 [12–12] | 24 |
| BRAM | 0 | 6 [6–8] | 10 |
| Cierra timing (≤ 3.33 ns) | sí | 6/16 éxitos | sí |

### Objetivo II ≤ 10

| Métrica | Pipeline (catálogo) | Baseline, mediana [IQR] (n=6) | Baseline, mejor run |
|---|---|---|---|
| II (peor bucle) | 10 | 2 [2–2] | 1 |
| Latencia (ciclos) | 37 770 | 12 321 [9 863–14 881] | 7 405 |
| Reloj estimado (ns) | 2.673 | 2.400 [2.400–2.400] | 2.400 |
| **t_FFT (µs)** | 125.8 | 41.0 [32.8–49.6] | 24.7 |
| LUT | 22 075 | 2 493 [2 060–2 926] | 7 040 |
| FF | 28 526 | 2 914 [2 448–3 458] | 10 314 |
| DSP | 38 | 12 [12–12] | 24 |
| BRAM | 0 | 10 [7–12] | 10 |
| Cierra timing (≤ 3.33 ns) | sí | 6/6 éxitos | sí |

### Objetivo II ≤ 5

| Métrica | Pipeline (catálogo) | Baseline, mediana [IQR] (n=4) | Baseline, mejor run |
|---|---|---|---|
| II (peor bucle) | 5 | 2 [2–2] | 1 |
| Latencia (ciclos) | 20 032 | 12 329 [11 093–12 393] | 7 406 |
| Reloj estimado (ns) | 2.633 | 2.400 [2.400–2.405] | 2.400 |
| **t_FFT (µs)** | 66.7 | 41.1 [36.9–41.3] | 24.7 |
| LUT | 37 624 | 2 637 [2 108–36 253] | 135 713 |
| FF | 46 981 | 3 514 [2 807–81 693] | 314 436 |
| DSP | 76 | 18 [12–24] | 24 |
| BRAM | 0 | 7 [6–9] | 8 |
| Cierra timing (≤ 3.33 ns) | sí | 4/4 éxitos | sí |

## 3. ¿El objetivo de II guía al baseline?

Si el objetivo condujera el diseño, la latencia debería bajar al endurecerlo. Se miran TODOS los diseños sintetizados (no solo los éxitos).

| Métrica | II ≤ 20 | II ≤ 10 | II ≤ 5 |
|---|---|---|---|
| Latencia, mediana [IQR] (ciclos) | 73 741 [23 952–73 741] | 73 741 [43 030–75 288] | 73 741 [12 565–73 742] |
| t_FFT, mediana [IQR] (µs) | 324.8 [94.9–324.8] | 324.8 [180.2–338.0] | 324.8 [41.8–324.8] |
| Pipeline: latencia (ciclos) | 73 205 | 37 770 | 20 032 |
| Pipeline: t_FFT (µs) | 243.8 | 125.8 | 66.7 |

## 4. Coste del baseline

| Métrica | II ≤ 20 | II ≤ 10 | II ≤ 5 |
|---|---|---|---|
| pass@1 / pass@3 / pass@5 (criterio L4) | 0.80 / 1.00 / 1.00 | 0.30 / 0.68 / 0.87 | 0.20 / 0.51 / 0.72 |
| pass@1 / pass@5 (estricto) | 0.25 / 0.81 | 0.15 / 0.60 | 0.20 / 0.72 |
| Tiempo por run, mediana (min) | 3.3 | 3.5 | 3.7 |
| Tiempo total de los runs (h) | 2.5 | 3.6 | 4.4 |
| Tiempo esperado por éxito L4 (min) | 9.4 | 35.9 | 66.0 |
| Tiempo esperado por éxito estricto (min) | 30.2 | 71.8 | 66.0 |
| Generación LLM, mediana (s) | 142 | 164 | 155 |
| Tokens de salida, mediana | 12 640 | 14 124 | 12 986 |

## Definiciones y advertencias

- **Éxito (criterio L4)**: csim correcta contra el mismo golden y vector que L2 (|diff| < 1e-3) + síntesis terminada en < 30 min + peor PipelineII ≤ objetivo. Es el criterio con el que el pipeline acepta un kernel.
- **Éxito estricto**: además, reloj estimado ≤ periodo objetivo y latencia acotada por Vitis.
- **t_FFT** = latencia × max(3.33 ns, reloj estimado). Estimaciones de csynth, antes de place & route.
- El **II** solo es el del peor bucle pipelineado: un diseño con II bajo pero bucles secuenciales puede ser lento. Por eso se compara sobre todo t_FFT y área.
- **IC95**: Wilson. **pass@k**: estimador insesgado de Chen et al. (2021) sobre los n runs.
- **Asimetría a declarar**: el pipeline aporta UN diseño convergido por objetivo (catálogo); su tasa de éxito y su coste por ejecución no están medidos con la misma n que el baseline.
