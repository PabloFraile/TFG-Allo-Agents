"""
Test AISLADO de L4 (síntesis HLS real con Vitis HLS), fuera de allo_tools.py
y del orquestador -- mismo patrón incremental que se usó para validar L1-L3
antes de integrarlas.

Objetivo de este script:
  1. Confirmar que `s.build(target="vivado_hls", mode="csyn")` funciona con
     tu instalación de Vitis HLS 2023.1.
  2. Localizar dónde deja exactamente el informe de síntesis (*_csynth.xml),
     porque el path puede variar entre versiones de Vitis.

Requisito: haber hecho `source ~/tools/Vitis_HLS/2023.1/settings64.sh` en
la MISMA terminal donde lances este script (o exportar el PATH a mano al
principio del script -- ver más abajo la comprobación).

Kernel elegido: suma de vectores trivial, NO la FFT del proyecto -- aquí
solo queremos aislar el comportamiento de Vitis, no la corrección del
kernel real.
"""

import glob
import os
import shutil
import sys

import allo
from allo.ir.types import int32


def kernel(A: int32[32], B: int32[32], C: int32[32]):
    for i in range(32):
        C[i] = A[i] + B[i]


def main():
    if shutil.which("vitis_hls") is None:
        print("ERROR: vitis_hls no está en el PATH.")
        print("¿Has hecho 'source ~/tools/Vitis_HLS/2023.1/settings64.sh' en esta terminal?")
        sys.exit(1)

    print(f"vitis_hls encontrado en: {shutil.which('vitis_hls')}\n")

    project_dir = "test_l4.prj"

    print("Paso 1: allo.customize()...")
    s = allo.customize(kernel)
    print(s.module)
    print("OK\n")

    print(f"Paso 2: s.build(target='vivado_hls', mode='csyn', project='{project_dir}')...")
    mod = s.build(target="vivado_hls", mode="csyn", project=project_dir)
    print("OK: build() devolvió un módulo\n")

    print("Paso 3: ejecutando mod() para disparar la síntesis real...")
    print("(esto puede tardar 1-3 minutos, Vitis está compilando y sintetizando)")
    mod()
    print("OK: síntesis terminada sin excepción\n")

    print(f"Paso 4: buscando el informe de síntesis dentro de '{project_dir}'...\n")
    candidatos = glob.glob(f"{project_dir}/**/*csynth*", recursive=True)
    if not candidatos:
        print(f"No se encontró ningún archivo '*csynth*' bajo {project_dir}/")
        print("Estructura completa generada:")
        for root, dirs, files in os.walk(project_dir):
            for f in files:
                print(os.path.join(root, f))
    else:
        print(f"Encontrados {len(candidatos)} archivo(s) relacionados con csynth:")
        for c in candidatos:
            print(f"  {c}")


if __name__ == "__main__":
    main()
