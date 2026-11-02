# Baseline: Claude → HLS C++ → Vitis HLS, sin agentes

Grupo de control del TFG. Responde a la pregunta *"¿y no bastaba con
pedirle el acelerador directamente al LLM?"* con números, en las mismas
condiciones que el pipeline de 3 agentes.

## Qué se compara

| | Pipeline (src/agentes) | Baseline (esta carpeta) |
|---|---|---|
| Entrada | `specs/*.yaml` | **la misma** `specs/*.yaml` (más la firma C++ y el objetivo de síntesis, que exige el cambio de lenguaje; el golden model **no** se describe, igual que al Generador) |
| Lenguaje que escribe el LLM | Allo (subconjunto restringido) | HLS C++ libre, con pragmas de Vitis |
| Modelo | el del Agent SDK | **el mismo**, mismas opciones (`allowed_tools=[]`, `dontAsk`) |
| Corrección funcional | L2: `golden_models.py`, vector seed 0, `|diff| < 1e-3` | csim de Vitis con **el mismo golden, el mismo vector y la misma tolerancia** (testbench generado por el arnés, no por el LLM) |
| Equivalencia formal | L3 (`allo.verify`) | **no existe equivalente** — diferencia cualitativa |
| Síntesis | L4: `xcu280-fsvh2892-2L-e`, 3.33 ns, `flow_target vivado`, timeout 1800 s | **idéntico** |
| II medido | máximo `PipelineII` entre informe top y submódulos | **mismo criterio** |
| Lazo de corrección | Validador + escalada (regenerar / congelar kernel) | `oneshot`: ninguno · `feedback`: se le devuelve la salida de Vitis tal cual, sin Validador |

Del pipeline solo se reutiliza `src/agentes/golden_models.py` (la referencia
numérica, no un agente). Nada de `orchestrator.py`, `allo_tools.py` ni
`schemas.py`.

El prompt no da pistas de diseño (particionado, dataflow, etc.): eso es lo
que el pipeline descubre por sí mismo y darlo aquí sesgaría la comparación.

## Uso

Desde `TFG/baseline`, con el entorno de Vitis ya cargado (igual que para el
orquestador). Al ser ejecuciones que cuentan como evidencia, se lanzan desde
terminal:

```bash
source <ruta_Vitis_HLS_2023.1>/settings64.sh
cd ~/TFG/baseline

# pass@1: lo que haría cualquiera (5 runs independientes por punto)
python3 -u generar_baseline.py --runs 5 --objetivo-ii 20
python3 -u generar_baseline.py --runs 5 --objetivo-ii 10
python3 -u generar_baseline.py --runs 5 --objetivo-ii 5

# variante intermedia: C++ + lazo con el compilador (hasta 6 intentos, como MAX_ITERACIONES)
python3 -u generar_baseline.py --runs 5 --objetivo-ii 10 --modo feedback

# otro bloque, misma spec que el pipeline
python3 -u generar_baseline.py --spec ../specs/spec_fft_radix4.yaml --runs 5 --objetivo-ii 5

# tabla resumen + comparación con results/catalogo/<bloque>_ii<N>.json
python3 resumir.py

# tablas para la memoria: IC95, pass@k, t_FFT, QoR vs pipeline, coste + figura
python3 comparativa.py
```

Corridas largas en segundo plano, igual que el orquestador:

```bash
LOG=baseline_$(date +%Y%m%d_%H%M).log
nohup python3 -u generar_baseline.py --runs 5 --objetivo-ii 10 > "$LOG" 2>&1 & disown
```

Es **reanudable**: los runs con `resultado.json` se saltan. Si el SDK falla
(cuota de Pro, issue #1031) el script se para sin registrar ese run como
fallo del modelo; se relanza el mismo comando y continúa.

## Qué guarda

```
results/baseline/<bloque>/ii<N>_<modo>/
├── config.json                 <- spec, part, reloj, tolerancia, system prompt...
└── run_01/
    ├── resultado.json          <- éxito, nº de intentos, etapa de fallo, métricas
    └── intento_01/
        ├── prompt.txt, respuesta.txt, kernel.cpp
        ├── tb.cpp, vectores.h, run.tcl      <- generados por el arnés
        ├── vitis.log
        └── informes_csynth/                 <- *_csynth.xml/.rpt (proj/ se borra, ocupa mucho)
```

`resumir.py` escribe `results/baseline/resumen.md` (tablas listas para la
memoria) y `runs.csv` (una fila por run, para gráficas).

## Métricas

- Embudo por etapas: devuelve código → compila → **funcionalmente correcto**
  → sintetiza → cumple II → **éxito** (correcto *y* cumple II).
- **Sintetiza pero es incorrecto**: el caso que más justifica el pipeline;
  un flujo que solo mira si Vitis termina daría por bueno ese diseño.
- Etapa de fallo del intento final: `sin_codigo`, `interfaz` (firma distinta
  de la pedida), `compilacion`, `funcional`, `sintesis`,
  `timeout_sintesis`, `ii`.
- Métricas HLS (II, latencia, reloj, BRAM/DSP/LUT/FF) del mejor éxito y la
  mediana de éxitos, junto a las del catálogo del pipeline.
- Intentos y tiempo por run.

## Limitaciones a declarar en la memoria

- La comparación de recursos solo tiene sentido entre diseños correctos y
  con el mismo `objetivo_ii`.
- El II es el peor `PipelineII` de los bucles pipelineados. Si un diseño no
  pipelinea ningún bucle (o usa DATAFLOW), `II` queda vacío y no cumple el
  objetivo; `intervalo_top` en `resultado.json` permite revisarlo a mano.
- `cumple_reloj_estimado` (reloj estimado de csynth <= objetivo) se registra pero no entra en el éxito, igual que en L4.
- En Ubuntu 24.04 la csim de Vitis 2023.1 necesita enlazar con el `ld` del sistema (`CSIM_LDFLAGS` en `arnes.py`); si la csim falla por el entorno, el run se aparta y no cuenta como fallo del modelo.
- csim valida contra un único vector (el mismo que L2) por defecto.
  `--n-vectores 3` endurece el criterio del baseline; para que la
  comparación siga siendo justa habría que endurecer igual L2.

## Baseline VHDL (Claude → VHDL → GHDL + Vivado, sin agentes)

Tercera aproximación. Mismo planteamiento que el baseline C++ en modo
`oneshot`: **un solo intento por run, sin lazo de corrección**, como si se le
pidiera el bloque a Claude sin hacer nada más.

| | Baseline C++ | Baseline VHDL |
|---|---|---|
| Entrada | spec + firma C++ + objetivo de síntesis | **la misma** spec (sin `objetivo_ii`, que no significa nada en RTL) + entidad VHDL obligatoria + protocolo de interfaz + dispositivo y reloj |
| Compilación | csim de Vitis | análisis con GHDL (`--std=08`) |
| Interfaz | `undefined reference` al top | el testbench no elabora contra la entidad generada |
| Corrección funcional | csim, mismo golden / vector / tolerancia que L2 | simulación GHDL con testbench del arnés; comparación en Python con el mismo golden / vector / tolerancia |
| Síntesis | csynth, mismo part y reloj, timeout 1800 s | `synth_design -mode out_of_context` de Vivado, mismo part y reloj, timeout 1800 s |
| Rendimiento | II (peor bucle) + latencia csynth | latencia start→done medida en simulación × periodo estimado (WNS) |
| Éxito | correcto + II ≤ objetivo | correcto + síntesis termina (estricto: + WNS ≥ 0) |

Interfaz fija (la genera `arnes_vhdl.entidad_vhdl` a partir de la spec):
memoria de entrada con puerto de escritura (`in_we`, `in_addr`, `x_real`,
`x_imag`), pulso `start`, nivel `done`, memoria de salida con puerto de
lectura (`out_addr`, `y_real`, `y_imag`), datos IEEE-754 binary32. Solo
bibliotecas estándar IEEE (se permite `float_pkg`); sin IP de Vivado, porque
el flujo no la genera.

```bash
sudo apt install ghdl                      # GHDL 4.1 en Ubuntu 24.04
source <ruta_Vivado_2023.1>/settings64.sh  # vivado en el PATH
cd ~/TFG/baseline

# comprobación del arnés sin gastar cuota (valida un kernel.vhd escrito a mano)
python3 generar_baseline_vhdl.py --probar-kernel mi_kernel.vhd

# 20 runs independientes, un solo intento cada uno
LOG=baseline_vhdl_$(date +%Y%m%d_%H%M).log
nohup python3 -u generar_baseline_vhdl.py --runs 20 > "$LOG" 2>&1 & disown

# tablas + comparación con C++ y pipeline
python3 resumir_vhdl.py
```

Si Vivado no está instalado o no tiene licencia para el dispositivo,
`--sin-sintesis` mide solo compilación, corrección y latencia (los runs
quedan con `etapa_fallo = sin_sintesis` y no cuentan como éxito).

Resultados en `results/baseline/<bloque>/vhdl_oneshot/run_XX/intento_01/`
(`prompt.txt`, `respuesta.txt`, `kernel.vhd`, `tb.vhd`, `vectores_in.txt`,
`salida.txt`, `ghdl.log`, `vivado.log`, `informes_vivado/`).

Asimetrías a declarar en la memoria: la latencia VHDL no incluye la carga ni
la lectura de los datos (la de HLS sí); los recursos VHDL vienen de
`synth_design` y los de HLS de la estimación de csynth.
