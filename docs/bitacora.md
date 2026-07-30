# Bitácora del TFG

Diario de trabajo del Trabajo de Fin de Grado (Ingeniería Industrial):
*generación automática de aceleradores hardware mediante LLMs con
validación en lazo cerrado sobre el lenguaje Allo*.

Formato: fecha, qué se decidió/hizo, qué problemas surgieron y cómo se
resolvieron. Pensado para poder citar en la memoria el "por qué" de cada
decisión sin tener que reconstruirlo de memoria al final.

---

## 27 de julio de 2026 — Arranque del proyecto: arquitectura de agentes

**Contexto.** Recibido por correo el planteamiento del proyecto: generación
automática de código RTL (comunicaciones/procesado de señal — 5G/6G, radar)
mediante LLMs restringidos al DSL Allo (Cornell), con validación en cascada
usando el propio compilador de Allo como oráculo (parseo → tipos → ejecución
contra golden model → equivalencia formal → HLS), y un lazo de reparación
que realimenta los errores al modelo hasta converger.

**Decisión de arquitectura.** Se plantea un pipeline de **3 agentes**
interconectados en vez de un único agente monolítico:

1. **Generador** — escribe código Allo (kernel + schedule) dentro de un
   subconjunto restringido del lenguaje (solo tipos de `allo.ir.types`,
   `allo.grid`, `range`, sin imports externos).
2. **Ejecutor** — corre la cascada de validación real (L1 sintaxis/tipos,
   L2 funcional contra golden model, L3 equivalencia formal de schedules,
   L4 síntesis HLS).
3. **Validador** — traduce la salida cruda del Ejecutor en un informe
   estructurado (JSON tipado) y decide la política de escalada:
   continuar, regenerar desde cero, o congelar el kernel y tocar solo el
   schedule.

**Por qué esta separación de roles** (y no un solo agente que hace todo):
cada rol necesita un contexto y unas herramientas distintas — el Generador
no necesita ejecutar nada, el Ejecutor no necesita "pensar" en lenguaje
natural, y el Validador necesita producir una salida con forma fija para
que el bucle pueda tomar decisiones automáticas sin parsear texto libre.

**Herramienta elegida: Claude Agent SDK.** Se descarta escribir el propio
orquestador de agentes desde cero — el SDK ya da subagentes, herramientas
personalizadas (MCP en proceso), hooks para telemetría, y salidas
estructuradas, que es justo lo que pedía la arquitectura del correo
original.

**Primer esqueleto de código.** Se crea un proyecto Python con:
- `schemas.py` — esquema tipado (Pydantic) del informe del Validador
  (`InformeValidacion`: nivel de fallo, mensaje accionable, diff numérico,
  métricas HLS, decisión de escalada).
- `allo_tools.py` — herramientas del Ejecutor que envuelven la cascada
  L1-L4 del toolchain de Allo (mockeadas al principio, para poder probar
  el bucle completo sin tener Allo instalado todavía).
- `orchestrator.py` — el bucle explícito: Generador → Ejecutor → Validador
  → decisión de escalada, con presupuesto máximo de iteraciones.
- `spec_example.yaml` — primer bloque de prueba: una mariposa FFT
  radix-2 (Cooley-Tukey).

**Decisión sobre orquestación:** explícita en Python (llamadas directas a
`query()` por rol) en vez de dejar que el propio SDK gestione subagentes
automáticamente — se necesita control fino sobre la cascada L1-L5 y la
política de escalada (congelar kernel vs. regenerar desde cero), que es
lógica muy específica del dominio.

---

## 28 de julio de 2026 — Entorno de desarrollo, Allo, y estructura de TFG

**Entorno base en Windows.** Instalación de Node.js, Python, el SDK
(`claude-agent-sdk`), y autenticación con la API. Problemas menores
resueltos: política de ejecución de PowerShell bloqueando `npm`
(`Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned`), y
una API key mal configurada (se guardó el *nombre* de la clave en vez del
valor real).

**Decisión: usar la suscripción Pro en vez de una API key de pago por
uso.** Se confirma que el uso automatizado (Agent SDK / bucles sin
intervención humana) sigue contando dentro de la cuota de Claude Pro
mientras Anthropic mantenga pausado el cambio de facturación anunciado
para el 15 de junio de 2026 — evita tener que cargar saldo en la consola
de API para las pruebas de desarrollo.

**Integración de Allo (real).** Se descubre que Allo depende de compilar
LLVM/MLIR y solo da soporte oficial para Linux (imagen Docker
`chhzh123/allo:latest`, o compilación desde fuente). No hay instalación
nativa en Windows. Además, el repo usa **submódulos de git** — el ZIP de
GitHub no los incluye, así que hay que clonar con
`git clone --recursive`.

**Decisión: entorno unificado en un contenedor** en vez de cruzar llamadas
Windows↔Docker en cada iteración del bucle (menos puntos de fallo). Se
escribe un `Dockerfile` que parte de la imagen oficial de Allo y añade
Node.js + Claude Code CLI + el SDK de Python encima.

**Reestructuración como TFG.** Al confirmarse que este es el Trabajo de
Fin de Grado, se reorganiza todo bajo una estructura de proyecto académico
(`C:\TFG`, fuera de `Documents` para evitar interferencias de OneDrive y
límites de longitud de ruta de Windows):

```
TFG/
├── docs/            (esta bitácora, notas de instalación)
├── docker/          (Dockerfile)
├── src/agentes/     (el pipeline de 3 agentes)
├── specs/           (specs de bloques, p. ej. spec_example.yaml)
├── external/allo/   (Allo como git submodule — permite citar el commit exacto)
└── results/catalogo/ (kernels validados + métricas, según vaya creciendo)
```

**Repositorio en GitHub.** Se crea `TFG-Allo-Agents` como repositorio
**privado** (pendiente de confirmar con el tutor si hay alguna norma de
confidencialidad específica de la universidad antes de hacerlo público).
Allo se añade como **git submodule** (no como clon normal) para poder citar
en la memoria el commit exacto usado, y para no mezclar el historial de
Allo con el del TFG. Autenticación con GitHub vía `gh auth login` en vez de
contraseña (GitHub ya no acepta contraseña plana por `git push`).

---

## 29 de julio de 2026 — Problemas de virtualización en Windows, cambio a Linux

**Intento de levantar Docker Desktop en Windows.** Error
`Virtualization support not detected`. Se descarta que sea por tener
Windows Home (Docker Desktop funciona en Home vía backend WSL2, no
necesita Hyper-V). Se investigan varias causas posibles a lo largo del
día: BIOS/SVM Mode (ya estaba activado), funciones opcionales de Windows
(`VirtualMachinePlatform`, WSL — activadas correctamente solo tras
ejecutar los comandos con PowerShell en modo Administrador, que al
principio no lo estaba), driver residual de VirtualBox (descartado, no
quedaba ninguno), y antivirus de terceros interfiriendo con el hipervisor
(descartado, solo Windows Defender). Ninguna de estas resolvió el problema
— quedó sin diagnosticar la causa raíz exacta en este equipo concreto
(hipótesis más probable: la Seguridad Basada en Virtualización de Windows
11 25H2 reservando el hipervisor de forma exclusiva para Credential Guard,
sin dejar partición libre para WSL2).

![Docker Desktop: "Virtualization support not detected" al intentar arrancar el motor de contenedores en Windows](img/2026-07-29_docker-virtualizacion-error.png)
*Figura 1. Pantalla de error de Docker Desktop en el equipo Windows de pruebas. El motor queda en estado `Engine stopped` y el arranque no llega a completarse pese a haber descartado las causas habituales (BIOS, VirtualBox, antivirus). Causa raíz no confirmada; hipótesis principal: reserva exclusiva del hipervisor por VBS/Credential Guard en Windows 11 25H2.*

**Decisión: usar un segundo ordenador con Linux nativo** en vez de seguir
depurando la virtualización de Windows. Justificación: Allo está pensado
para Linux de origen — evitar la capa de virtualización elimina de raíz la
categoría entera de problemas que estábamos teniendo, sin perder tiempo en
un diagnóstico que no era imprescindible para el progreso del proyecto (se
puede retomar más adelante si hace falta reproducir el entorno también en
Windows).

**Entorno validado en Linux.** Clonado del repositorio (`git clone
--recurse-submodules`), instalación de dependencias, `claude login` con la
cuenta Pro, y ejecución de `test_minimo.py` — confirmado
`apiKeySource: none` (usando la suscripción, no facturación de API) y
respuesta correcta del modelo, tanto desde Claude Code como desde una
terminal normal de forma independiente.

![Ejecución de test_minimo.py en Linux, con apiKeySource: 'none' y respuesta 'funciona'](img/2026-07-29_test-minimo-exitoso.png)
*Figura 2. Salida completa de `python3 test_minimo.py` en el nuevo entorno Linux. El `SystemMessage` confirma `apiKeySource: 'none'` (autenticación vía suscripción Pro, no API de pago por uso); el `AssistantMessage` devuelve el texto esperado (`'funciona'`); el `RateLimitEvent` confirma cuota de cinco horas con `overageDisabledReason: 'org_level_disabled'` (sin riesgo de facturación adicional); y el `ResultMessage` cierra con `is_error=False`. Esta captura cierra la validación del entorno antes de la primera ejecución del pipeline completo.*

**Primera ejecución del pipeline completo (con Allo aún mockeado).**
Se detectan y corrigen dos errores de integración al ejecutar
`orchestrator.py` por primera vez fuera de la carpeta original:
1. Ruta relativa a `spec_example.yaml` rota tras mover el archivo a
   `specs/` — corregido a `../../specs/spec_example.yaml` desde
   `src/agentes/`.
2. `mcp_servers` pasado como lista (`[allo_tools_server]`) en vez de
   diccionario (`{"allo-tools": allo_tools_server}`) al configurar las
   herramientas del Ejecutor — el SDK esperaba un mapeo nombre→servidor,
   no una lista, y lo interpretaba erróneamente como ruta a un archivo de
   configuración.

![Traza residual del error de spec_example.yaml y error "Invalid MCP configuration" al pasar mcp_servers como lista](img/2026-07-29_generador-fft-error-mcp.png)
*Figura 3. Salida de terminal de la primera ejecución de `orchestrator.py` desde su ubicación definitiva. Se observa, al inicio, el rastro del primer error ya resuelto (`FileNotFoundError: 'spec_example.yaml'`); a continuación, el código Allo generado por el agente Generador para el bloque `fft_radix2` (kernel de mariposa FFT radix-2, bucle `allo.grid(H)` con `H=512`); y finalmente el error `Invalid MCP configuration: MCP config file not found`, producido porque el SDK interpretó la lista `[allo_tools_server]` como ruta a un archivo de configuración en lugar de como el servidor MCP ya instanciado — confirmando el segundo bug descrito en el punto 2 anterior. Captura tomada **antes** de aplicar la corrección (diccionario `{"allo-tools": allo_tools_server}`); se conserva como evidencia del proceso de depuración, no como estado final del sistema.*

**Estado al cierre de esta sesión:** el Generador produce código Allo
plausible para la FFT radix-2 de prueba; el Ejecutor y el Validador están
en proceso de validarse con las herramientas aún mockeadas (pendiente de
confirmar una iteración completa exitosa tras el último arreglo).

---

## Pendiente para la siguiente sesión

- Confirmar que `orchestrator.py` completa una iteración entera con las
  herramientas mockeadas, ahora que `mcp_servers` está corregido.
- Instalar Allo de verdad en el Linux (`pip install -e .` dentro de
  `external/allo`) y sustituir las funciones `MOCK_*` de `allo_tools.py`
  por llamadas reales (`allo.customize()`, `s.build()`, el verificador
  formal, síntesis HLS).
- Decidir si se retoma el diagnóstico de virtualización en el equipo
  Windows (para poder reproducir el entorno en ambas máquinas) o se
  documenta como limitación conocida del entorno de desarrollo.
- Confirmar con el tutor si el repositorio debe mantenerse privado por
  alguna norma específica de la universidad o del colaborador que propuso
  el proyecto.
