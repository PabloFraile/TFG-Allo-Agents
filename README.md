# TFG: Generación automática de aceleradores hardware mediante LLMs sobre Allo

Trabajo de Fin de Grado (Ingeniería Industrial). Pipeline de agentes LLM
para generar código RTL (sistemas de comunicaciones y procesado de señal —
5G/6G, radar) restringido al DSL **Allo**, con validación en lazo cerrado
usando el propio toolchain de Allo como oráculo.

> Repositorio privado. Ver `docs/bitacora.md` para el diario completo de
> decisiones y problemas resueltos durante el desarrollo.

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
presupuesto `K` de iteraciones.

Detalle completo de por qué se eligió esta separación de roles (en vez de
un solo agente) en `docs/bitacora.md`, entrada del 27 de julio de 2026.

## Estructura del repositorio

```
TFG/
├── README.md                  <- este archivo
├── docs/
│   ├── bitacora.md             <- diario de decisiones, fechado
│   └── SETUP_DOCKER.md         <- entorno unificado en Docker (Linux/WSL2)
├── docker/
│   └── Dockerfile              <- Allo + Node + Claude Agent SDK en una imagen
├── src/
│   └── agentes/
│       ├── orchestrator.py     <- el bucle: Generador -> Ejecutor -> Validador
│       ├── allo_tools.py       <- herramientas del Ejecutor (cascada L1-L4)
│       ├── schemas.py          <- esquema tipado del informe del Validador
│       ├── test_minimo.py      <- prueba mínima de que el SDK/login funcionan
│       └── requirements.txt
├── specs/
│   └── spec_example.yaml       <- specs de bloques (una por archivo, según crezca)
├── external/
│   └── allo/                   <- Allo (Cornell) como git submodule
└── results/
    └── catalogo/                <- kernels validados + métricas (se va llenando)
```

## Cómo reproducir el entorno

**Recomendado: Linux nativo** (Allo depende de compilar LLVM/MLIR y solo
tiene soporte oficial en Linux — en Windows se puede intentar vía
Docker/WSL2, pero puede haber problemas de virtualización según el
equipo; ver nota en `docs/SETUP_DOCKER.md`).

```bash
git clone --recurse-submodules <url-del-repo> TFG
cd TFG/src/agentes
pip install --break-system-packages -r requirements.txt

# Autenticación (usa tu suscripción Claude Pro, sin coste de API adicional)
sudo npm install -g @anthropic-ai/claude-code
claude login

# Prueba mínima de que todo funciona
python3 test_minimo.py

# Pipeline completo (por ahora con la cascada de Allo mockeada)
python3 orchestrator.py
```

Para instalar Allo de verdad (sustituyendo las funciones `MOCK_*` de
`allo_tools.py`):

```bash
cd ../../external/allo
python3 -m pip install --break-system-packages -v -e .
```

## Estado actual

Ver la última entrada de `docs/bitacora.md` para el estado exacto y los
próximos pasos pendientes.

## Notas para la memoria del TFG

- Allo se referencia como **git submodule**, no como copia — permite citar
  el commit exacto usado para reproducibilidad.
- La bitácora (`docs/bitacora.md`) documenta el "por qué" de cada decisión
  de diseño a medida que se tomó, para poder citarlo directamente en la
  memoria sin reconstruirlo de memoria al final del proyecto.
