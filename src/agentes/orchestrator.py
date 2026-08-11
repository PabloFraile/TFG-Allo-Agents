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

from allo_tools import allo_tools_server
from schemas import InformeValidacion, DecisionEscalada, NivelFallo

MAX_ITERACIONES = 6
MAX_FALLOS_L2_SEGUIDOS = 2  # a partir de aquí, regenerar desde cero

# Carpeta donde se persisten los kernels validados con éxito.
DIR_CATALOGO = "../../results/catalogo"


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


async def llamar_generador(spec: dict, historial_errores: list[str]) -> str:
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
    """Ejecuta la cascada L1->L4 llamando a las herramientas reales (o mock).
    Se detiene en el primer nivel que falle."""
    opciones = ClaudeAgentOptions(
        system_prompt=SYSTEM_PROMPT_EJECUTOR,
        mcp_servers={"allo-tools": allo_tools_server},
        allowed_tools=[
            "mcp__allo-tools__run_l1_parse_types",
            "mcp__allo-tools__run_l2_functional",
            "mcp__allo-tools__run_l3_equivalence",
            "mcp__allo-tools__run_l4_hls",
        ],
        # CRÍTICO: sin esto, si el modelo intenta usar CUALQUIER otra
        # herramienta (p. ej. Read/Bash para "investigar" un error de
        # Allo, como probablemente ocurrió en la Iteración 2 del 6 de
        # agosto con el error de BITREV), el proceso se queda colgado
        # esperando una aprobación de permiso que nunca llega -- el script
        # no tiene un terminal interactivo real conectado a ese prompt.
        # "dontAsk" deniega automáticamente cualquier cosa fuera de
        # allowed_tools en vez de esperar.
        permission_mode="dontAsk",
    )
    prompt = (
        "Ejecuta la cascada de validación EN ORDEN (L1, L2, L3, L4) sobre el "
        "siguiente código Allo. Detente en el primer nivel que falle y "
        "reporta el resultado tal cual lo devuelve la herramienta.\n\n"
        f"golden_model_id: {spec['golden_model_id']}\n"
        f"objetivo_ii: {spec['restricciones']['objetivo_ii']}\n\n"
        f"CODIGO:\n{codigo_allo}"
    )

    salida_texto = ""
    async for msg in query(prompt=prompt, options=opciones):
        if isinstance(msg, AssistantMessage):
            for bloque in msg.content:
                if isinstance(bloque, TextBlock):
                    salida_texto += bloque.text
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
    catalogo_validados = []  # espejo en memoria de lo que también se escribe a disco

    for i in range(1, MAX_ITERACIONES + 1):
        print(f"\n=== Iteración {i}/{MAX_ITERACIONES} ===")

        codigo = await llamar_generador(spec, historial_errores)
        print("--- Código generado ---")
        print(codigo[:400], "..." if len(codigo) > 400 else "")

        # IMPORTANTE (6 de agosto de 2026, ver docs/bitacora.md): el propio
        # SDK tiene un bug conocido (issue #1031 en
        # anthropics/claude-agent-sdk-python) por el que, ante un fallo a
        # nivel de API (posiblemente un límite de cuota de la suscripción
        # Pro, dado el volumen de llamadas automatizadas), lanza una
        # excepción con el mensaje engañoso "Claude Code returned an error
        # result: success" -- el mensaje humano real queda descartado
        # internamente por el SDK, así que no podemos recuperarlo aquí.
        #
        # Sin este try/except, CUALQUIER hipo de infraestructura (este bug,
        # un timeout de red, un rate limit) tumba las MAX_ITERACIONES
        # enteras de golpe, perdiendo todo el progreso de iteraciones
        # anteriores. Lo tratamos como un fallo transitorio: se registra,
        # se cuenta como un "continuar" genérico (sin tocar
        # fallos_l2_seguidos ni el historial más allá de anotar el
        # incidente), y se pasa a la siguiente iteración en vez de abortar
        # el proceso completo.
        try:
            resultado = await llamar_ejecutor(codigo, spec)
            informe = await llamar_validador(resultado, fallos_l2_seguidos)
        except Exception as e:  # noqa: BLE001 -- fallo de infraestructura, no de Allo
            print(f"⚠️  Fallo de infraestructura en la Iteración {i} (Ejecutor/Validador): "
                  f"{type(e).__name__}: {e}")
            print("    Tratado como transitorio -- se reintenta en la siguiente iteración "
                  "sin descartar el historial de errores acumulado.")
            historial_errores.append(
                f"[Iteración {i}] Fallo de infraestructura al validar (no de Allo): "
                f"{type(e).__name__}. Se reintenta."
            )
            continue

        print(f"--- Informe del validador: nivel_fallo={informe.nivel_fallo}, "
              f"decision={informe.decision_escalada} ---")
        print(informe.mensaje_accionable)

        if informe.nivel_fallo == NivelFallo.NINGUNO:
            ruta = guardar_en_catalogo(spec, codigo, informe.metricas_hls)
            print(f"\n✅ Éxito. Guardado en el catálogo: {ruta}")
            catalogo_validados.append({"spec": spec, "codigo": codigo, "metricas": informe.metricas_hls})
            break

        if informe.nivel_fallo == NivelFallo.L2_FUNCIONAL:
            fallos_l2_seguidos += 1
        else:
            fallos_l2_seguidos = 0

        if informe.decision_escalada == DecisionEscalada.REGENERAR_DESDE_CERO:
            print("↻ Regenerando desde cero (se descarta el historial de errores).")
            historial_errores = []
        elif informe.decision_escalada == DecisionEscalada.SOLO_TOCAR_SCHEDULE:
            print("🔒 Kernel congelado — el siguiente intento solo debe tocar el schedule.")
            historial_errores = [
                f"El kernel es correcto (pasó L1-L3). Solo ajusta el SCHEDULE: {informe.mensaje_accionable}"
            ]
        else:
            historial_errores.append(informe.mensaje_accionable)
    else:
        print(f"\n⚠️ Se agotó el presupuesto de {MAX_ITERACIONES} iteraciones sin converger.")


if __name__ == "__main__":
    asyncio.run(main())
