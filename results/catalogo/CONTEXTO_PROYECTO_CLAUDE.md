# Contexto del proyecto — TFG Allo Agents

Documento de traspaso para arrancar un Proyecto de Claude nuevo sin perder
el contexto acumulado en la conversación anterior. Pégalo como una de las
fuentes de conocimiento del proyecto (o resume esta info en las
instrucciones personalizadas — ver abajo cómo repartirlo).

## Quién soy y qué es esto

Estudiante de Ingeniería Industrial haciendo el TFG. El proyecto consiste
en generar automáticamente código RTL (sistemas de comunicaciones y
procesado de señal — 5G/6G, radar) mediante LLMs restringidos al DSL
**Allo** (github.com/cornell-zhang/allo), con validación en lazo cerrado
usando el propio compilador de Allo como oráculo.

## Arquitectura: pipeline de 3 agentes

1. **Generador** — escribe código Allo (kernel + schedule) dentro de un
   subconjunto restringido del lenguaje (solo `allo.ir.types`,
   `allo.grid`, `range`, sin imports externos).
2. **Ejecutor** — corre la cascada de validación real contra el toolchain
   de Allo: L1 sintaxis/tipos, L2 funcional (contra golden model), L3
   equivalencia formal del schedule, L4 síntesis HLS.
3. **Validador** — traduce la salida cruda del Ejecutor en un informe
   estructurado (JSON tipado con Pydantic) y decide la política de
   escalada: continuar, regenerar desde cero, o congelar el kernel y
   tocar solo el schedule.

Un orquestador explícito en Python (no subagentes automáticos del SDK)
conecta los tres en un bucle con presupuesto máximo de iteraciones.

## Stack técnico

- **Claude Agent SDK** (Python) para los 3 agentes — autenticado vía
  `claude login` con **Claude Pro** (no API key de pago por uso; el uso
  automatizado del SDK sigue contando dentro de la cuota de Pro mientras
  Anthropic mantenga pausado el cambio de facturación anunciado para el
  15 de junio de 2026).
- Herramientas del Ejecutor como servidor MCP en proceso
  (`create_sdk_mcp_server` + `@tool`), pasado a `ClaudeAgentOptions` como
  **diccionario** `{"allo-tools": server}` (no lista — error ya resuelto).
- **Allo** como git submodule en `external/allo`, para citar el commit
  exacto en la memoria.
- Entorno de desarrollo: **Linux nativo** (no Windows) — Allo depende de
  compilar LLVM/MLIR y solo tiene soporte oficial en Linux. En Windows,
  Docker Desktop dio problemas de virtualización sin resolver (ver
  bitácora, 29 de julio) — se descartó esa vía por ahora.
- Repositorio privado en GitHub: `TFG-Allo-Agents` (usuario `PabloFraile`),
  autenticado con `gh auth login`.

## Estructura del repositorio (`~/TFG`)

```
TFG/
├── README.md
├── docs/
│   ├── bitacora.md         <- diario fechado de decisiones y problemas resueltos
│   ├── arquitectura.md     <- las mismas decisiones en formato de consulta rápida
│   └── SETUP_DOCKER.md     <- guía Docker (con nota de que en Windows no funcionó)
├── docker/Dockerfile
├── src/agentes/
│   ├── orchestrator.py
│   ├── allo_tools.py
│   ├── schemas.py
│   ├── test_minimo.py
│   └── requirements.txt
├── specs/spec_example.yaml   <- bloque de prueba: FFT radix-2
├── external/allo/            <- git submodule
└── results/catalogo/
```

## Estado a fecha de hoy (29 de julio de 2026)

- Entorno completo validado en Linux: Python, SDK, autenticación con Pro
  (`apiKeySource: none`), todo confirmado funcionando.
- El Generador produce código Allo plausible para la FFT de prueba.
- Ejecutor y Validador corrigen dos bugs de integración (ruta relativa al
  spec, y `mcp_servers` como diccionario en vez de lista) — pendiente de
  confirmar una iteración completa exitosa con las herramientas aún
  **mockeadas** (no se ha conectado Allo de verdad todavía).
- Documentación (README, bitácora, decisiones de arquitectura) ya
  commiteada en el repo.

## Pendiente / próximos pasos

1. Confirmar que `orchestrator.py` completa una iteración entera con las
   herramientas mockeadas tras el último arreglo.
2. Instalar Allo de verdad en Linux (`pip install -e .` dentro de
   `external/allo`) y sustituir las funciones `MOCK_*` de
   `allo_tools.py` por llamadas reales.
3. Decidir si se retoma el diagnóstico de virtualización en Windows o se
   deja documentado como limitación conocida.
4. Confirmar con el tutor si el repo debe seguir siendo privado por
   alguna norma de la universidad o del colaborador que propuso el
   proyecto.

## Dónde está el detalle completo

Todo el razonamiento detallado (por qué cada decisión, troubleshooting
completo de Windows, comandos exactos usados) está en
`docs/bitacora.md` y `docs/arquitectura.md` dentro del propio
repositorio — súbelos también como conocimiento del proyecto si quieres
que Claude pueda consultar el detalle completo, no solo este resumen.
