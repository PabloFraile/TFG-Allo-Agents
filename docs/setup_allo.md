# Instalación de Allo desde fuente — Guía de referencia

Guía completa para instalar el toolchain de **Allo** (github.com/cornell-zhang/allo)
desde fuente en Linux, sustituyendo las funciones mockeadas de `allo_tools.py`
por el compilador real. Incluye al final los errores encontrados durante la
instalación en este proyecto y cómo se resolvieron, por si se repite en otra
máquina.

> Entorno de referencia: Ubuntu (Linux nativo), Python 3.12, CMake 3.28,
> Ninja 1.11.1. Allo depende de compilar LLVM/MLIR y solo tiene soporte
> oficial en Linux.

---

## 0. Requisitos previos

```bash
sudo apt install ninja-build cmake
```

Confirmar que el repositorio de Allo está clonado con submódulos (Allo
referencia su propia versión de `llvm-project` como submódulo, con un commit
concreto pinneado):

```bash
cd external/allo
cat .gitmodules
```

Debería mostrar algo como:

```
[submodule "externals/llvm-project"]
	path = externals/llvm-project
	url = https://github.com/llvm/llvm-project.git

[submodule "externals/past-python-bindings"]
	path = externals/past-python-bindings
	url = https://github.com/cornell-zhang/past-python-bindings.git
```

Si los submódulos no están descargados:

```bash
git submodule update --init --recursive
```

---

## 1. Compilar LLVM/MLIR desde fuente

Allo **no compila su propia copia de LLVM** — asume que ya existe un build
hecho aparte, y se le indica la ruta vía la variable de entorno
`LLVM_BUILD_DIR`. Este es el paso más largo del proceso (puede tardar de 30
minutos a más de 2 horas según el hardware).

```bash
cd external/allo/externals/llvm-project
mkdir build && cd build

cmake -G Ninja ../llvm \
  -DLLVM_ENABLE_PROJECTS=mlir \
  -DLLVM_BUILD_EXAMPLES=ON \
  -DLLVM_TARGETS_TO_BUILD="host" \
  -DCMAKE_BUILD_TYPE=Release \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DLLVM_INSTALL_UTILS=ON \
  -DMLIR_ENABLE_BINDINGS_PYTHON=ON \
  -DPython3_EXECUTABLE=$(which python3)

ninja
```

**Notas:**
- Si el equipo tiene poca RAM (≤8 GB), usa `ninja -j2` o `ninja -j1` en vez
  de `ninja` a secas (que usa todos los núcleos por defecto) para evitar que
  el sistema se quede sin memoria a mitad de compilación (síntoma típico:
  el proceso se cuelga o la terminal se cierra sola).
- Es recomendable lanzar la compilación dentro de `tmux` o `screen`, para
  que si la terminal se cierra por cualquier motivo, el proceso de
  compilación siga vivo en segundo plano:

  ```bash
  tmux new -s build_llvm
  # dentro de tmux: lanzar el cmake + ninja de arriba
  # para salir sin matar el proceso: Ctrl+B, luego D
  # para volver a engancharte: tmux attach -t build_llvm
  ```

- Como Ninja es incremental, si el proceso se interrumpe se puede relanzar
  el mismo `ninja` y retomará donde se quedó, sin recompilar desde cero.

Confirmar que terminó bien: debe aparecer una línea final del tipo
`[N/N] Linking CXX ...` sin errores.

---

## 2. Exportar `LLVM_BUILD_DIR`

```bash
export LLVM_BUILD_DIR=$(pwd)   # estando dentro de externals/llvm-project/build
```

Para que persista entre sesiones de terminal:

```bash
echo 'export LLVM_BUILD_DIR=/ruta/completa/a/externals/llvm-project/build' >> ~/.bashrc
```

---

## 3. Instalar `nanobind`

Allo usa `nanobind` para los bindings de Python con MLIR:

```bash
pip install --break-system-packages nanobind
```

---

## 4. Instalar Allo

```bash
cd external/allo
pip install --break-system-packages --no-build-isolation -v -e .
```

El flag **`--no-build-isolation`** es importante: sin él, pip crea un
entorno aislado temporal para las dependencias de build declaradas en
`pyproject.toml`, y el `ninja` de ese entorno aislado puede no resolverse
correctamente. Con este flag, pip reutiliza el `ninja`/`cmake` ya
instalados en el sistema.

Este paso compila las extensiones propias de Allo en C++/MLIR enlazando
contra el LLVM ya construido — tarda bastante menos que el paso 1, pero no
es instantáneo (varios minutos).

---

## 5. Verificar la instalación

```bash
python3 -c "import allo; import allo.ir; print('OK')"
```

Si imprime `OK` sin errores, la instalación está completa.

---

## Errores encontrados y cómo se resolvieron

Durante la instalación en este proyecto aparecieron, en orden, los
siguientes errores. Se documentan aquí por si se repiten en otra máquina —
cada uno solo se hizo visible al resolver el anterior.

### Error 1 — `RuntimeError: LLVM_BUILD_DIR environment variable is not set`

**Causa:** se intentó `pip install -e .` sin haber compilado LLVM/MLIR
primero, o sin haber exportado la variable de entorno.

**Solución:** completar los pasos 1 y 2 de esta guía antes de instalar Allo.

---

### Error 2 — `ninja: no such file or directory` (dentro del build aislado de pip)

**Síntoma:** el log de instalación mostraba algo como:

```
'/tmp/pip-build-env-XXXXXXXX/overlay/local/bin/ninja' '--version'
failed with:
no such file or directory
```

**Causa:** pip, al procesar `pyproject.toml`, crea un entorno aislado
temporal (`overlay`) e instala ahí las dependencias de build declaradas
(incluyendo un paquete `ninja` de PyPI, distinto del `ninja-build` del
sistema). Ese `ninja` de pip no se resolvía correctamente como ejecutable
dentro del entorno aislado.

**Solución:** usar `--no-build-isolation` para que pip reutilice las
herramientas ya instaladas en el sistema (`ninja-build`, `cmake`) en vez de
crear el entorno aislado:

```bash
pip install --break-system-packages --no-build-isolation -v -e .
```

---

### Error 3 — `RuntimeError: nanobind is not installed`

**Causa:** falta la dependencia de Python `nanobind`, que Allo usa para los
bindings con MLIR.

**Solución:**

```bash
pip install --break-system-packages nanobind
```

---

### Error 4 — `CMake Error ... Could not find a package configuration file provided by "MLIR"`

**Síntoma:**

```
CMake Error at CMakeLists.txt:17 (find_package):
  Could not find a package configuration file provided by "MLIR" with any of
  the following names:
    MLIRConfig.cmake
    mlir-config.cmake
```

**Causa:** el archivo `MLIRConfig.cmake` no se había generado dentro del
build de LLVM (`build/lib/cmake/mlir/`), aunque el equivalente de LLVM
(`LLVMConfig.cmake`) sí existía. Se confirmó que `LLVM_ENABLE_PROJECTS=mlir`
estaba correctamente activo en la caché de CMake, y que `tools/mlir` sí se
había compilado — el problema era solo que el archivo de configuración
exportable para consumidores externos no se generó en la fase de
configuración inicial.

**Solución:** reconfigurar CMake in-place dentro del build de LLVM (sin
recompilar nada, tarda solo unos segundos):

```bash
cd external/allo/externals/llvm-project/build
cmake .
```

Verificar que se generó:

```bash
find . -iname "MLIRConfig.cmake"
```

---

### Error 5 — `ninja: error: '.../build/bin/mlir-tblgen', needed by '...', missing and no known rule to make it`

**Causa:** consecuencia directa del error 4. La compilación original de
LLVM (con `ninja`, los "855/855" pasos) se había completado **antes** de
que la configuración de MLIR quedara resuelta, así que el `build.ninja` de
aquel momento nunca incluyó los targets específicos de MLIR (como
`mlir-tblgen`). Al reconfigurar con `cmake .` (error 4), el `build.ninja`
se actualizó para incluir esos targets, pero nunca se había vuelto a
ejecutar `ninja` para compilarlos de verdad.

**Solución:** relanzar Ninja en el build de LLVM. Al ser incremental, no
repite el trabajo ya hecho — solo compila los targets nuevos que faltan:

```bash
cd external/allo/externals/llvm-project/build
ninja -j2
```

Verificar que el binario existe:

```bash
ls -la bin/mlir-tblgen
```

---

### Error 6 — El mismo error del `ninja` aislado (Error 2) reaparece aunque ya se use `--no-build-isolation`

**Causa:** una carpeta de build propia de Allo (`external/allo/mlir/build/`,
generada en el primer intento fallido, antes de añadir el flag correcto)
contenía un `CMakeCache.txt` que seguía apuntando al `ninja` roto del
entorno aislado de aquel primer intento. CMake reutilizaba esa caché vieja
en vez de reevaluar el comando nuevo, aunque el flag `--no-build-isolation`
ya estuviera puesto.

**Diagnóstico:** localizar la caché:

```bash
find external/allo -maxdepth 3 -iname "CMakeCache.txt"
```

**Solución:** borrar esa carpeta de build concreta (**no** la de
`externals/llvm-project/build`, esa debe conservarse) y reintentar desde
cero:

```bash
rm -rf external/allo/mlir/build
pip install --break-system-packages --no-build-isolation -v -e .
```

---

## Consejo general de depuración

Cuando `pip install -e .` falla, el traceback final de Python
(`subprocess.CalledProcessError: Command 'cmake'/'ninja' returned non-zero
exit status 1`) casi nunca contiene el motivo real — solo dice que el
subproceso falló. El error de verdad está más arriba en el log. Conviene
guardar siempre la salida completa y buscar en ella:

```bash
pip install --break-system-packages --no-build-isolation -v -e . 2>&1 | tee /tmp/allo_install.log

# Buscar errores de configuración de CMake:
grep -n -A 15 "CMake Error" /tmp/allo_install.log

# Si no aparece nada, buscar errores de compilación:
grep -n -B2 -A 15 "error:" /tmp/allo_install.log | head -150

# Si el fallo es de Ninja en concreto, buscar el paso que falló:
grep -n -B2 -A 20 "FAILED:" /tmp/allo_install.log | head -150
```

Usar un nombre de log distinto en cada intento (`_v2`, `_v3`, ...) evita
confundir la salida de un intento antiguo con la del intento actual —
especialmente importante si se sospecha de una caché obsoleta, ya que un
error idéntico letra por letra entre dos intentos (mismo hash de carpeta
temporal, por ejemplo) es la señal de que se está mirando un log viejo, no
uno nuevo.
