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
