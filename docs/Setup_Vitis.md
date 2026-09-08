# Instalación de Vitis HLS en Ubuntu (para el nivel L4 de la cascada)

> **Contexto:** L4 (síntesis HLS) estaba pendiente de decisión: o se implementaba
> con el toolchain real de Vitis HLS, o se dejaba como "L4-lite" (solo
> generación de código HLS C++ vía `target="vhls"`, sin síntesis real). Se optó
> por instalar Vitis HLS de verdad porque **la síntesis C (`csyn`) no requiere
> licencia de pago** — solo haría falta licencia de Vivado si se quisiera llegar
> a implementación de RTL, que no es el alcance de este TFG.

## Entorno de partida

- Ubuntu 24.04.4 LTS ("noble")
- Sin Docker de por medio (se descartó en la entrada del 29 de julio; se
  instala directamente en el Linux nativo del equipo)

## 1. Versión elegida: Vitis HLS 2023.1 (no la última)

El propio paper de Allo (PLDI'24) y su artifact de reproducción usan **Vitis
HLS 2022.1**, con el flujo "classic" (`vitis_hls` + `run.tcl`). Desde 2023.1+
AMD ha ido migrando todo al nuevo Vitis Unified IDE y el modo classic está en
proceso de deprecación — el backend `target="vitis_hls"` de Allo depende de
ese flujo classic.

Se descartó 2022.1 porque solo tiene soporte oficial hasta Ubuntu 20.04.
Se eligió **2023.1** como compromiso: es la primera versión con soporte
oficial de Ubuntu 22.04+ que todavía conserva el modo classic disponible.

## 2. Dependencias del sistema: la odisea de `ncurses`/`tinfo`

Vitis todavía depende de tres librerías del sistema que Canonical eliminó de
los repos por defecto a partir de Ubuntu 22.04 (y ya no están ni en
`universe` en 24.04): `libtinfo5`, `libncurses5`, `libncursesw5`.

```bash
sudo apt install libtinfo5 libncurses5 libncursesw5
# E: No se ha podido localizar el paquete libtinfo5
# E: No se ha podido localizar el paquete libncurses5
# E: No se ha podido localizar el paquete libncursesw5
```

**Intento 1 — paquetes de Launchpad (Ubuntu 22.04/jammy):** funcionó para
`libtinfo5` y `libncurses5`, pero la versión concreta de `libncursesw5` que
se buscó ya no estaba disponible en ese mirror (`archive.ubuntu.com` y varios
mirrors universitarios devolvían 404 para el mismo fichero — los mirrors van
limpiando versiones antiguas sin previo aviso).

```bash
wget http://launchpadlibrarian.net/648013231/libtinfo5_6.4-2_amd64.deb
sudo dpkg -i libtinfo5_6.4-2_amd64.deb

wget http://launchpadlibrarian.net/648013227/libncurses5_6.4-2_amd64.deb
sudo dpkg -i libncurses5_6.4-2_amd64.deb
```

**Intento 2 — `libncursesw5` desde el repositorio de Debian
(`deb.debian.org`)**, que sí lo mantenía disponible, aunque en una versión
distinta (6.4-4 en vez de 6.4-2):

```bash
wget https://deb.debian.org/debian/pool/main/n/ncurses/libncursesw5_6.4-4_amd64.deb
sudo dpkg -i libncursesw5_6.4-4_amd64.deb
```

Esto generó un **conflicto de versiones cruzado**: `libncursesw5` 6.4-4
exige `libtinfo5` en exactamente esa misma versión, pero el sistema tenía la
6.4-2 de Launchpad — `apt --fix-broken install` resolvía el conflicto
desinstalando el paquete recién puesto en vez de arreglarlo.

**Solución final:** subir las tres librerías a la misma versión (6.4-4),
todas desde la misma fuente (Debian), instalándolas juntas en el mismo
comando `dpkg -i` para que las dependencias cruzadas se resuelvan de una vez:

```bash
wget https://deb.debian.org/debian/pool/main/n/ncurses/libtinfo5_6.4-4_amd64.deb
wget https://deb.debian.org/debian/pool/main/n/ncurses/libncurses5_6.4-4_amd64.deb
wget https://deb.debian.org/debian/pool/main/n/ncurses/libncursesw5_6.4-4_amd64.deb
sudo dpkg -i libtinfo5_6.4-4_amd64.deb libncurses5_6.4-4_amd64.deb libncursesw5_6.4-4_amd64.deb
sudo apt --fix-broken install
```

Verificación:
```bash
dpkg -l | grep -E "libtinfo5|libncurses5|libncursesw5"
# ii  libncurses5:amd64    6.4-4   shared libraries for terminal handling (legacy version)
# ii  libncursesw5:amd64   6.4-4   shared libraries for terminal handling (wide character legacy version)
# ii  libtinfo5:amd64      6.4-4   shared low-level terminfo library (legacy version)
```

**Lección para la memoria del TFG:** aunque son paquetes de Debian (no
Ubuntu), son binariamente compatibles porque comparten la misma ABI de glibc
en amd64 — la fuente del `.deb` importa menos que tener **todas las
dependencias cruzadas en la misma versión exacta**.

## 3. Descarga del instalador

Cuenta gratuita en `account.amd.com` (Job Function: Student), descarga del
**AMD Unified Installer for Linux** (`Xilinx_Unified_2023.1_..._Lin64.bin`).

```bash
chmod +x Xilinx_Unified_2023.1_0507_1903_Lin64.bin
./Xilinx_Unified_2023.1_0507_1903_Lin64.bin
```

## 4. Selección de producto y componentes

- **Select Product to Install:** `Vitis` (ya incluye Vivado Design Suite
  integrado — no hace falta seleccionarlo aparte).
- **Vitis Unified Software Platform**, deseleccionando lo que no hace falta
  para reducir tamaño de descarga:
  - ❌ Vitis Model Composer (MATLAB/Simulink)
  - ❌ DocNav (documentación offline)
  - ❌ Install devices for Alveo and edge acceleration platforms
  - ❌ Install Devices for Kria SOMs and Starter Kits
  - Dentro de *Devices for Custom Platforms*: solo se dejó marcado
    **UltraScale+** (familia del Alveo U280, la placa usada en el propio
    paper/artifact de Allo — mantiene compatibilidad si en el futuro se
    quieren comparar métricas con sus resultados publicados). Se
    desmarcaron SoCs, 7 Series, UltraScale y Versal ACAP.

## 5. Ruta de instalación

**Problema:** la ruta por defecto `/tools/Xilinx` da error
`Cannot write to /tools/Xilinx. Check the read/write permissions.` porque
esa carpeta no es escribible sin sudo, y el instalador corre como usuario
normal (correcto, no debe correr como root).

**Solución:** instalar bajo el home del usuario:
```
/home/pablo/tools/Xilinx
```

## 6. Post-instalación

**Nota sobre la ruta real:** aunque en el paso 5 se pidió instalar bajo
`/home/pablo/tools/Xilinx`, el instalador terminó colocando Vitis HLS en
`~/tools/Vitis_HLS/2023.1` (sin la carpeta intermedia `Xilinx/Vitis` que
cabría esperar por el nombre del producto elegido). Verificar siempre la
ruta real tras la instalación en vez de asumirla por convención.

```bash
# Instalar librerías de sistema que pide el propio instalador al terminar
sudo bash ~/tools/Vitis_HLS/2023.1/scripts/installLibs.sh

# Cargar el entorno
source ~/tools/Vitis_HLS/2023.1/settings64.sh

# Verificar
which vitis_hls
vitis_hls -version
```

### Bache: locale `en_US.UTF-8` no generado

Primer arranque de `vitis_hls` tras el `source` falló con:

```
aviso: setlocale: LC_ALL: no se puede cambiar el local (en_US.UTF-8)
terminate called after throwing an instance of 'std::runtime_error'
  what():  locale::facet::_S_create_c_locale name not valid
```

Vitis HLS asume que el locale `en_US.UTF-8` está generado en el sistema, algo
que Ubuntu no trae por defecto en instalaciones en español. Solución:

```bash
sudo locale-gen en_US.UTF-8
sudo update-locale LANG=en_US.UTF-8
```

(reabrir la terminal, o `exec bash`, para que el nuevo locale se cargue).

### Dejarlo persistente

```bash
echo 'source ~/tools/Vitis_HLS/2023.1/settings64.sh' >> ~/.bashrc
```

## Estado: ✅ Vitis HLS 2023.1 instalado y verificado

```
Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
```

## Pendiente

- Sustituir el mock de `run_l4_hls` en `allo_tools.py` por la llamada real
  (`allo.customize(...).build(target="vivado_hls", mode="csyn", project=...)`)
  y confirmar la ruta exacta del informe `*_csynth.xml` generado por esta
  versión concreta (2023.1) — puede variar respecto a lo documentado para
  otras versiones.
