# Entorno unificado: Allo + agentes, todo dentro de un contenedor Linux

> **Nota (29 de julio de 2026):** en el equipo Windows de pruebas de este
> TFG, Docker Desktop dio el error `Virtualization support not detected` y
> no se consiguió resolver a pesar de: activar SVM Mode en BIOS, activar
> `VirtualMachinePlatform`/WSL como funciones de Windows, desinstalar
> VirtualBox, y descartar antivirus de terceros. La causa raíz no quedó
> confirmada (hipótesis: Seguridad Basada en Virtualización de Windows 11
> 25H2 reservando el hipervisor para Credential Guard sin dejar partición
> libre para WSL2). **La vía que sí funcionó fue usar un equipo con Linux
> nativo**, sin Docker — ver `docs/bitacora.md`, entrada del 29 de julio,
> para el diagnóstico completo. Esta guía se mantiene por si se retoma el
> diagnóstico en Windows más adelante, o para otros equipos donde Docker
> Desktop sí funcione sin problemas.

Esta guía asume que ya tienes:
- Docker Desktop instalado (con WSL2 activado)
- El repo de Allo clonado con `git clone --recursive` (NO el ZIP — le faltan los submódulos)
- Esta carpeta (`allo-agent-pipeline`) con los archivos del pipeline de agentes

Y que ambas carpetas están en tu disco de Windows, por ejemplo:

```
C:\Users\Pablo\Documents\allo                    <- repo de Allo clonado
C:\Users\Pablo\Documents\allo-agent-pipeline      <- este proyecto
```

Ajusta las rutas de los comandos si las tuyas son distintas.

---

## Paso 1 — Construir la imagen (una sola vez)

Desde PowerShell, dentro de la carpeta `allo-agent-pipeline` (donde está el `Dockerfile`):

```powershell
cd C:\Users\Pablo\Documents\allo-agent-pipeline
docker build -t allo-agents .
```

Esto tarda unos minutos la primera vez (descarga la imagen base de Allo + instala Node y el SDK). Las siguientes veces será instantáneo gracias a la caché de Docker, a menos que cambies el `Dockerfile`.

---

## Paso 2 — Entrar al contenedor con tus dos carpetas montadas

```powershell
docker run --rm -it `
  -v C:\Users\Pablo\Documents\allo:/workspace/allo `
  -v C:\Users\Pablo\Documents\allo-agent-pipeline:/workspace/allo-agent-pipeline `
  allo-agents bash
```

(El backtick `` ` `` es el "continúa en la siguiente línea" de PowerShell; también puedes escribirlo todo en una sola línea sin backticks.)

Ahora estás **dentro** de un shell Linux, con ambas carpetas de Windows visibles en `/workspace/`. Cualquier cambio que hagas ahí también se guarda en tu disco de Windows — no se pierde al cerrar el contenedor.

---

## Paso 3 — Instalar Allo (dentro del contenedor)

```bash
cd /workspace/allo
python3 -m pip install -v -e .
```

Esto compila las extensiones de Allo contra el LLVM que ya viene en la imagen. Puede tardar varios minutos.

Verifica que funcionó:

```bash
python3 -c "import allo; import allo.ir"
```

Sin errores = listo.

---

## Paso 4 — Autenticarte con tu plan Pro (dentro del contenedor)

```bash
cd /workspace/allo-agent-pipeline
claude login
```

Te dará una URL para abrir en el navegador de tu Windows normal (fuera del contenedor) y autenticarte con tu cuenta Pro. Sigue las instrucciones en pantalla.

---

## Paso 5 — Probar el test mínimo

```bash
python3 test_minimo.py
```

Debería funcionar igual que en Windows, pero ahora ejecutándose en el mismo entorno donde vive Allo.

---

## Paso 6 — Conectar Allo de verdad al pipeline

Este es el trabajo que queda pendiente y lo hacemos juntos en cuanto llegues hasta aquí: sustituir las funciones `MOCK_*` de `allo_tools.py` por las llamadas reales, ahora que `import allo` funciona en el mismo proceso Python que ejecuta el orquestador. Como ya no hay que cruzar entre Windows y Linux, cada función se convierte simplemente en:

```python
import allo
# ...
s = allo.customize(mi_kernel)   # en vez del bloque MOCK
```

Cuando llegues a este punto, dime y repasamos juntos la sintaxis exacta de `allo.customize()`, `s.build()`, etc. contra la documentación de Allo para tu caso concreto (la mariposa FFT del `spec_example.yaml`).

---

## Nota sobre persistencia

El flag `--rm` borra el contenedor al salir (pero no las carpetas montadas, esas son tuyas). Lo único que se pierde es lo que hayas instalado *dentro* del contenedor con `pip`/`apt` fuera de lo que ya está en el `Dockerfile` — como Allo se reinstala desde el volumen montado cada vez, no pasa nada. Si prefieres no tener que ejecutar `pip install -e .` y `claude login` cada vez que entras, dímelo y te preparo una variante que guarda el contenedor entre sesiones (`docker start`/`docker attach` en vez de `--rm`).
