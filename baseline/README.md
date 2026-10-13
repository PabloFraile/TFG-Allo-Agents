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
