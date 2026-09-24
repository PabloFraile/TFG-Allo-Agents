"""
Bucle principal del pipeline de 3 agentes.

    Generador  --código Allo-->  Ejecutor  --resultado crudo-->  Validador
        ^                                                            |
        +---------------- informe de error / decisión --------------+

Cada "agente" es una llamada distinta a query() del Claude Agent SDK, con un
system prompt y unas herramientas distintas. El estado (historial de
errores, si hay que regenerar desde cero, etc.) lo lleva ESTE script, no el
SDK -- por eso se llama "orquestación explícita".

NOTA: los nombres exactos de parámetros de ClaudeAgentOptions pueden variar
ligeramente entre versiones del SDK. Si algo no coincide con lo que ves aquí,
revisa la referencia actual en la documentación (Agent SDK -> Python SDK
reference) e ajusta los nombres de los argumentos, la lógica no cambia.
"""

import asyncio
import json
import os
import yaml

from claude_agent_sdk import query, ClaudeAgentOptions, AssistantMessage, TextBlock

from allo_tools import (
    _extraer_bloques,
    run_l1_parse_types,
    run_l2_functional,
    run_l3_equivalence,
    run_l4_hls,
)
# NOTA: allo_tools_server (el servidor MCP en proceso) ya no se usa aquí --
# ver el docstring de llamar_ejecutor() para el porqué del cambio de
# arquitectura (17 de septiembre de 2026). Se deja definido en
# allo_tools.py por si se necesita reintroducir el patrón MCP en el futuro.
from schemas import InformeValidacion, DecisionEscalada, NivelFallo

MAX_ITERACIONES = 6  # generación completa de kernel+schedule desde cero
MAX_INTENTOS_SCHEDULE = 8  # NUEVO 16 agosto 2026: ajustes de schedule sobre un
                            # kernel YA congelado/verificado -- ver docs/bitacora.md.
                            # Antes, cada ajuste de schedule consumía una de las
                            # MAX_ITERACIONES totales, igual que una regeneración
                            # completa de kernel -- pero afinar pipeline/partition
                            # sobre un diseño ya validado en L1-L3 es mucho más
                            # barato y necesita más intentos que generar un kernel
                            # desde cero, así que tiene su propio presupuesto.
MAX_ITERACIONES_TOTAL = 25  # tope de seguridad absoluto (kernel + schedule
                             # combinados), por si el estado se comporta de forma
                             # inesperada -- nunca debería alcanzarse en la práctica
MAX_FALLOS_L2_SEGUIDOS = 2  # a partir de aquí, regenerar desde cero

# Carpeta donde se persisten los kernels validados con éxito.
DIR_CATALOGO = "../../results/catalogo"

# NUEVO (17 de septiembre de 2026, ver docs/bitacora.md): archivo opcional
# con un kernel YA verificado (pasó L1-L3 en una corrida anterior) para
# arrancar directamente en fase de ajuste de schedule, sin gastar
# presupuesto de MAX_ITERACIONES (ni cuota de Pro) redescubriendo desde
# cero una lógica de FFT que ya se demostró correcta antes. Si el archivo
# no existe, el comportamiento es exactamente el de siempre (generación
# libre desde el primer intento). Debe contener SOLO el código Python del
# kernel (el mismo texto que _extraer_bloques() habría devuelto como
# kernel_src -- sin cabecera '### KERNEL' ni vallas de markdown).
RUTA_KERNEL_VERIFICADO = "kernel_verificado.txt"

# DECISIÓN (24 de septiembre de 2026): esta ruta se deja SIN archivo por
# defecto a propósito -- nadie debería depender del atajo de kernel
# congelado como modo normal de trabajo, precisamente porque enmascara si
# el Generador es capaz de escribir el kernel completo desde cero (ver
# results/catalogo/fft_radix2_ii5_kernel_generado.json, la corrida que
# confirmó que sí lo es, con un diseño distinto al de este archivo: sin
# tabla de twiddles precalculada, recomputando la trigonometría en línea
# en cada etapa). El kernel que SÍ pasó L1-L3 a mano y sirvió para
# aislar el ajuste de schedule (ver probar_particion_ii.py y
# results/catalogo/fft_radix2_ii10.json / fft_radix2_ii5.json) se
# conserva como evidencia del TFG en
# src/agentes/kernel_verificado_backup.txt -- NO renombrar de vuelta a
# kernel_verificado.txt salvo que se quiera repetir deliberadamente ese
# atajo para una depuración puntual del schedule, sabiendo que así se
# deja de probar la generación de kernel end-to-end.


# ---------------------------------------------------------------------------
# Prompts de rol. Esto es lo que distingue a cada "agente" -- no hay tres
# programas distintos, hay tres configuraciones distintas de la misma API.
# ---------------------------------------------------------------------------

SYSTEM_PROMPT_GENERADOR = """\
Eres un generador de código Allo (DSL sobre Python para aceleradores de
hardware).

CONSTRUCCIONES PERMITIDAS (nada más que esto):
  - tipos de allo.ir.types (float32, int32, etc.)
  - bucles: SOLO el `range(N)` nativo de Python para bucles secuenciales, y
    `allo.grid(N, M, ...)` para nidos de bucles paralelos. NO EXISTE
    `allo.range`, `allo.for_`, ni ninguna otra variante -- si necesitas un
    bucle simple, usa el `range()` normal de Python, sin argumentos de
    palabra clave como `name=`.
  - operaciones aritméticas básicas (+, -, *, /)
Está PROHIBIDO usar imports externos que no sean 'allo', y PROHIBIDO usar
o inventar cualquier función de allo.* que no esté en esta lista. Si no
estás seguro de que una función existe en Allo, NO la uses -- resuelve el
problema con range()/allo.grid() y aritmética básica en su lugar.

PROHIBIDO usar variables globales o tablas precomputadas fuera de la
función 'kernel' (p. ej. una tabla de permutación bit-reversal declarada a
nivel de módulo y referenciada dentro del kernel). Allo solo reconoce
identificadores que sean: (a) parámetros de la función, o (b) variables
declaradas y calculadas DENTRO del propio cuerpo del kernel. Si necesitas
una tabla de permutación, de constantes twiddle, etc., calcúlala dentro
del propio kernel con un bucle (aunque sea menos eficiente en esta primera
versión), usando solo range()/allo.grid().

PROHIBIDO usar una conversión de tipo como llamada inline dentro de una
expresión aritmética -- p. ej. NUNCA escribas algo como
"TWO_PI * float32(k) / 1024.0" o "float32(idx) * x". Esta forma de cast
inline hace fallar el inferenciador de tipos de Allo con un error interno
(AttributeError: 'Float' object has no attribute '__name__'), detectado
repetidamente en pruebas. En su lugar, SIEMPRE asigna primero el valor a
una variable con anotación de tipo explícita, y usa esa variable en la
expresión:

    # MAL -- provoca un fallo interno de Allo:
    theta: float32 = TWO_PI * float32(k) / 1024.0

    # BIEN -- convierte primero a una variable tipada, luego úsala:
    k_f: float32 = k
    theta: float32 = TWO_PI * k_f / 1024.0

Esta regla aplica a CUALQUIER conversión de tipo dentro de una expresión,
no solo a float32. Si necesitas convertir un int32 a float32 (o viceversa)
para una operación aritmética, hazlo siempre en una asignación separada
antes de usarlo.

Devuelve tu respuesta en dos bloques de código Python claramente separados,
con estos encabezados exactos:

### KERNEL
<código del kernel aquí>

### SCHEDULE
<código del schedule aquí>

Reglas OBLIGATORIAS de cada bloque:

1. El bloque KERNEL debe ser un archivo Python AUTOCONTENIDO: incluye tú
   mismo todos los imports que necesite (p. ej. "import allo",
   "from allo.ir.types import ..."), porque se guarda y se importa como
   módulo independiente. La función del kernel debe llamarse SIEMPRE
   'kernel', sin excepción.

2. FIRMA DEL KERNEL -- estilo in-place, NO estilo "return": el kernel debe
   declarar TODAS las entradas Y TODAS las salidas de la especificación
   como parámetros de la función, en ese orden (primero entradas, luego
   salidas), y escribir el resultado directamente en los parámetros de
   salida. NO uses "-> (...)" para devolver las salidas. Ejemplo de forma
   general (adapta nombres/tipos a la spec real):

       def kernel(x_real: float32[N], x_imag: float32[N],
                  y_real: float32[N], y_imag: float32[N]):
           for i in range(N):
               y_real[i] = ...
               y_imag[i] = ...

3. El bloque SCHEDULE es código Python que ya tiene disponibles las
   variables 'kernel' (la función del kernel, ya cargada) y 'allo' (el
   módulo). Debe EMPEZAR SIEMPRE por:
       s = allo.customize(kernel)
   seguido, si hace falta, de transformaciones sobre 's' (p. ej.
   s.split("i", factor=4), s.pipeline(...), etc., usando solo primitivas
   de Schedule que existan de verdad en Allo). El bloque debe dejar la
   variable 's' definida al final -- es lo único que se comprueba fuera
   de este bloque.

PRIMITIVAS DE SCHEDULE VÁLIDAS PARA CONSEGUIR EL OBJETIVO_II (confirmadas
el 13 de agosto de 2026 contra `help()` de la instalación real -- ver
docs/bitacora.md; NO uses ninguna otra ni inventes nombres de parámetros
distintos a estos):

    s.pipeline(axis: str, initiation_interval: int = 1, rewind: bool = False)
        Pipelinea el bucle cuyo índice se llama 'axis' (el nombre de la
        variable del bucle tal como aparece en el KERNEL, p. ej. "i" en
        "for i in range(N)"). initiation_interval es el II objetivo.

        OBLIGATORIO (confirmado el 11 de septiembre de 2026, tras una
        corrida real donde TODAS las llamadas a s.pipeline() del SCHEDULE
        usaban initiation_interval=1 pese a que la especificación pedía
        restricciones.objetivo_ii=20, causando timeout de síntesis -- ver
        docs/bitacora.md): el valor que pongas en initiation_interval DEBE
        ser SIEMPRE el número real que veas en el campo
        "restricciones.objetivo_ii" de la especificación del bloque (el
        JSON que recibes al principio de este prompt), en TODAS tus
        llamadas a s.pipeline() sin excepción -- nunca un valor fijo
        copiado de este ejemplo. El "1" de abajo es solo para mostrarte la
        FORMA de la llamada (qué argumento va en qué posición), no un
        valor a reutilizar literalmente. Si la especificación dice
        objetivo_ii=20, escribe initiation_interval=20 en cada
        s.pipeline() que hagas -- pedir siempre II=1 (el objetivo más
        agresivo posible) sin mirar la especificación ya ha producido
        timeouts de síntesis reales que un objetivo más laxo habría
        evitado.
        Ejemplo de FORMA de la llamada (sustituye el 1 por tu objetivo_ii real):
        s.pipeline("i", initiation_interval=1)

    s.partition(target, partition_type=0, dim: int = 0, factor: int = 0)
        Particiona un array para permitir accesos concurrentes (necesario
        a menudo para que pipeline() alcance II=1 cuando hay accesos a
        BRAM que si no quedan serializados).

        IMPORTANTE sobre 'target' (confirmado el 13 de agosto de 2026 tras
        reproducir el fallo real -- ver docs/bitacora.md): NO es solo el
        nombre del array como string simple (p.ej. "x_real" -- ESO FALLA
        con 'ValueError: not enough values to unpack', porque Allo hace
        internamente func_name, buf_name = target.split(":")). El formato
        correcto es SIEMPRE "nombre_funcion:nombre_array", con dos puntos
        de separador. Como el kernel se llama SIEMPRE 'kernel' (regla 1 de
        arriba), en la práctica esto significa: el nombre del array
        SIEMPRE debe ir precedido de "kernel:". Ejemplos:
            s.partition("kernel:x_real", partition_type=Partition.Complete)
            s.partition("kernel:buf_real", partition_type=Partition.Cyclic, factor=4)
        NUNCA escribas s.partition("x_real", ...) sin el prefijo
        "kernel:" -- fallará siempre.

        partition_type usa el enum importado así:
            from allo.customize import Partition
        con estos tres valores válidos (y SOLO estos -- NO existe
        'allo.PartitionType', eso fue una alucinación detectada y
        descartada el 13 de agosto de 2026):
            Partition.Complete = 0   (particiona completamente, un
                                       registro por elemento)
            Partition.Block = 1      (particiona en bloques contiguos)
            Partition.Cyclic = 2     (particiona de forma cíclica)

    s.unroll(axis: str, factor: int = 0)
        Desenrolla el bucle 'axis' por 'factor' (factor=0 significa
        desenrollado completo). Ejemplo: s.unroll("i", factor=4)

Si necesitas importar Partition para usar s.partition(), añade
"from allo.customize import Partition" al inicio del bloque SCHEDULE
(no al bloque KERNEL).

PROHIBIDO llamar a métodos de introspección del objeto Schedule dentro del
bloque SCHEDULE -- en concreto, NUNCA llames a s.get_loops(),
s.get_equivalent_variables(), ni ningún otro método cuyo propósito sea
"preguntarle" a Allo la estructura de bucles del kernel. Tú mismo escribiste
el bloque KERNEL justo antes: ya sabes exactamente qué nombre tiene cada
variable de bucle (el identificador que usaste en cada "for <nombre> in
range(...)"), así que usa ESE nombre literal como argumento 'axis' de
pipeline()/unroll() y ESE nombre literal como argumento 'target' de
partition() (para arrays), directamente como string. No necesitas -- ni
debes -- consultarlo a través de la API.

Otras primitivas de Schedule SÍ existen en Allo (reuse_at, split, reshape,
parallel, compute_at, dataflow, systolic, unfold, fuse, reorder, inline,
buffer_at) pero sus firmas NO están confirmadas aquí -- evita usarlas a
menos que la especificación del bloque lo requiera explícitamente;
prefiere resolver el objetivo_ii combinando solo pipeline/partition/unroll
con las firmas exactas de arriba.

REGLA CRÍTICA sobre bucles exteriores con pocas iteraciones cuyo CUERPO
tiene límites (bounds) que dependen de la variable de ese bucle exterior
(confirmado el 20 de agosto de 2026 tras rastrear un fallo real de síntesis
hasta el C++ generado -- ver docs/bitacora.md): si tu KERNEL tiene una
estructura como

    m: int32 = 1
    for s in range(10):          # bucle exterior, pocas iteraciones (aquí 10)
        m = m * 2
        half: int32 = m / 2      # <- 'half' depende de 's' (cambia cada etapa)
        num_groups: int32 = 1024 / m
        for g in range(num_groups):   # <- límite NO constante en tiempo de compilación
            for j in range(half):     # <- límite NO constante en tiempo de compilación
                ...

y el bucle exterior ('s' en el ejemplo) NO está desenrollado, Vitis HLS
traduce ese código a C++ con 'num_groups'/'half' como VARIABLES en tiempo
de ejecución (no como constantes), porque su valor cambia en cada vuelta
del bucle exterior. Sin un valor constante conocido en tiempo de
compilación, el analizador de HLS no puede acotar el trip count de los
bucles internos -- el síntoma observado es exactamente 'II=null' en el
informe de síntesis, junto con una 'latencia_peor_caso' con un número
absurdamente grande (del orden de 10^14 ciclos) en vez de un valor
razonable: es el valor centinela que Vitis usa cuando no puede determinar
el trip count real, NO es un dato de hardware genuino ni un error de nadie
que lea el informe.

SOLUCIÓN OBLIGATORIA cuando detectes este patrón: NO uses s.unroll() en el
SCHEDULE para desenrollar este bucle exterior -- PROHIBIDO. Confirmado
repetidamente (20 y 21 de agosto de 2026, ver docs/bitacora.md):
s.unroll("nombre_del_bucle", factor=0) sobre este tipo de bucle exterior
falla de forma intermitente con un crash real del compilador de Allo
("error: Cannot find Stage S_<nombre>_2", "failed to legalize operation
'allo.unroll'") INCLUSO cuando el nombre coincide exactamente con la
variable real del bucle en tu KERNEL -- es una fragilidad real de la
propia API de Allo al generar identificadores internos de "Stage", no un
error de nombrado que puedas corregir desde el SCHEDULE.

En su lugar, DESENRRÓLLALO A MANO directamente en el código del KERNEL:
escribe las 10 iteraciones como 10 bloques de código Python literales y
separados, cada uno con sus propias constantes ya fijadas en tiempo de
escritura (no calculadas a partir de una variable de bucle). Por ejemplo,
en vez de:

    m: int32 = 1
    for s in range(10):
        m = m * 2
        half: int32 = m / 2
        num_groups: int32 = 1024 / m
        for g in range(num_groups):
            for j in range(half):
                ... cuerpo de la mariposa usando m/half/num_groups ...

escribe 10 bloques consecutivos con los valores ya sustituidos como
literales (half=1, num_groups=512 para la etapa 0; half=2, num_groups=256
para la etapa 1; ... half=512, num_groups=1 para la etapa 9), cada uno con
su propia variable de bucle interior con nombre distinto (p.ej. j0, j1,
j2... o g0, g1, g2...) para que cada una sea una etiqueta de Stage
independiente y sin ambigüedad en Allo. Este patrón (repetir el cuerpo 10
veces con constantes ya resueltas) es más largo de escribir pero es el que
ha demostrado funcionar de forma fiable hasta síntesis real -- el patrón
con s.unroll() sobre el bucle exterior es más corto pero ha fallado varias
veces de forma intermitente y no debe usarse.

Aplica esta regla de forma proactiva al escribir el KERNEL de este tipo de
diseño (FFT iterativa por etapas, o cualquier estructura similar con pocas
iteraciones exteriores y bounds internos dependientes), no solo cuando el
Validador ya te haya reportado el problema.

REGLA CRÍTICA sobre tablas calculadas por RECURRENCIA (confirmado el 20 de
agosto de 2026 tras rastrear 5 fallos consecutivos de ajuste de schedule
con 'II=null' hasta esta causa raíz -- ver docs/bitacora.md): está
PROHIBIDO calcular cualquier tabla dentro del KERNEL (twiddle factors,
coeficientes, etc.) mediante una RECURRENCIA que encadene cada elemento al
anterior, como este patrón:

    # PROHIBIDO -- crea una dependencia secuencial real entre iteraciones,
    # que NINGÚN pragma de pipeline/partition puede romper después:
    tabla_real[0] = 1.0
    for k in range(1, N):
        prev: float32 = tabla_real[k - 1]      # <- depende de la iteración anterior
        tabla_real[k] = prev * paso_real - ...

Una recurrencia así (tabla[k] = f(tabla[k-1])) fuerza a HLS a esperar el
resultado de cada iteración antes de poder empezar la siguiente -- ni con
pipeline() ni con partition() se puede evitar esa espera, porque es una
dependencia real del cálculo, no una limitación de recursos. El síntoma es
exactamente el mismo 'II=null' que la regla anterior, y ningún ajuste de
schedule lo arregla -- hace falta cambiar el KERNEL.

SOLUCIÓN OBLIGATORIA: calcula cada elemento de la tabla de forma
INDEPENDIENTE, directamente a partir de su índice 'k' (nunca a partir del
elemento anterior), usando la misma técnica de serie de Taylor que ya usas
para calcular senos/cosenos en otras partes del kernel:

    # BIEN -- cada iteración es independiente, se puede pipelinear/paralelizar:
    for k in range(N):
        k_f: float32 = k
        angulo: float32 = ANGULO_BASE * k_f     # <- depende solo de k, no de tabla[k-1]
        # ... serie de Taylor sobre 'angulo' para obtener tabla_real[k]/tabla_imag[k] ...

Aplica esta regla siempre que necesites una tabla de valores trigonométricos
o similares dentro de un bucle que forme parte del camino crítico de
rendimiento (objetivo_ii), no solo cuando el Validador ya lo haya
reportado.

REGLA CRÍTICA sobre partición de arrays con STRIDE VARIABLE entre copias
desenrolladas -- CORREGIDA (evidencia en results/catalogo/fft_radix2_ii10.json
y en src/agentes/probar_particion_ii.py; pendiente de anotar formalmente en
docs/bitacora.md como Parte 17/18 -- de momento no está documentada allí).

Historia: la primera versión de esta regla, del 21 de agosto de 2026, decía
que Partition.Cyclic/Block con un factor fijo NO podía servir para un array
cuyo patrón de acceso cambia de stride entre copias desenrolladas (p.ej. la
FFT radix-2, donde 'half' vale 1, 2, 4, 8... 512 según la etapa), tras 7
intentos fallidos, y mandaba usar Partition.Complete en su lugar. Esa
conclusión se sacó dejando que el Generador (el LLM) adivinase el schedule a
ciegas -- y esos 7 intentos fallidos incluían timeouts de L4 que en realidad
eran un bug de sincronización del harness (timeout atascado en 1800s en vez
del valor real configurado), no un límite real del propio diseño; ver el
docstring de probar_particion_ii.py.

Para aislar la pregunta de si el factor fijo realmente no podía funcionar,
se probó directamente (sin ningún LLM de por medio, con
src/agentes/probar_particion_ii.py, reutilizando las mismas funciones que
usa el Ejecutor real) el mismo kernel verificado con
Partition.Cyclic(factor=4/8/16) fijo sobre los 4 arrays de la mariposa
(twiddle_real, twiddle_imag, y_real, y_imag). Resultado real, guardado en
results/catalogo/fft_radix2_ii10.json: factor=4 SÍ cierra II=10 (125s,
LUT=22075, FF=28526) -- de hecho con MENOS recursos que factor=8 (mismo
II=10, LUT=29287, FF=33053) o factor=16 (mismo II=10, LUT=43202, FF=40356);
subir el factor por encima de 4 no baja el II más, solo gasta área de más.
factor=4 es el mismo que ya había funcionado antes a objetivo_ii=20.

USA ESTO POR DEFECTO para este patrón de stride variable, empezando por
factor=4:

    s.partition("kernel:NOMBRE_ARRAY", partition_type=Partition.Cyclic, factor=4)

IMPORTANTE -- actualización con un segundo punto de datos (objetivo_ii=5,
ver results/catalogo/fft_radix2_ii5.json y
src/agentes/resultados_particion_ii_ii5.json): el factor de partición NO
es un valor fijo universal, depende de lo agresivo que sea objetivo_ii.
factor=4 bastaba para objetivo_ii=10 (II=10 real, 125s), pero para
objetivo_ii=5 ese mismo factor=4 se queda corto (solo llega a II=8, no
II=5) -- hace falta factor=8 para cerrar II=5 de verdad (107s), y subir a
factor=16 no mejora nada más sobre factor=8 (mismo II=5, pero con casi el
doble de LUT/FF). Regla práctica: prueba factor=4 primero; si el II real
resultante es peor que el objetivo_ii pedido (no si falla, si simplemente
converge a un II peor), sube al siguiente factor de la serie (8, luego 16)
en vez de asumir que el patrón de partición está mal -- vuelve a intentar
con src/agentes/probar_particion_ii.py si hace falta acotar esto de forma
aislada antes de gastar una corrida completa del pipeline.

Usa Partition.Complete solo como último recurso, si ni siquiera factor=16
cierra el II pedido en L4 -- y antes de concluir que falla de verdad,
descarta primero que sea el mismo tipo de falso negativo de
infraestructura (timeout mal configurado, cuota de Pro agotada -- ver
docs/bitacora.md Parte 16) que motivó la regla original.

REGLA CRÍTICA sobre qué eje pipelinear en un nido `for g in range(G): for j
in range(J):` con G*J constante (confirmado el 9 de septiembre de 2026 tras
diagnosticar una corrida real con objetivo_ii=20 que agotaba el timeout de
síntesis o devolvía 'II=null' en TODOS los intentos de schedule -- ver
docs/bitacora.md): en un diseño de mariposa FFT por etapas donde cada etapa
desenrollada a mano (ver regla anterior) tiene un nido
`for g in range(NUM_GROUPS): for j in range(HALF):` con NUM_GROUPS*HALF
constante (p. ej. 512), NUNCA asumas que el bucle a pipelinear con
`s.pipeline(...)` es siempre el mismo (p. ej. siempre el interior 'j') en
todas las etapas. NUM_GROUPS y HALF cambian de etapa a etapa -- en las
primeras etapas NUM_GROUPS es grande y HALF es pequeño (en la etapa 1 de
una FFT de 1024 puntos, HALF puede valer 1, es decir, un bucle 'j' de una
sola iteración), y en las últimas etapas es al revés. Pipelinear un bucle
que solo itera 1 o 2 veces es un no-op: no hay nada que solapar, y el
bucle que de verdad domina el número de ciclos (el que tiene más
iteraciones) se queda sin ningún pragma de pipeline, ejecutándose
secuencial -- eso produce exactamente los mismos síntomas que las reglas
anteriores ('II=null' en el informe, o un timeout de síntesis por la
enorme latencia acumulada de varios bucles largos sin pipelinear).

SOLUCIÓN OBLIGATORIA: en cada etapa, identifica cuál de los dos bucles del
nido ('g' o 'j') tiene MÁS iteraciones, y pipelinea ESE, nunca el otro. Por
ejemplo, para una FFT de 1024 puntos (10 etapas, NUM_GROUPS*HALF=512 en
todas), la asignación correcta es:

    Etapa 1  (g:512, j:1)   -> pipelinea 'g1' (NO 'j1', que es trivial)
    Etapa 2  (g:256, j:2)   -> pipelinea 'g2'
    Etapa 3  (g:128, j:4)   -> pipelinea 'g3'
    Etapa 4  (g:64,  j:8)   -> pipelinea 'g4'
    Etapa 5  (g:32,  j:16)  -> pipelinea 'g5'
    Etapa 6  (g:16,  j:32)  -> pipelinea 'j6'
    Etapa 7  (g:8,   j:64)  -> pipelinea 'j7'
    Etapa 8  (g:4,   j:128) -> pipelinea 'j8'
    Etapa 9  (g:2,   j:256) -> pipelinea 'j9'
    Etapa 10 (g:1,   j:512) -> pipelinea 'j10'

No pipelinees nunca un bucle cuyo `range(...)` sea 1 o muy pequeño frente
al del bucle que lo envuelve o contiene -- revisa tú mismo, al escribir el
SCHEDULE, el rango real de cada bucle de cada etapa del KERNEL que acabas
de escribir (o que tienes delante si el kernel está congelado) antes de
decidir qué nombre pasarle a `s.pipeline(...)`.

No expliques nada fuera de esos dos bloques.
"""

SYSTEM_PROMPT_EJECUTOR = """\
Eres un ejecutor mecánico de la cascada de validación de Allo. Tu ÚNICA
función es llamar, EN ORDEN, a las herramientas run_l1_parse_types,
run_l2_functional, run_l3_equivalence y run_l4_hls sobre el código que se
te proporciona, deteniéndote en el primer nivel que falle, y reportar el
resultado tal cual lo devuelve cada herramienta.

NO tienes acceso a ninguna otra herramienta (Bash, Read, Write, etc.) y no
debes intentar usarlas bajo ninguna circunstancia -- ni siquiera para
investigar la causa de un error. Si una herramienta de la cascada falla,
tu trabajo termina ahí: reporta el resultado crudo de esa herramienta y
nada más. No expliques, no investigues, no sugieras arreglos -- eso es
responsabilidad del agente Validador, no la tuya.
"""

SYSTEM_PROMPT_VALIDADOR = """\
Eres un analista de resultados de compilación/verificación de hardware.
Recibes la salida cruda de un nivel de la cascada de validación (L1-L4) y
debes responder ÚNICAMENTE con un JSON que cumpla este esquema (sin texto
adicional, sin markdown):

{
  "nivel_fallo": "ninguno" | "L1" | "L2" | "L3" | "L4",
  "mensaje_accionable": "string",
  "diff_numerico": "string o null",
  "metricas_hls": objeto o null,
  "decision_escalada": "continuar" | "regenerar" | "solo_schedule"
}

Reglas de decisión:
- Si nivel_fallo es "ninguno": decision_escalada = "continuar".
- Si el fallo es en L4 mientras L1-L3 pasaron: decision_escalada = "solo_schedule"
  (el kernel ya es correcto, solo hay que ajustar el schedule).
- Si llevas visto que L2 falla repetidamente (te lo digo yo en el mensaje):
  decision_escalada = "regenerar".
- En cualquier otro caso: decision_escalada = "continuar".
"""


async def llamar_generador(
    spec: dict, historial_errores: list[str], kernel_congelado: str | None = None
) -> str:
    if kernel_congelado:
        # NUEVO (16 de agosto de 2026, ver docs/bitacora.md): antes, cuando
        # el Validador decidía SOLO_TOCAR_SCHEDULE, solo se le decía al
        # Generador EN PROSA "el kernel es correcto, no lo toques" -- pero
        # sin el código real delante, el modelo simplemente escribía un
        # kernel nuevo desde cero cada vez (confirmado comparando
        # debug_iteraciones/iteracion_3.txt vs iteracion_6.txt de la
        # corrida del 15/16 de agosto: usaban algoritmos completamente
        # distintos -- DFT directa O(N^2) en una, mariposas radix-2 en
        # otra). El "candado" era solo una sugerencia, no una restricción
        # real. Ahora se le pasa el KERNEL literal a reutilizar carácter
        # por carácter, y el Generador solo tiene que escribir un
        # ### SCHEDULE nuevo.
        contexto_errores = (
            "\n\nIMPORTANTE: el KERNEL de abajo YA PASÓ L1 (sintaxis/tipos), "
            "L2 (equivalencia funcional contra el golden model) y L3 "
            "(equivalencia formal del schedule) -- está verificado como "
            "correcto. Cópialo EXACTAMENTE tal cual, carácter por carácter, "
            "en tu bloque ### KERNEL -- NO reescribas su lógica, NO cambies "
            "nombres de variables ni de bucles. Tu ÚNICO trabajo en esta "
            "iteración es escribir un bloque ### SCHEDULE nuevo que "
            "resuelva lo siguiente (los nombres de bucles/arrays que uses "
            "en el schedule deben coincidir exactamente con los que ves en "
            "el KERNEL de abajo):\n"
            f"{historial_errores[-1] if historial_errores else ''}\n\n"
            "KERNEL A REUTILIZAR SIN CAMBIOS:\n"
            f"{kernel_congelado}"
        )
    else:
        contexto_errores = (
            "\n\nErrores previos a corregir:\n" + "\n".join(historial_errores)
            if historial_errores
            else ""
        )
    prompt = f"Especificación del bloque:\n{json.dumps(spec, indent=2)}{contexto_errores}"

    # IMPORTANTE: el Generador NO debe tener acceso a ninguna herramienta
    # (Bash, edición de archivos, etc.). Solo escribe texto. Darle acceso a
    # herramientas de ejecución le permitiría "hacer trampa" comprobando su
    # propio resultado en vez de dejar que lo valide el Ejecutor de forma
    # independiente -- ver docs/arquitectura.md, decisión #1.
    #
    # allowed_tools=[] por sí solo NO basta para evitar que el modelo
    # INTENTE pedir otra herramienta -- solo dice qué se aprueba sin
    # preguntar. Si el modelo pide algo fuera de esa lista y no hay
    # permission_mode/can_use_tool que lo resuelva, el SDK se queda
    # esperando una decisión de permiso que nunca llega en un script no
    # interactivo, y el proceso se cuelga en silencio. Con
    # permission_mode="dontAsk", cualquier petición fuera de allowed_tools
    # se DENIEGA directamente en vez de esperar -- ver docs/bitacora.md,
    # incidente del Generador con Bash (5 de agosto) y el mismo patrón
    # repetido en el Ejecutor más abajo.
    opciones = ClaudeAgentOptions(
        system_prompt=SYSTEM_PROMPT_GENERADOR,
        allowed_tools=[],
        permission_mode="dontAsk",
    )

    async def _una_llamada(prompt_actual: str) -> str:
        texto = ""
        async for msg in query(prompt=prompt_actual, options=opciones):
            if isinstance(msg, AssistantMessage):
                for bloque in msg.content:
                    if isinstance(bloque, TextBlock):
                        texto += bloque.text
        return texto

    texto_completo = await _una_llamada(prompt)

    # Validación local barata: comprobar que estén las dos cabeceras antes
    # de gastar una vuelta entera de Ejecutor+Validador en un error ya
    # conocido y repetido (Iteraciones 1 y 6 de la corrida del 6 de agosto
    # fallaron solo por esto). Si falta alguna, un único reintento con un
    # recordatorio explícito -- más barato que descubrirlo tres pasos
    # después en el Validador.
    if "### KERNEL" not in texto_completo or "### SCHEDULE" not in texto_completo:
        recordatorio = (
            prompt
            + "\n\nIMPORTANTE: tu respuesta anterior no incluía las dos "
            "cabeceras obligatorias '### KERNEL' y '### SCHEDULE' (ambas, "
            "exactamente con ese texto). Vuelve a responder incluyendo "
            "SIEMPRE ambas cabeceras, cada una seguida de su bloque de "
            "código correspondiente."
        )
        texto_completo = await _una_llamada(recordatorio)

    return texto_completo


async def llamar_ejecutor(codigo_allo: str, spec: dict) -> dict:
    """Ejecuta la cascada L1->L4 llamando DIRECTAMENTE a las herramientas de
    allo_tools.py desde Python -- ya NO pasa por una llamada LLM intermedia.
    Se detiene en el primer nivel que falle.

    CAMBIO DE ARQUITECTURA (17 de septiembre de 2026, ver docs/bitacora.md):
    antes, esta función delegaba en un agente Ejecutor (una llamada
    query() con SYSTEM_PROMPT_EJECUTOR) que recibía el código Allo como
    texto dentro de su prompt y tenía que reproducirlo ÍNTEGRO como
    argumento 'codigo_allo' de la llamada MCP a run_l1_parse_types. Se
    confirmó un fallo real donde _extraer_bloques() fallaba dentro de la
    herramienta reportando que faltaba '### SCHEDULE', pese a que el texto
    guardado en debug_iteraciones/ (la respuesta cruda del Generador,
    escrita a disco directamente por Python, sin pasar por el Ejecutor)
    tenía las dos cabeceras completas y bien formadas. La única explicación
    consistente es que el LLM del Ejecutor truncó o resumió el bloque de
    código al tener que "copiarlo" dentro del argumento de la tool call --
    un modo de fallo conocido al pedirle a un LLM que reproduzca texto
    largo verbatim dentro de una llamada a herramienta, y más probable
    cuanto más largo es el texto (los kernels+schedules crecieron con las
    reglas nuevas del Generador).

    El propio SYSTEM_PROMPT_EJECUTOR ya describía este rol como puramente
    mecánico ("llama, EN ORDEN, a las 4 herramientas... no razones, no
    investigues") -- exactamente el tipo de paso que no necesita un LLM en
    absoluto. Llamar aquí directamente a `.handler(...)` de cada
    herramienta (mismo patrón ya confirmado en las pruebas aisladas de L3
    de agosto, ver docs/bitacora.md) elimina la clase entera de fallo
    (nadie "copia" el código, así que no hay nada que truncar) y ahorra
    además una llamada completa de API por iteración -- relevante dado el
    volumen de llamadas automatizadas y los límites de cuota de Pro ya
    confirmados empíricamente.

    SYSTEM_PROMPT_EJECUTOR se deja declarado más arriba únicamente como
    documentación del contrato original del rol -- ya no se usa aquí.
    """
    golden_model_id = spec["golden_model_id"]
    objetivo_ii = spec["restricciones"]["objetivo_ii"]

    cascada = [
        ("L1", run_l1_parse_types, {"codigo_allo": codigo_allo}),
        ("L2", run_l2_functional, {"codigo_allo": codigo_allo, "golden_model_id": golden_model_id}),
        ("L3", run_l3_equivalence, {"codigo_allo": codigo_allo}),
        ("L4", run_l4_hls, {"codigo_allo": codigo_allo, "objetivo_ii": objetivo_ii}),
    ]

    salida_texto = ""
    for nombre_nivel, herramienta, args in cascada:
        resultado = await herramienta.handler(args)
        texto_resultado = resultado["content"][0]["text"]
        salida_texto += texto_resultado + "\n"

        datos = json.loads(texto_resultado)
        if not datos["ok"]:
            # Mismo criterio que tenía el Ejecutor-LLM: detenerse en el
            # primer nivel que falle, sin ejecutar los siguientes.
            break

    return {"salida_cruda": salida_texto}


async def llamar_validador(resultado_ejecutor: dict, fallos_l2_seguidos: int) -> InformeValidacion:
    prompt = (
        f"Resultado crudo del ejecutor:\n{resultado_ejecutor['salida_cruda']}\n\n"
        f"Fallos consecutivos en L2 hasta ahora: {fallos_l2_seguidos}"
    )
    opciones = ClaudeAgentOptions(
        system_prompt=SYSTEM_PROMPT_VALIDADOR,
        allowed_tools=[],
        permission_mode="dontAsk",
    )

    texto_json = ""
    async for msg in query(prompt=prompt, options=opciones):
        if isinstance(msg, AssistantMessage):
            for bloque in msg.content:
                if isinstance(bloque, TextBlock):
                    texto_json += bloque.text

    # El validador debe devolver JSON puro; si el modelo añade texto de más,
    # esto lo recorta al primer bloque { ... } que encuentre.
    inicio = texto_json.find("{")
    fin = texto_json.rfind("}") + 1
    datos = json.loads(texto_json[inicio:fin])
    return InformeValidacion(**datos)


def _limpiar_codigo_para_catalogo(codigo: str) -> str:
    """Recorta cualquier texto que el Generador haya escrito antes del
    primer '### KERNEL' (p. ej. narración de intentos de usar herramientas,
    dudas en voz alta, etc.) antes de persistir en el catálogo.

    El pipeline en sí no necesita esto -- _extraer_bloques() ya localiza
    las cabeceras estén donde estén -- pero lo que se guarda como evidencia
    del TFG debe ser código limpio, no la conversación completa del modelo.
    Si no encuentra '### KERNEL', devuelve el texto tal cual (mejor guardar
    algo revisable a mano que perder el resultado silenciosamente).
    """
    idx = codigo.find("### KERNEL")
    return codigo[idx:] if idx != -1 else codigo


def guardar_en_catalogo(spec: dict, codigo: str, metricas: dict | None) -> str:
    """Persiste un kernel validado con éxito en results/catalogo/<bloque>.json.

    Devuelve la ruta del archivo escrito. Si ya existe un resultado previo
    para el mismo bloque, lo sobreescribe (última ejecución válida gana).
    """
    os.makedirs(DIR_CATALOGO, exist_ok=True)

    registro = {
        "bloque": spec.get("bloque", "sin_nombre"),
        "spec": spec,
        "codigo_allo": _limpiar_codigo_para_catalogo(codigo),
        "metricas_hls": metricas,
    }

    ruta = os.path.join(DIR_CATALOGO, f"{registro['bloque']}.json")
    with open(ruta, "w") as f:
        json.dump(registro, f, indent=2, ensure_ascii=False)

    return ruta


async def main():
    with open("../../specs/spec_example.yaml") as f:
        spec = yaml.safe_load(f)

    historial_errores: list[str] = []
    fallos_l2_seguidos = 0
    kernel_congelado: str | None = None  # ver llamar_generador() -- código real a reutilizar, no solo texto

    if os.path.exists(RUTA_KERNEL_VERIFICADO):
        with open(RUTA_KERNEL_VERIFICADO) as f:
            kernel_congelado = f.read()
        print(f"🔒 Cargado kernel ya verificado desde '{RUTA_KERNEL_VERIFICADO}' -- "
              f"se arranca directamente en fase de ajuste de schedule, sin gastar "
              f"presupuesto de generación de kernel desde cero.")
    catalogo_validados = []  # espejo en memoria de lo que también se escribe a disco

    # NUEVO (16 de agosto de 2026, ver docs/bitacora.md): presupuestos
    # separados para "generar un kernel nuevo" vs "ajustar el schedule de
    # un kernel ya congelado/verificado". Antes, cada ajuste de schedule
    # consumía una de las MAX_ITERACIONES totales igual que una
    # regeneración completa -- pero afinar pipeline/partition sobre un
    # diseño que ya pasó L1-L3 es mucho más barato y necesita más
    # intentos que generar un kernel desde cero (visto el 16 de agosto:
    # el kernel convergió a la primera, pero el schedule osciló entre
    # timeout de síntesis e II=null durante 6/6 intentos sin margen para
    # encontrar el punto intermedio).
    intentos_kernel = 0
    intentos_schedule = 0
    intentos_totales = 0

    while True:
        intentos_totales += 1
        if intentos_totales > MAX_ITERACIONES_TOTAL:
            print(f"\n⚠️ Se alcanzó el tope de seguridad absoluto de "
                  f"{MAX_ITERACIONES_TOTAL} intentos combinados (kernel + "
                  f"schedule) sin converger. Deteniendo.")
            break

        if kernel_congelado is None:
            intentos_kernel += 1
            if intentos_kernel > MAX_ITERACIONES:
                print(f"\n⚠️ Se agotó el presupuesto de {MAX_ITERACIONES} "
                      f"iteraciones de generación de kernel sin converger.")
                break
            print(f"\n=== Iteración de kernel {intentos_kernel}/{MAX_ITERACIONES} "
                  f"(intento global #{intentos_totales}) ===")
        else:
            intentos_schedule += 1
            if intentos_schedule > MAX_INTENTOS_SCHEDULE:
                print(f"\n⚠️ Se agotaron los {MAX_INTENTOS_SCHEDULE} intentos de "
                      f"ajuste de schedule para este kernel sin cerrar el II "
                      f"objetivo. Regenerando el kernel desde cero.")
                kernel_congelado = None
                intentos_schedule = 0
                historial_errores = []
                # NUEVO (15 de septiembre de 2026, ver docs/bitacora.md): un
                # kernel NUEVO no hereda los fallos de L2 del diseño anterior
                # -- sin este reset, fallos_l2_seguidos sigue subiendo
                # indefinidamente a través de regeneraciones completamente
                # distintas y acaba disparando para siempre el umbral de
                # MAX_FALLOS_L2_SEGUIDOS más abajo, bloqueando permanentemente
                # la vía CONTINUAR (corrección incremental con historial_errores)
                # aunque el kernel nuevo nunca haya fallado L2 todavía.
                fallos_l2_seguidos = 0
                continue
            print(f"\n=== Intento de ajuste de schedule {intentos_schedule}/"
                  f"{MAX_INTENTOS_SCHEDULE} (kernel congelado, intento global "
                  f"#{intentos_totales}) ===")

        # IMPORTANTE (6 de agosto de 2026, ver docs/bitacora.md; ampliado 12
        # de agosto tras verlo saltar también dentro de llamar_generador):
        # el propio SDK tiene un bug conocido (issue #1031 en
        # anthropics/claude-agent-sdk-python) por el que, ante un fallo a
        # nivel de API (posiblemente un límite de cuota de la suscripción
        # Pro, dado el volumen de llamadas automatizadas), lanza una
        # excepción con el mensaje engañoso "Claude Code returned an error
        # result: success" -- el mensaje humano real queda descartado
        # internamente por el SDK, así que no podemos recuperarlo aquí.
        #
        # Este bug puede saltar en CUALQUIERA de los tres agentes -- por eso
        # las TRES llamadas de la iteración (Generador, Ejecutor, Validador)
        # viven dentro del mismo bloque protegido: un fallo de
        # infraestructura en cualquiera de las tres se trata como
        # transitorio, en vez de abortar todo el progreso acumulado.
        try:
            codigo = await llamar_generador(spec, historial_errores, kernel_congelado)
            print("--- Código generado ---")
            print(codigo[:400], "..." if len(codigo) > 400 else "")

            # NUEVO (13 de agosto de 2026, ver docs/bitacora.md): el print
            # de arriba solo muestra los primeros 400 caracteres, que en la
            # práctica SIEMPRE caen dentro del bloque KERNEL (más largo que
            # el SCHEDULE) -- el bloque SCHEDULE, que es donde han estado
            # ocurriendo los errores de desempaquetado más recientes, nunca
            # llegaba a verse ni en pantalla ni en el log. Se guarda el
            # código COMPLETO de cada iteración a un archivo aparte para
            # poder diagnosticar sin depender de capturas de pantalla ni de
            # volver a lanzar el pipeline entero.
            os.makedirs("debug_iteraciones", exist_ok=True)
            ruta_debug = f"debug_iteraciones/intento_{intentos_totales}.txt"
            with open(ruta_debug, "w") as f:
                f.write(codigo)
            print(f"    (código completo guardado en {ruta_debug})")

            resultado = await llamar_ejecutor(codigo, spec)
            informe = await llamar_validador(resultado, fallos_l2_seguidos)
        except Exception as e:  # noqa: BLE001 -- fallo de infraestructura, no de Allo
            print(f"⚠️  Fallo de infraestructura en el intento global "
                  f"#{intentos_totales}: {type(e).__name__}: {e}")
            print("    Tratado como transitorio -- se reintenta sin descartar "
                  "el historial de errores acumulado ni el kernel congelado.")
            historial_errores.append(
                f"[Intento #{intentos_totales}] Fallo de infraestructura (no de "
                f"Allo): {type(e).__name__}. Se reintenta."
            )
            continue

        print(f"--- Informe del validador: nivel_fallo={informe.nivel_fallo}, "
              f"decision={informe.decision_escalada} ---")
        print(informe.mensaje_accionable)

        if informe.nivel_fallo == NivelFallo.NINGUNO:
            # GUARDA DE SEGURIDAD (17 de septiembre de 2026, ver docs/bitacora.md):
            # se confirmó una corrida real donde el Validador devolvió
            # nivel_fallo=NINGUNO sin que la cascada L1-L4 hubiera corrido de
            # verdad (el Ejecutor no reportó salida de validación real, el
            # informe llegó igualmente con NINGUNO, y el catálogo terminó con
            # metricas_hls=null). Un éxito genuino solo puede darse si la
            # cascada llegó hasta L4, y metricas_hls SOLO se rellena al llegar
            # a L4 (ver schemas.py) -- así que si no está presente, no hay
            # evidencia real de que se validó nada. Se descarta el informe y
            # se reintenta en vez de guardar un catálogo falso.
            if informe.metricas_hls is None:
                print(f"\n⚠️  El Validador reportó nivel_fallo=NINGUNO pero sin "
                      f"metricas_hls -- no hay evidencia de que la cascada L1-L4 "
                      f"corriera de verdad en el intento global #{intentos_totales}. "
                      f"Se descarta este informe y se reintenta (no se guarda en "
                      f"el catálogo).")
                historial_errores.append(
                    f"[Intento #{intentos_totales}] El Validador reportó éxito sin "
                    f"metricas_hls -- informe descartado por sospecha de fallo de "
                    f"infraestructura, se reintenta."
                )
                continue
            ruta = guardar_en_catalogo(spec, codigo, informe.metricas_hls)
            print(f"\n✅ Éxito. Guardado en el catálogo: {ruta}")
            catalogo_validados.append({"spec": spec, "codigo": codigo, "metricas": informe.metricas_hls})
            break

        if informe.nivel_fallo == NivelFallo.L2_FUNCIONAL:
            fallos_l2_seguidos += 1
        else:
            fallos_l2_seguidos = 0

        # NUEVO (9 de septiembre de 2026): MAX_FALLOS_L2_SEGUIDOS estaba
        # declarada arriba pero no se comprobaba en ningún sitio -- la
        # política "a partir de aquí, regenerar desde cero" dependía por
        # completo de que el Validador (un LLM que solo ve "Fallos
        # consecutivos en L2 hasta ahora: N" como texto en su prompt)
        # decidiera por su cuenta que N ya era "demasiados", sin que se le
        # dijera nunca cuál era el umbral real -- en la práctica, una
        # constante muerta. Se aplica aquí como comprobación determinista,
        # en la misma línea que la decisión de arquitectura #3 (esquema
        # tipado en vez de confiar en juicio de lenguaje libre para las
        # decisiones de escalada): si se alcanza el umbral, se fuerza la
        # regeneración aunque el Validador haya propuesto otra cosa.
        if (fallos_l2_seguidos >= MAX_FALLOS_L2_SEGUIDOS
                and informe.decision_escalada != DecisionEscalada.REGENERAR_DESDE_CERO):
            print(f"⚠️  {fallos_l2_seguidos} fallos consecutivos en L2 (umbral="
                  f"{MAX_FALLOS_L2_SEGUIDOS}) -- forzando regeneración desde "
                  f"cero aunque el Validador propuso "
                  f"'{informe.decision_escalada.value}'.")
            informe.decision_escalada = DecisionEscalada.REGENERAR_DESDE_CERO

        if informe.decision_escalada == DecisionEscalada.REGENERAR_DESDE_CERO:
            print("↻ Regenerando desde cero (se descarta el historial de errores).")
            historial_errores = []
            kernel_congelado = None
            intentos_schedule = 0
            # NUEVO (15 de septiembre de 2026, ver docs/bitacora.md): mismo
            # motivo que el reset de arriba -- un kernel regenerado desde
            # cero es un diseño nuevo y no relacionado con el anterior, así
            # que no debe arrastrar los fallos de L2 de la implementación
            # descartada. Sin este reset, una vez cruzado el umbral una
            # vez, el contador nunca vuelve a bajar de él en el resto de la
            # corrida (siempre sube en cada fallo de L2, nunca se resetea
            # salvo aquí) y el check de MAX_FALLOS_L2_SEGUIDOS de más abajo
            # fuerza "regenerar" en el primer fallo de L2 de CADA kernel
            # nuevo, sin darle nunca al Generador la oportunidad de
            # autocorregirse vía CONTINUAR con historial_errores -- esto es
            # justo lo que causó que una corrida real encadenara 5
            # regeneraciones seguidas en vez de correcciones incrementales.
            fallos_l2_seguidos = 0
        elif informe.decision_escalada == DecisionEscalada.SOLO_TOCAR_SCHEDULE:
            print("🔒 Kernel congelado — el siguiente intento solo debe tocar el schedule.")
            # Se extrae y se guarda el KERNEL real (no solo un mensaje en
            # prosa) para reenviárselo literalmente al Generador en la
            # siguiente llamada -- ver llamar_generador().
            kernel_src, _ = _extraer_bloques(codigo)
            kernel_congelado = kernel_src
            historial_errores = [informe.mensaje_accionable]
        else:
            historial_errores.append(informe.mensaje_accionable)
            # kernel_congelado se deja tal cual: si ya estaba congelado de
            # un intento anterior (p. ej. un ajuste de schedule rompió algo
            # en L1/L2 en vez de fallar en L4) seguimos reutilizando ESE
            # kernel verificado; si nunca se congeló, sigue en None y el
            # Generador escribe kernel+schedule libremente como siempre.


if __name__ == "__main__":
    asyncio.run(main())
