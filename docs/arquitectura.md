# Decisiones de arquitectura

Resumen de consulta rápida de las decisiones de diseño tomadas y su
justificación. Ver `bitacora.md` para el contexto cronológico completo de
cada una.

## 1. Tres agentes separados, no uno monolítico

**Decisión:** Generador, Ejecutor y Validador como tres configuraciones
distintas de llamada al modelo, en vez de un único agente que genere y
valide todo en una sola pasada.

**Por qué:** cada rol necesita un contexto y unas herramientas distintas.
El Generador solo necesita escribir texto (código Allo) dentro de un
subconjunto restringido del lenguaje — darle acceso a herramientas de
ejecución sería innecesario y abriría la puerta a que "haga trampa"
comprobando su propio resultado en vez de dejar que lo valide el Ejecutor
de forma independiente. El Ejecutor necesita herramientas reales (el
toolchain de Allo) pero no necesita "razonar" en lenguaje natural. El
Validador necesita producir una salida con forma fija (JSON tipado) para
que el orquestador pueda tomar decisiones automáticas sin parsear texto
libre — mezclar esto con la generación de código haría más frágil el
parseo de ambas cosas a la vez.

## 2. Orquestación explícita en Python, no subagentes gestionados por el SDK

**Decisión:** un script (`orchestrator.py`) que llama a `query()` tres
veces por iteración con prompts y herramientas distintas, en vez de
delegar la coordinación al propio Claude Agent SDK vía subagentes
automáticos.

**Por qué:** la política de escalada (cuántos fallos consecutivos en L2
antes de regenerar desde cero, cuándo congelar el kernel y tocar solo el
schedule) es lógica muy específica del dominio del proyecto. Necesitamos
control fino sobre cuándo se llama a cada agente y qué contexto recibe —
algo que se pierde si se delega la orquestación a un agente "coordinador"
genérico.

## 3. Informe del Validador como esquema tipado (Pydantic), no texto libre

**Decisión:** `schemas.py` define `InformeValidacion` con campos fijos
(`nivel_fallo`, `mensaje_accionable`, `diff_numerico`, `metricas_hls`,
`decision_escalada`) en vez de dejar que el Validador devuelva una
explicación en prosa.

**Por qué:** el orquestador necesita tomar decisiones automáticas
(regenerar vs. continuar vs. congelar kernel) basadas en el resultado del
Validador. Con texto libre, esto requeriría heurísticas de parseo frágiles
sobre lenguaje natural; con un esquema fijo, la decisión es una simple
comparación de un campo enum.

## 4. Allo como git submodule, no como copia

**Decisión:** `external/allo` se añade con `git submodule add`, apuntando
al repo oficial de Cornell, en vez de copiar los archivos dentro del
repositorio del TFG.

**Por qué:** permite citar en la memoria el **commit exacto** de Allo
usado en los experimentos (reproducibilidad), y evita mezclar el
historial de commits de un proyecto externo con el del TFG. El
inconveniente es que hay que recordar `git submodule update --init
--recursive` al clonar en una máquina nueva.

## 5. Entorno de desarrollo: Linux nativo en vez de Windows+Docker

**Decisión:** desarrollar en un segundo equipo con Linux nativo, en vez de
insistir en resolver el problema de virtualización de Docker Desktop en
Windows.

**Por qué:** Allo depende de compilar LLVM/MLIR y su soporte oficial es
Linux — cualquier vía en Windows pasa necesariamente por una capa de
virtualización (WSL2/Docker) que en el equipo de pruebas dio problemas no
resueltos (ver `bitacora.md`, 29 de julio). Usar Linux nativo elimina esa
categoría de problemas de raíz. Queda como limitación conocida del entorno
de desarrollo documentada, no resuelta — se puede retomar si en algún
momento hace falta reproducir el entorno también en Windows.

## 6. Autenticación vía suscripción Claude Pro, no API key de pago por uso

**Decisión:** autenticar el Claude Agent SDK a través de `claude login`
(vinculado a la suscripción Pro) en vez de una `ANTHROPIC_API_KEY` de la
consola de facturación por uso.

**Por qué:** mientras Anthropic mantenga pausado el cambio de facturación
del Agent SDK (anunciado para el 15 de junio de 2026 y pausado antes de
entrar en vigor), el uso automatizado del SDK sigue contando dentro de la
cuota de la suscripción Pro — evita gestionar saldo de facturación
aparte durante el desarrollo. Si Anthropic reactiva ese cambio, o si el
volumen de iteraciones del pipeline supera la cuota compartida de Pro,
habría que revisar esta decisión y pasar a una API key dedicada.

**Actualización (agosto de 2026):** esta última condición ya se ha
observado empíricamente — una racha de 5 fallos idénticos y consecutivos
del issue #1031 del SDK, justo tras encadenar varias síntesis HLS reales
de 20 minutos cada una en la misma sesión, resultó ser agotamiento real de
la cuota de Pro, no un bug (ver `bitacora.md`). No se ha tomado todavía la
decisión de migrar a API key dedicada, pero la condición que la
motivaría ya se ha dado al menos una vez.

## 7. Vitis HLS 2023.1 sin licencia de pago, invocado directamente por subprocess

**Decisión:** para el nivel L4 (síntesis HLS), se instala Vitis HLS
**2023.1** (no la última versión disponible) usando solo la síntesis C
(`csyn`), sin licencia de Vivado. La invocación real no usa `mod()` tal
como lo devuelve `s.build()` de Allo, sino que se lanza `vitis_hls -f
run.tcl` directamente vía `subprocess`, saltándose el Makefile que genera
Allo.

**Por qué:** la síntesis C no requiere licencia de pago (solo hace falta
para implementación de RTL/bitstream, fuera del alcance del TFG), lo que
resuelve de raíz la pregunta abierta de julio sobre si la síntesis HLS
real encajaba en el alcance del proyecto sin coste añadido. La versión
2023.1 es la primera con soporte oficial de Ubuntu 22.04+ que conserva el
flujo "classic" de Vitis HLS (`run.tcl`) que Allo asume — versiones más
recientes empujan hacia el nuevo Vitis Unified IDE. El bypass del
Makefile es necesario porque ese Makefile invoca un binario llamado
`vivado_hls`, discontinuado por Xilinx desde 2020.2+ (ver `bitacora.md`
para el detalle completo del diagnóstico).

## 8. L3 y L4 aislados en subprocesos, no en el proceso principal

**Decisión:** tanto `allo.verify()` (L3) como la invocación de `vitis_hls`
(L4) se ejecutan en subprocesos separados (`l3_subproceso.py` para L3; un
`subprocess.run()` directo para L4), nunca dentro del proceso Python
principal de `orchestrator.py`.

**Por qué:** el verificador PAST (usado por `allo.verify()`) puede
disparar un `assert()` de C++ real ante ciertas construcciones no
soportadas, terminando en `abort()`/`SIGABRT` — esto mata el proceso
Python **entero**, sin que ningún `try/except` (ni siquiera `except
BaseException`) pueda evitarlo, porque no es una excepción de Python. La
única defensa real es que ese crash ocurra en un proceso hijo desechable.
Se aplicó el mismo principio a L4 por consistencia y porque `vitis_hls`
también es una herramienta nativa externa fuera del control del proyecto.
El resultado de L3 se comunica de vuelta al proceso principal por un
**archivo dedicado**, no por stdout/stderr (que puede mezclarse de forma
impredecible con el panel de diagnóstico nativo de las herramientas y
corromper cualquier intento de parseo, incluso cuando la verificación en
sí tuvo éxito).

## 9. El "kernel congelado" se pasa como código literal, no como instrucción en prosa

**Decisión:** cuando el Validador decide `SOLO_TOCAR_SCHEDULE`,
`orchestrator.py` extrae el bloque `KERNEL` real de esa iteración y lo
reenvía **literalmente** en el siguiente prompt del Generador (con
instrucciones de copiarlo carácter por carácter), en vez de solo decirle
en texto "no lo cambies".

**Por qué:** confirmado empíricamente que un LLM sin el artefacto real
delante no respeta una instrucción de "no tocar X" de forma fiable —
sin el código, el Generador simplemente escribía un kernel distinto en
cada intento pese a la instrucción explícita (ver `bitacora.md`). Un
"candado" de arquitectura solo es real si el propio artefacto a preservar
forma parte del contexto que ve el modelo, no solo la orden de
preservarlo.

## 10. Presupuestos de iteración separados: generación de kernel vs. ajuste de schedule

**Decisión:** dos contadores independientes en vez de uno solo —
`MAX_ITERACIONES` (6) para generar un kernel completo desde cero, y
`MAX_INTENTOS_SCHEDULE` (8) para ajustar el schedule de un kernel ya
congelado/verificado. Un tope de seguridad absoluto combinado
(`MAX_ITERACIONES_TOTAL`, 25) evita bucles indefinidos.

**Por qué:** afinar directivas de `pipeline`/`partition` sobre un kernel
ya verificado en L1-L3 es una tarea mucho más barata (no hay que rehacer
la verificación funcional ni formal) y necesita más intentos por
naturaleza que generar un kernel completo desde cero (es más fácil
acertar aproximadamente con un pragma que con un algoritmo entero). Un
presupuesto único penalizaba ambos tipos de tarea por igual, agotando el
presupuesto total antes de darle margen real al ajuste fino de schedule
que es donde de hecho se concentran los intentos necesarios para cerrar
un objetivo de II agresivo.

## 11. Desenrollado de bucles exteriores: manual en el KERNEL, no vía `s.unroll()` en el SCHEDULE

**Decisión:** para bucles exteriores de pocas iteraciones cuyo cuerpo
define límites de bucles internos (el caso típico: las 10 etapas de una
FFT iterativa), el desenrollado se hace escribiendo el código Python
repetido a mano en el propio `KERNEL` (10 bloques literales con
constantes ya fijas), en vez de usar `s.unroll("nombre_bucle",
factor=0)` en el `SCHEDULE`.

**Por qué:** `s.unroll()` sobre este patrón concreto demostró ser frágil
de forma intermitente en la API de Allo, fallando con un crash real del
compilador (`error: Cannot find Stage S_<nombre>_2`, `failed to legalize
operation 'allo.unroll'`) incluso cuando el nombre del bucle coincidía
exactamente con la variable real del kernel, en generaciones
completamente independientes entre sí. Al no ser reproducible de forma
determinista ni depurable sin acceso al código fuente interno de Allo, se
optó por evitar la primitiva por completo para este caso en vez de seguir
intentando encontrar la combinación exacta que la hiciera funcionar.
