"""
Arnés de validación del baseline VHDL: lo que sustituye a L1-L4 cuando el
código no es Allo ni HLS C++, sino VHDL escrito directamente por Claude.

  - L1 (compila)          -> análisis con GHDL (VHDL-2008) del kernel.vhd.
  - Interfaz              -> elaboración del testbench contra la entidad
                             pedida. Si el kernel analiza pero el testbench no
                             elabora, la entidad no es la que se pidió.
  - L2 (funcional)        -> simulación con un testbench generado AQUÍ (no por
                             Claude): carga el mismo vector de entrada que L2,
                             lanza el cálculo, mide la latencia en ciclos y
                             vuelca la salida; la comparación con el golden
                             model se hace en Python con la misma tolerancia
                             que L2 y que la csim del baseline C++.
  - L3 (equivalencia)     -> no existe equivalente. Diferencia cualitativa.
  - L4 (síntesis)         -> synth_design de Vivado fuera de contexto, mismo
                             part y mismo reloj que L4 y que el baseline C++.
                             Como en VHDL no existe el II, el criterio de
                             rendimiento es la latencia medida en simulación y
                             el periodo estimado tras la síntesis.

Igual que en el baseline C++, la síntesis se lanza aunque falle la
simulación, para poder medir cuántos diseños sintetizan siendo incorrectos.
"""

import math
import os
import re
import shutil
import signal
import subprocess
import time
from pathlib import Path

import numpy as np

from comun import nombre_top, tipo_numpy

MARCA_LAT = "BASELINE_LAT"
MARCA_SIM_FIN = "BASELINE_SIM_DONE"
MARCA_NO_TERMINA = "BASELINE_NO_DONE"
MARCA_SYN_FIN = "BASELINE_SYNTH_DONE"
MARCA_SYN_ERROR = "BASELINE_SYNTH_ERROR"
MARCA_WNS = "BASELINE_WNS"

# Ciclos máximos que el testbench espera a 'done' antes de darlo por colgado.
# Una FFT de 1024 puntos completamente secuencial (una mariposa cada varios
# ciclos) cabe holgadamente; un diseño que no levanta 'done' no.
MAX_CICLOS_POR_DEFECTO = 5_000_000
TIMEOUT_SIM_POR_DEFECTO = 900


# ---------------------------------------------------------------------------
# Interfaz fija (equivalente a la firma C++ obligatoria del baseline HLS)
# ---------------------------------------------------------------------------

def _comprobar_spec(spec: dict) -> int:
    puertos = spec["entradas"] + spec["salidas"]
    formas = {tuple(p["forma"]) for p in puertos}
    if len(formas) != 1 or len(next(iter(formas))) != 1:
        raise ValueError("El baseline VHDL asume que todas las entradas y salidas son vectores 1-D del mismo tamaño")
    if any(tipo_numpy(p) != "float32" for p in puertos):
        raise ValueError("El baseline VHDL solo soporta puertos allo.float32 (IEEE-754 binary32)")
    return next(iter(formas))[0]


def ancho_direccion(n: int) -> int:
    return max(1, math.ceil(math.log2(n)))


def entidad_vhdl(spec: dict) -> str:
    """Entidad obligatoria. Memoria de entrada con puerto de escritura,
    pulso start / nivel done, memoria de salida con puerto de lectura."""
    n = _comprobar_spec(spec)
    a = ancho_direccion(n)
    lineas = [
        "    clk      : in  std_logic;",
        "    rst      : in  std_logic;",
        "    in_we    : in  std_logic;",
        f"    in_addr  : in  std_logic_vector({a - 1} downto 0);",
    ]
    lineas += [f"    {p['nombre']:<8} : in  std_logic_vector(31 downto 0);" for p in spec["entradas"]]
    lineas += [
        "    start    : in  std_logic;",
        "    done     : out std_logic;",
        f"    out_addr : in  std_logic_vector({a - 1} downto 0);",
    ]
    lineas += [f"    {p['nombre']:<8} : out std_logic_vector(31 downto 0);" for p in spec["salidas"]]
    lineas[-1] = lineas[-1].rstrip(";")
    return (f"entity {nombre_top(spec)} is\n  port (\n" + "\n".join(lineas) + "\n  );\nend entity;")


def protocolo_interfaz(spec: dict) -> str:
    n = _comprobar_spec(spec)
    ent = ", ".join(p["nombre"] for p in spec["entradas"])
    sal = ", ".join(p["nombre"] for p in spec["salidas"])
    return f"""\
Protocolo de la interfaz (lo usa un testbench que ya existe; respétalo exactamente):
- Todos los datos son IEEE-754 binary32 (float32) en std_logic_vector(31 downto 0).
- rst es síncrono y activo a nivel alto. Tras el reset, done vale '0'.
- Carga: el testbench escribe las {n} muestras de entrada, una por ciclo, poniendo
  in_we='1', in_addr=i y los valores {ent}. La escritura se captura en el flanco de subida.
- Cálculo: después de la carga, el testbench pone start='1' durante un ciclo. El diseño
  pone done='0' mientras calcula y done='1' cuando la salida está completa; done se
  mantiene a '1' hasta el siguiente start.
- Lectura: con done='1', el testbench pone out_addr=i y lee {sal} en el ciclo siguiente
  (lectura registrada, latencia 1; una lectura combinacional también es válida)."""


# ---------------------------------------------------------------------------
# Vectores (mismos que L2 y que la csim del baseline C++) en hexadecimal
# ---------------------------------------------------------------------------

def _hex32(a: np.ndarray) -> list[str]:
    return [f"{int(u):08X}" for u in np.asarray(a, dtype=np.float32).view(np.uint32).ravel()]


def escribir_vectores(spec: dict, vector: dict, ruta: Path) -> None:
    columnas = [_hex32(vector["entradas"][p["nombre"]]) for p in spec["entradas"]]
    ruta.write_text("\n".join(" ".join(fila) for fila in zip(*columnas)) + "\n")


def leer_salida(spec: dict, ruta: Path) -> dict | None:
    if not ruta.exists():
        return None
    filas = [l.split() for l in ruta.read_text().splitlines() if l.strip()]
    n = _comprobar_spec(spec)
    if len(filas) != n:
        return None
    out = {}
    for k, p in enumerate(spec["salidas"]):
        bits = []
        for f in filas:
            try:
                bits.append(int(f[k], 16))
            except (ValueError, IndexError):
                bits.append(0x7FC00000)  # 'U'/'X' en la salida -> NaN (cuenta como fallo)
        out[p["nombre"]] = np.array(bits, dtype=np.uint32).view(np.float32)
    return out


def comparar(spec: dict, salida: dict, referencia: dict, tolerancia: float) -> tuple[bool, list[str]]:
    """Mismo criterio que L2: |y - ref| < tol en todos los elementos (NaN falla)."""
    ok, detalle = True, []
    for p in spec["salidas"]:
        y = salida[p["nombre"]].astype(np.float64)
        r = referencia[p["nombre"]].astype(np.float64)
        d = np.abs(y - r)
        malos = int(np.sum(~(d < tolerancia)))
        max_d = float(np.nanmax(d)) if np.any(np.isfinite(d)) else float("nan")
        if np.any(np.isnan(d)):
            max_d = float("nan")
        detalle.append(f"salida={p['nombre']} discrepantes={malos}/{y.size} max_abs_diff={max_d:.6g} tol={tolerancia:g}")
        ok &= malos == 0
    return ok, detalle


# ---------------------------------------------------------------------------
# Testbench VHDL (lo genera el arnés, no el LLM)
# ---------------------------------------------------------------------------

def escribir_testbench(spec: dict, ruta: Path, max_ciclos: int = MAX_CICLOS_POR_DEFECTO) -> None:
    n = _comprobar_spec(spec)
    a = ancho_direccion(n)
    top = nombre_top(spec)
    ent, sal = spec["entradas"], spec["salidas"]
    decl = "\n".join(f"  signal s_{p['nombre']} : std_logic_vector(31 downto 0) := (others => '0');" for p in ent + sal)
    mapa = ",\n".join(
        ["      clk => clk", "      rst => rst", "      in_we => in_we", "      in_addr => in_addr"]
        + [f"      {p['nombre']} => s_{p['nombre']}" for p in ent]
        + ["      start => start", "      done => done", "      out_addr => out_addr"]
        + [f"      {p['nombre']} => s_{p['nombre']}" for p in sal])
    # hread salta los espacios iniciales, así que las columnas se leen seguidas.
    lee_cols = "\n".join(f"      hread(l, v); s_{p['nombre']} <= v;" for p in ent)
    escr_cols = "\n".join(
        (f"      write(l, to_hstring(s_{p['nombre']}));" if i == 0 else
         f"      write(l, string'(\" \")); write(l, to_hstring(s_{p['nombre']}));")
        for i, p in enumerate(sal))
    tb = f"""\
-- Testbench generado por baseline/arnes_vhdl.py -- NO lo escribe el LLM.
-- Mismo vector de entrada que L2; la comparación con el golden model se hace
-- en Python con la misma tolerancia.
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity tb is
end entity;

architecture sim of tb is
  constant PERIODO   : time := 10 ns;   -- el periodo simulado no afecta a la latencia en ciclos
  constant N         : integer := {n};
  constant MAX_CICLOS: integer := {max_ciclos};
  signal clk      : std_logic := '0';
  signal rst      : std_logic := '1';
  signal in_we    : std_logic := '0';
  signal in_addr  : std_logic_vector({a - 1} downto 0) := (others => '0');
  signal start    : std_logic := '0';
  signal done     : std_logic;
  signal out_addr : std_logic_vector({a - 1} downto 0) := (others => '0');
{decl}
  signal fin      : boolean := false;
begin
  clk <= not clk after PERIODO / 2 when not fin else clk;

  dut : entity work.{top}
    port map (
{mapa}
    );

  estimulo : process
    file f_in  : text open read_mode  is "vectores_in.txt";
    file f_out : text open write_mode is "salida.txt";
    variable l   : line;
    variable v   : std_logic_vector(31 downto 0);
    variable ciclos : integer := 0;
  begin
    -- reset síncrono
    rst <= '1';
    for k in 1 to 5 loop wait until rising_edge(clk); end loop;
    rst <= '0';
    wait until rising_edge(clk);

    -- carga de la entrada, una muestra por ciclo
    for i in 0 to N - 1 loop
      readline(f_in, l);
{lee_cols}
      in_addr <= std_logic_vector(to_unsigned(i, in_addr'length));
      in_we   <= '1';
      wait until rising_edge(clk);
    end loop;
    in_we <= '0';
    wait until rising_edge(clk);

    -- start de un ciclo y medida de la latencia hasta done
    start <= '1';
    wait until rising_edge(clk);
    start <= '0';
    ciclos := 1;
    loop
      wait until rising_edge(clk);
      ciclos := ciclos + 1;
      exit when done = '1';
      if ciclos >= MAX_CICLOS then
        report "{MARCA_NO_TERMINA} " & integer'image(ciclos) severity note;
        fin <= true;
        wait;
      end if;
    end loop;
    report "{MARCA_LAT} " & integer'image(ciclos) severity note;

    -- lectura de la salida (latencia de lectura 1)
    for i in 0 to N - 1 loop
      out_addr <= std_logic_vector(to_unsigned(i, out_addr'length));
      wait until rising_edge(clk);
      wait for 1 ns;
{escr_cols}
      writeline(f_out, l);
    end loop;
    report "{MARCA_SIM_FIN}" severity note;
    fin <= true;
    wait;
  end process;
end architecture;
"""
    ruta.write_text(tb)


# ---------------------------------------------------------------------------
# Simulación con GHDL
# ---------------------------------------------------------------------------

def _ejecutar(cmd: list[str], cwd: Path, timeout_s: int, ruta_log: Path) -> dict:
    t0 = time.monotonic()
    timeout = False
    with open(ruta_log, "a") as log:
        log.write(f"\n$ {' '.join(cmd)}\n")
        log.flush()
        proc = subprocess.Popen(cmd, cwd=cwd, stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
        try:
            proc.wait(timeout=timeout_s)
        except subprocess.TimeoutExpired:
            timeout = True
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait()
    return {"rc": proc.returncode, "timeout": timeout, "duracion_s": round(time.monotonic() - t0, 1)}


def ghdl_disponible() -> bool:
    return shutil.which("ghdl") is not None


def simular(directorio: Path, timeout_s: int) -> dict:
    """Analiza kernel.vhd, analiza y elabora tb.vhd, y ejecuta la simulación."""
    log = directorio / "ghdl.log"
    log.write_text("")
    opts = ["--std=08", "-frelaxed", "--workdir=ghdl_work"]
    (directorio / "ghdl_work").mkdir(exist_ok=True)
    r = {"analiza_kernel": False, "elabora_tb": False, "sim_timeout": False, "t_sim_s": 0.0}

    a = _ejecutar(["ghdl", "-a", *opts, "kernel.vhd"], directorio, 300, log)
    r["analiza_kernel"] = a["rc"] == 0 and not a["timeout"]
    if not r["analiza_kernel"]:
        r["log"] = log.read_text(errors="replace")
        return r
    b = _ejecutar(["ghdl", "-a", *opts, "tb.vhd"], directorio, 300, log)
    c = _ejecutar(["ghdl", "-e", *opts, "tb"], directorio, 600, log) if b["rc"] == 0 else {"rc": 1, "timeout": False}
    r["elabora_tb"] = c["rc"] == 0 and not c["timeout"]
    if not r["elabora_tb"]:
        r["log"] = log.read_text(errors="replace")
        return r
    s = _ejecutar(["ghdl", "-r", *opts, "tb", "--ieee-asserts=disable-at-0", "--max-stack-alloc=0"],
                  directorio, timeout_s, log)
    r["sim_timeout"] = s["timeout"]
    r["t_sim_s"] = s["duracion_s"]
    r["log"] = log.read_text(errors="replace")
    return r


# ---------------------------------------------------------------------------
# Síntesis con Vivado (fuera de contexto)
# ---------------------------------------------------------------------------

def vivado_disponible() -> bool:
    return shutil.which("vivado") is not None


def escribir_synth_tcl(spec: dict, part: str, periodo_ns: float, ruta: Path) -> None:
    (ruta.parent / "reloj.xdc").write_text(f"create_clock -period {periodo_ns} -name clk [get_ports clk]\n")
    tcl = f"""\
# Generado por baseline/arnes_vhdl.py. Mismo part y reloj que L4 y que el
# baseline C++. Síntesis fuera de contexto: los puertos no se asignan a pines.
if {{[catch {{
  read_vhdl -vhdl2008 kernel.vhd
  read_xdc -mode out_of_context reloj.xdc
  synth_design -top {nombre_top(spec)} -part {part} -mode out_of_context
  report_utilization -file utilizacion.rpt
  report_timing_summary -file timing.rpt
  set ruta [get_timing_paths -max_paths 1 -nworst 1 -setup]
  if {{[llength $ruta] > 0}} {{
    puts "{MARCA_WNS} [get_property SLACK $ruta]"
  }} else {{
    puts "{MARCA_WNS} NA"
  }}
}} msg]}} {{
  puts "{MARCA_SYN_ERROR}: $msg"
}} else {{
  puts "{MARCA_SYN_FIN}"
}}
exit
"""
    ruta.write_text(tcl)


def sintetizar(directorio: Path, timeout_s: int) -> dict:
    log = directorio / "vivado.log"
    log.write_text("")
    e = _ejecutar(["vivado", "-mode", "batch", "-nojournal", "-nolog", "-source", "synth.tcl"],
                  directorio, timeout_s, log)
    return {"timeout": e["timeout"], "duracion_s": e["duracion_s"], "log": log.read_text(errors="replace")}


def _num_tabla(rpt: str, etiqueta: str) -> float | None:
    m = re.search(rf"^\|\s*{etiqueta}\s*\|\s*([\d.]+)\s*\|", rpt, re.MULTILINE)
    return float(m.group(1)) if m else None


def parsear_utilizacion(ruta: Path) -> dict:
    if not ruta.exists():
        return {}
    rpt = ruta.read_text(errors="replace")
    bram_tiles = _num_tabla(rpt, r"Block RAM Tile")
    return {
        "LUT": _num_tabla(rpt, r"CLB LUTs\*?"),
        "FF": _num_tabla(rpt, r"CLB Registers"),
        "DSP": _num_tabla(rpt, r"DSPs"),
        # Vivado cuenta tiles de 36 Kb; Vitis HLS informa BRAM_18K -> x2 para comparar.
        "BRAM_18K": None if bram_tiles is None else bram_tiles * 2,
        "URAM": _num_tabla(rpt, r"URAM"),
    }


# ---------------------------------------------------------------------------
# Análisis de un intento
# ---------------------------------------------------------------------------

def analizar(spec: dict, directorio: Path, sim: dict, syn: dict | None, referencia: dict,
             tolerancia: float, periodo_obj_ns: float) -> dict:
    log_sim = sim.get("log", "")
    lat = re.search(rf"{MARCA_LAT} (\d+)", log_sim)
    no_termina = MARCA_NO_TERMINA in log_sim or sim["sim_timeout"]
    sim_completa = MARCA_SIM_FIN in log_sim
    salida = leer_salida(spec, directorio / "salida.txt") if sim_completa else None
    funcional_ok, detalle = (comparar(spec, salida, referencia, tolerancia) if salida is not None else (False, []))

    metricas, wns, sintesis_ok, timeout_syn = None, None, False, False
    if syn is not None:
        timeout_syn = syn["timeout"]
        sintesis_ok = MARCA_SYN_FIN in syn["log"] and not timeout_syn
        m = re.search(rf"{MARCA_WNS} (\S+)", syn["log"])
        try:
            wns = float(m.group(1)) if m else None
        except ValueError:
            wns = None
        metricas = parsear_utilizacion(directorio / "utilizacion.rpt") if sintesis_ok else None
        for f in ("utilizacion.rpt", "timing.rpt"):
            if (directorio / f).exists():
                (directorio / "informes_vivado").mkdir(exist_ok=True)
                shutil.copy2(directorio / f, directorio / "informes_vivado" / f)

    latencia = int(lat.group(1)) if lat else None
    periodo_est = (periodo_obj_ns - wns) if (wns is not None) else None
    cierra_timing = None if wns is None else wns >= 0
    t_fft_us = None
    if latencia is not None and funcional_ok:
        t_fft_us = latencia * max(periodo_obj_ns, periodo_est or periodo_obj_ns) / 1000

    if not sim["analiza_kernel"]:
        etapa = "compilacion"
    elif not sim["elabora_tb"]:
        etapa = "interfaz"
    elif no_termina:
        etapa = "no_termina"
    elif not funcional_ok:
        etapa = "funcional"
    elif syn is None:
        etapa = "sin_sintesis"
    elif timeout_syn:
        etapa = "timeout_sintesis"
    elif not sintesis_ok:
        etapa = "sintesis"
    else:
        etapa = None

    return {
        "compila": sim["analiza_kernel"],
        "interfaz_ok": sim["elabora_tb"],
        "sim_termina": sim_completa,
        "funcional_ok": funcional_ok,
        "sim_detalle": detalle,
        "t_sim_s": sim.get("t_sim_s"),
        "sintesis_ok": sintesis_ok,
        "timeout_sintesis": timeout_syn,
        "t_vivado_s": syn["duracion_s"] if syn else None,
        "metricas": {
            "latencia_ciclos": latencia,
            "wns_ns": wns,
            "periodo_reloj_estimado_ns": None if periodo_est is None else round(periodo_est, 3),
            "t_fft_us": None if t_fft_us is None else round(t_fft_us, 3),
            **(metricas or {}),
        },
        "cierra_timing": cierra_timing,
        "exito": funcional_ok and sintesis_ok,
        "exito_estricto": bool(funcional_ok and sintesis_ok and cierra_timing),
        "etapa_fallo": etapa,
    }
