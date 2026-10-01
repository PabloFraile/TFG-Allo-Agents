# Generación automática de aceleradores hardware mediante LLMs sobre Allo

Trabajo de Fin de Grado (Ingeniería Industrial). Pipeline de agentes LLM
para generar código RTL (sistemas de comunicaciones y procesado de señal —
5G/6G, radar) restringido al DSL **Allo**, con validación en lazo cerrado
usando el propio toolchain de Allo como oráculo.

> Repositorio privado. Ver `docs/bitacora.md` para el diario completo de
> decisiones y problemas resueltos durante el desarrollo, y
> `docs/arquitectura.md` para el mismo contenido en formato de consulta
> rápida.

## Idea del proyecto

Un LLM genera exclusivamente código Allo (kernel + schedule). Un lazo
automático lo valida con el compilador de Allo en una cascada de barreras
cada vez más estrictas — sintaxis/tipos → ejecución funcional contra un
golden model → equivalencia formal del schedule → síntesis HLS —
realimentando cualquier error al modelo hasta converger o agotar un
presupuesto de iteraciones. El objetivo es que restringir la salida del
LLM a un lenguaje pequeño, tipado y con verificación integrada convierta
la generación de hardware en un problema de búsqueda con oráculo barato,
en vez del enfoque de generar Verilog libre (donde los LLMs fallan mucho
más).

## Arquitectura: 3 agentes

| Agente | Rol | Entrada | Salida |
|---|---|---|---|
| **Generador** | Escribe código Allo dentro de un subconjunto restringido del lenguaje | Spec del bloque + historial de errores previos | Código Allo (kernel + schedule) |
| **Ejecutor** | Corre la cascada de validación real (L1-L4) contra el toolchain de Allo | Código Allo | Resultado crudo de cada nivel |
| **Validador** | Traduce el resultado crudo en un informe estructurado y decide la política de escalada | Salida del Ejecutor | JSON tipado (ver `src/agentes/schemas.py`) |

Un orquestador explícito en Python conecta los tres: por cada iteración,
llama al Generador, pasa su salida al Ejecutor, pasa el resultado al
Validador, y decide si continuar, regenerar desde cero, o congelar el
kernel y tocar solo el schedule — hasta convergencia o agotar el
presupuesto de iteraciones.

Detalle completo de por qué se eligió esta separación de roles (en vez de
un solo agente) en `docs/bitacora.md`.

## Estructura del repositorio

```
TFG/
├── README.md                      <- este archivo
├── docs/
│   ├── bitacora.md                 <- diario de decisiones, fechado
│   ├── arquitectura.md             <- las mismas decisiones en formato de consulta rápida
│   ├── setup_allo.md               <- instalación de Allo en Linux nativo
│   ├── Setup_Vitis.md              <- instalación de Vitis HLS 2023.1
│   └── SETUP_DOCKER.md             <- alternativa en Docker (no soportada en Windows)
├── src/
│   └── agentes/
│       ├── orchestrator.py         <- el bucle: Generador -> Ejecutor -> Validador
│       ├── allo_tools.py           <- herramientas del Ejecutor (cascada L1-L4)
│       ├── golden_models.py        <- modelos de referencia NumPy para L2
│       ├── l3_subproceso.py        <- allo.verify() aislado en proceso propio
│       ├── schemas.py              <- esquema tipado del informe del Validador
│       ├── probar_particion_ii.py  <- exploración aislada del factor de partición para bajar II
│       ├── test_minimo.py          <- prueba mínima de que el SDK/login funcionan
│       └── requirements.txt
├── specs/
│   ├── spec_example.yaml           <- FFT radix-2
│   └── spec_fft_radix4.yaml        <- FFT radix-4
├── external/
│   └── allo/                       <- Allo (Cornell) como git submodule
└── results/
    └── catalogo/                   <- kernels validados + métricas HLS (se va llenando)
```

## Cómo reproducir el entorno

**Linux nativo** (Allo depende de compilar LLVM/MLIR y solo tiene soporte
oficial en Linux; ver `docs/setup_allo.md`). Existe una alternativa en
Docker documentada en `docs/SETUP_DOCKER.md`, pero no llegó a funcionar en
Windows por problemas de virtualización — Linux nativo es la vía validada.

```bash
git clone --recurse-submodules https://github.com/PabloFraile/TFG-Allo-Agents.git TFG
cd TFG/src/agentes
pip install --break-system-packages -r requirements.txt

# Autenticación (usa tu suscripción Claude Pro, sin coste de API adicional)
sudo npm install -g @anthropic-ai/claude-code
claude login

# Allo, desde el submodule
cd ../../external/allo
python3 -m pip install --break-system-packages -v -e .

# Vitis HLS 2023.1 (ver docs/Setup_Vitis.md para la instalación completa)
source ~/tools/Vitis_HLS/2023.1/settings64.sh

# Prueba mínima de que todo funciona
cd ../../src/agentes
python3 test_minimo.py

# Pipeline completo contra el toolchain real (sin mocks)
python3 -u orchestrator.py ../../specs/spec_example.yaml
```

## Estado actual

El pipeline corre de extremo a extremo contra el toolchain real — Allo y
Vitis HLS 2023.1, sin ninguna herramienta mockeada — y ha quedado
validado tanto para la mariposa FFT radix-2 original como para su
generalización a radix-4 (mismo golden model, agnóstico al radix usado
internamente por el kernel). Ver la última entrada de `docs/bitacora.md`
para el estado exacto, el barrido de initiation interval conseguido y los
próximos pasos pendientes.

## Notas

- Allo se referencia como **git submodule**, no como copia — permite citar
  el commit exacto usado para reproducibilidad.
- La bitácora (`docs/bitacora.md`) documenta el "por qué" de cada decisión
  de diseño a medida que se tomó, para poder citarlo directamente en la
  memoria sin reconstruirlo de memoria al final del proyecto.
- `results/catalogo/` guarda, por bloque, el kernel validado y sus métricas
  de síntesis (II, latencia, LUT/FF/BRAM/DSP) — es la evidencia cruda
  detrás de cualquier cifra citada en la memoria.
