"""
Utilidades compartidas del baseline: rutas del repo, carga de specs y
traducción de la spec (la MISMA que recibe el Generador del pipeline) a una
firma C++ para Vitis HLS.

El baseline NO importa nada de los agentes (orchestrator.py, allo_tools.py,
schemas.py). Lo único que reutiliza del pipeline es `golden_models.py`, que
no es un agente sino la referencia numérica: usar exactamente el mismo golden
model y los mismos vectores de test es lo que hace comparables ambos
resultados.
"""

import copy
import sys
from pathlib import Path

import yaml

RAIZ_REPO = Path(__file__).resolve().parent.parent
DIR_AGENTES = RAIZ_REPO / "src" / "agentes"
DIR_CATALOGO = RAIZ_REPO / "results" / "catalogo"
DIR_RESULTADOS_BASELINE = RAIZ_REPO / "results" / "baseline"
SPEC_POR_DEFECTO = RAIZ_REPO / "specs" / "spec_example.yaml"

# Mismas condiciones de síntesis que L4. Copiadas del run.tcl que genera
# Allo (s.build(target="vivado_hls")): mismo dispositivo, mismo reloj, mismo
# flow_target. Si cambias la plantilla de Allo, cámbialas aquí también.
PART_POR_DEFECTO = "xcu280-fsvh2892-2L-e"
PERIODO_RELOJ_NS_POR_DEFECTO = 3.33
FLOW_TARGET_POR_DEFECTO = "vivado"

# Mismo timeout que TIMEOUT_SINTESIS_L4_SEGUNDOS en allo_tools.py.
TIMEOUT_VITIS_POR_DEFECTO = 1800

# Misma tolerancia que L2 (allo_tools.run_l2_functional): |diff| < 1e-3
# elemento a elemento, en cada salida.
TOLERANCIA_POR_DEFECTO = 1e-3

# Mismo presupuesto que MAX_ITERACIONES del orquestador (modo feedback).
MAX_ITERACIONES_POR_DEFECTO = 6

TIPOS_ALLO_A_CPP = {
    "allo.float32": ("float", "float32"),
    "allo.float64": ("double", "float64"),
    "allo.int32": ("int", "int32"),
    "allo.int16": ("short", "int16"),
    "allo.int8": ("signed char", "int8"),
    "allo.uint32": ("unsigned int", "uint32"),
    "allo.uint16": ("unsigned short", "uint16"),
    "allo.uint8": ("unsigned char", "uint8"),
}


def importar_golden_models():
    """Importa golden_models.py del pipeline sin importar ningún agente."""
    if str(DIR_AGENTES) not in sys.path:
        sys.path.insert(0, str(DIR_AGENTES))
    import golden_models  # noqa: E402

    return golden_models


def cargar_spec(ruta: Path, objetivo_ii: int | None = None) -> dict:
    with open(ruta) as f:
        spec = yaml.safe_load(f)
    spec = copy.deepcopy(spec)
    if objetivo_ii is not None:
        spec.setdefault("restricciones", {})["objetivo_ii"] = objetivo_ii
    if "objetivo_ii" not in spec.get("restricciones", {}):
        raise ValueError("La spec no define restricciones.objetivo_ii y no se pasó --objetivo-ii")
    return spec


def tipo_cpp(puerto: dict) -> str:
    try:
        return TIPOS_ALLO_A_CPP[puerto["tipo"]][0]
    except KeyError:
        raise ValueError(
            f"Tipo '{puerto['tipo']}' del puerto '{puerto['nombre']}' sin traducción a C++ "
            f"en comun.TIPOS_ALLO_A_CPP"
        ) from None


def tipo_numpy(puerto: dict) -> str:
    return TIPOS_ALLO_A_CPP[puerto["tipo"]][1]


def dims_cpp(puerto: dict) -> str:
    return "".join(f"[{d}]" for d in puerto["forma"])


def nombre_top(spec: dict) -> str:
    return spec["bloque"]


def firma_cpp(spec: dict) -> str:
    """Firma obligatoria de la función top: entradas const, salidas escritas
    in-place (mismo patrón que la firma kernel(x_real, x_imag, y_real, y_imag)
    que asume L2)."""
    params = [f"const {tipo_cpp(p)} {p['nombre']}{dims_cpp(p)}" for p in spec["entradas"]]
    params += [f"{tipo_cpp(p)} {p['nombre']}{dims_cpp(p)}" for p in spec["salidas"]]
    return f"void {nombre_top(spec)}(\n    " + ",\n    ".join(params) + "\n)"
