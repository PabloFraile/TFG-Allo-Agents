"""
Ejecuta allo.verify(s, s_orig) en un PROCESO SEPARADO (no in-process),
para aislar orchestrator.py de crashes nativos del verificador PAST.

Descubierto el 15 de agosto de 2026 (ver docs/bitacora.md): PAST tiene
reglas gramaticales sin implementar ("[PAST][Parser] Rule 7 not
implemented!") que en ciertos casos no solo producen un árbol
incompleto/inconsistente, sino que además disparan un assert() de C++
(`core/past.c:2489: set_parent_pref: Assertion 'n->rhs' failed.`) que
termina en abort() -- SIGABRT. Esto mata el proceso Python ENTERO, no es
una excepción de Python capturable con try/except (ni siquiera con
except BaseException). La única forma de sobrevivir a esto es que el
crash ocurra en un proceso hijo desechable, no en el proceso principal
que lleva el estado de las 6 iteraciones.

Uso: se invoca vía subprocess.run() desde run_l3_equivalence() en
allo_tools.py, nunca se ejecuta como script de primer nivel a mano.

Protocolo (revisado 16 de agosto de 2026, ver docs/bitacora.md): recibe
el código Allo completo por stdin y la RUTA de un archivo de salida como
argv[1]. Escribe el JSON del resultado a ESE ARCHIVO, no a stdout -- el
panel nativo de diagnóstico de PAST (C++) también escribe a stdout/stderr
y puede mezclarse de forma impredecible con cualquier print() de Python,
corrompiendo un JSON que se intentara leer desde ahí (visto el 15/16 de
agosto: la verificación SÍ tenía éxito, pero el parseo de stdout fallaba
por bytes corruptos intercalados). Escribir a un archivo dedicado evita
depender por completo de lo que pase por stdout/stderr.
"""

import contextlib
import io
import json
import sys

import allo

# Importa las utilidades compartidas del propio allo_tools.py -- este
# script vive en la misma carpeta (src/agentes/), así que el import
# funciona igual que en el proceso principal.
from allo_tools import _extraer_bloques, _cargar_kernel_desde_disco, _construir_schedule, ERRORES_CAPTURABLES


def main():
    ruta_salida = sys.argv[1]
    codigo = sys.stdin.read()
    log_verify = io.StringIO()

    try:
        kernel_src, schedule_src = _extraer_bloques(codigo)
        kernel_fn = _cargar_kernel_desde_disco(kernel_src)

        s_orig = allo.customize(kernel_fn)
        s = _construir_schedule(kernel_fn, schedule_src)

        with contextlib.redirect_stdout(log_verify):
            ok = bool(allo.verify(s, s_orig))

        if ok:
            salida = "Equivalencia de schedule verificada por allo.verify(s, s_orig)"
        else:
            salida = (
                "allo.verify(s, s_orig) devolvió False -- NO equivalente.\n"
                "Diagnóstico de PAST (verificador formal de Allo):\n"
                f"{log_verify.getvalue()[-4000:]}"
            )
        resultado = {"ok": ok, "salida_cruda": salida}

    except ERRORES_CAPTURABLES as e:  # noqa: BLE001
        resultado = {
            "ok": False,
            "salida_cruda": f"{type(e).__name__}: {e}",
        }
        log_parcial = log_verify.getvalue()
        if log_parcial:
            resultado["salida_cruda"] += f"\n\nLog parcial de PAST:\n{log_parcial[-2000:]}"

    # NUEVO: se escribe a un archivo dedicado (ruta_salida), NO a stdout.
    # Si PAST hace abort() DESPUÉS de este punto (no debería, ya tenemos
    # el resultado), el archivo ya quedó escrito de todas formas. Si
    # aborta ANTES (durante allo.verify()), el archivo nunca se crea -- el
    # padre lo detecta por ausencia del archivo, además de por el
    # returncode negativo.
    with open(ruta_salida, "w", encoding="utf-8") as f:
        json.dump(resultado, f)


if __name__ == "__main__":
    main()
