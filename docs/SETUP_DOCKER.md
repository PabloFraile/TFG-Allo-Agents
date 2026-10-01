# Alternativa en Docker (no utilizada en la versión final)

La vía soportada y validada para reproducir el entorno es Linux nativo —
ver `docs/setup_allo.md` y `docs/Setup_Vitis.md`. Esta nota documenta por
qué se descartó la alternativa en Docker, por si resulta útil retomarla
en otro equipo.

## Diagnóstico en Windows

En el equipo Windows usado inicialmente para las pruebas, Docker Desktop
devolvía el error `Virtualization support not detected`. Se intentó
resolver mediante:

- activar SVM Mode en la BIOS,
- activar las funciones de Windows `VirtualMachinePlatform` y WSL,
- desinstalar VirtualBox,
- descartar interferencia de antivirus de terceros.

Ninguna de estas acciones resolvió el problema. La causa raíz no quedó
confirmada; la hipótesis más probable es que la Seguridad Basada en
Virtualización de Windows 11 25H2 reserva el hipervisor para Credential
Guard sin dejar partición libre para WSL2. El diagnóstico completo está
en `docs/bitacora.md`.

Dado que Allo requiere compilar LLVM/MLIR y solo tiene soporte oficial en
Linux, se optó por usar directamente un equipo con Linux nativo en lugar
de seguir depurando la virtualización en Windows.

## Qué necesitaría la imagen, si se retoma

Un contenedor Linux con:

- las dependencias de compilación de Allo (LLVM/MLIR, toolchain de C++),
- Node.js (para instalar el Claude Agent SDK),
- Python 3 con las dependencias de `src/agentes/requirements.txt`,
- Allo instalado en modo editable desde el submódulo (`external/allo`),

montando como volúmenes tanto el repo de Allo como este repositorio, para
que los cambios se conserven fuera del contenedor. La autenticación
(`claude login`) se haría dentro del contenedor igual que en Linux
nativo, abriendo la URL resultante en el navegador del host.

Esta vía no se llegó a implementar — el equipo con Linux nativo cubrió
las necesidades del proyecto sin necesidad de contenedor.
