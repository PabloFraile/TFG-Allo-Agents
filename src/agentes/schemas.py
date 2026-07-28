"""
Define la FORMA exacta del informe que el agente Validador debe producir
tras analizar el resultado del Ejecutor.

Usar un esquema tipado (Pydantic) en vez de dejar que el modelo devuelva
texto libre es lo que permite que el orquestador tome decisiones automáticas
(regenerar desde cero, congelar el kernel y tocar solo el schedule, etc.)
sin tener que parsear lenguaje natural.
"""

from enum import Enum
from typing import Optional
from pydantic import BaseModel, Field


class NivelFallo(str, Enum):
    NINGUNO = "ninguno"       # todo pasó — éxito
    L1_SINTAXIS = "L1"        # error de sintaxis/tipos (allo.customize)
    L2_FUNCIONAL = "L2"       # el resultado numérico no coincide con el golden model
    L3_EQUIVALENCIA = "L3"    # el schedule rompió la semántica del kernel
    L4_HLS = "L4"             # no cumple objetivos de HLS (II, latencia, recursos)


class DecisionEscalada(str, Enum):
    CONTINUAR = "continuar"              # reintentar con el mismo enfoque
    REGENERAR_DESDE_CERO = "regenerar"   # descartar historial, empezar de nuevo
    SOLO_TOCAR_SCHEDULE = "solo_schedule"  # el kernel es correcto, congelarlo


class InformeValidacion(BaseModel):
    nivel_fallo: NivelFallo = Field(
        description="En qué nivel de la cascada falló (o 'ninguno' si pasó todo)"
    )
    mensaje_accionable: str = Field(
        description="Explicación breve y concreta de qué falló y por qué, "
                    "en términos que el agente Generador pueda usar para corregir el código"
    )
    diff_numerico: Optional[str] = Field(
        default=None,
        description="Si el fallo es L2: resumen del diff contra el golden model "
                    "(p. ej. primeros índices discrepantes)"
    )
    metricas_hls: Optional[dict] = Field(
        default=None,
        description="Si se llegó a L4: II conseguido, latencia, BRAM/DSP/LUT"
    )
    decision_escalada: DecisionEscalada = Field(
        description="Qué debe hacer el orquestador en la siguiente iteración"
    )


class ResultadoNivel(BaseModel):
    """Resultado crudo de un único nivel de la cascada, tal como lo devuelve
    una herramienta del Ejecutor (antes de que el Validador lo interprete)."""
    nivel: str
    ok: bool
    salida_cruda: str
