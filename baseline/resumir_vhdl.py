"""
Resumen del baseline VHDL y comparación con el baseline C++ y el pipeline.

Uso (desde TFG/baseline):
  python3 resumir_vhdl.py                 # fft_radix2 por defecto
  python3 resumir_vhdl.py --bloque fft_radix4

Escribe en results/baseline/:
  comparativa_<bloque>_vhdl.md        tablas para la memoria
  comparativa_<bloque>_vhdl_runs.csv  una fila por run

Definiciones:
  - Éxito: compila, respeta la entidad, la simulación termina, la salida
    coincide con el golden (|diff| < tol, mismo vector que L2) y la síntesis
    de Vivado termina. En RTL no hay II: no forma parte del criterio.
  - Éxito estricto: además cierra timing (WNS >= 0 al periodo objetivo).
  - t_FFT = latencia simulada (ciclos desde start hasta done) x
    max(periodo objetivo, periodo estimado). No incluye la carga ni la
    lectura (1024 ciclos cada una), que en el diseño HLS sí forman parte de
    la latencia del top: es una asimetría a declarar.
"""

import argparse
import csv
import json
import statistics
from pathlib import Path

from comun import DIR_CATALOGO, DIR_RESULTADOS_BASELINE, PERIODO_RELOJ_NS_POR_DEFECTO

ETAPAS = ["sin_codigo", "compilacion", "interfaz", "no_termina", "funcional", "sintesis",
          "timeout_sintesis", "sin_sintesis"]


def wilson(k, n, z=1.96):
    if n == 0:
        return 0.0, 0.0
    p = k / n
    den = 1 + z * z / n
    c = (p + z * z / (2 * n)) / den
    s = z * ((p * (1 - p) / n + z * z / (4 * n * n)) ** 0.5) / den
    return max(0.0, c - s), min(1.0, c + s)


def pct(k, n):
    lo, hi = wilson(k, n)
    return f"{k}/{n} ({100 * k / n:.0f} %; IC95 {100 * lo:.0f}–{100 * hi:.0f} %)" if n else "—"


def med(xs):
    xs = [x for x in xs if x is not None]
    if not xs:
        return "—"
    q = statistics.quantiles(xs, n=4) if len(xs) > 1 else [xs[0]] * 3
    fmt = lambda x: f"{x:,.0f}".replace(",", " ") if abs(x) >= 100 else f"{x:.3g}"  # noqa: E731
    return f"{fmt(statistics.median(xs))} [{fmt(q[0])}–{fmt(q[2])}]"


def cargar_runs(dir_cfg: Path) -> list[dict]:
    filas = []
    for f in sorted(dir_cfg.glob("run_*/resultado.json")):
        if "descartado" in f.parent.name:
            continue
        r = json.loads(f.read_text())
        fin, m = r["final"], r["final"].get("metricas") or {}
        filas.append({
            "run": f.parent.name, "etapa_fallo": fin.get("etapa_fallo") or "",
            "compila": fin.get("compila"), "interfaz_ok": fin.get("interfaz_ok"),
            "sim_termina": fin.get("sim_termina"), "funcional_ok": fin.get("funcional_ok"),
            "sintesis_ok": fin.get("sintesis_ok"), "cierra_timing": fin.get("cierra_timing"),
            "exito": fin.get("exito"), "exito_estricto": fin.get("exito_estricto"),
            "latencia": m.get("latencia_ciclos"), "periodo_est_ns": m.get("periodo_reloj_estimado_ns"),
            "wns_ns": m.get("wns_ns"), "t_fft_us": m.get("t_fft_us"), "LUT": m.get("LUT"), "FF": m.get("FF"),
            "DSP": m.get("DSP"), "BRAM_18K": m.get("BRAM_18K"), "URAM": m.get("URAM"),
            "t_generacion_s": fin.get("t_generacion_s"), "t_total_s": r.get("t_total_s"),
        })
    return filas


def referencia_cpp(bloque: str) -> list[dict]:
    ruta = DIR_RESULTADOS_BASELINE / f"comparativa_{bloque}_oneshot_runs.csv"
    if not ruta.exists():
        return []
    return list(csv.DictReader(open(ruta)))


def referencia_pipeline(bloque: str) -> list[dict]:
    out = []
    for f in sorted(DIR_CATALOGO.glob(f"{bloque}_ii*.json")):
        m = json.loads(f.read_text()).get("metricas_hls") or {}
        try:
            lat = float(m["latencia_peor_caso"])
            per = max(PERIODO_RELOJ_NS_POR_DEFECTO, float(m["periodo_reloj_estimado_ns"]))
        except (KeyError, TypeError, ValueError):
            continue
        out.append({"diseño": f.stem, "II": m.get("II"), "latencia": lat, "t_fft_us": lat * per / 1000,
                    "LUT": m.get("LUT"), "FF": m.get("FF"), "DSP": m.get("DSP"), "BRAM": m.get("BRAM")})
    return out


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--bloque", default="fft_radix2")
    p.add_argument("--salida", type=Path, default=DIR_RESULTADOS_BASELINE)
    args = p.parse_args()

    dir_cfg = args.salida / args.bloque / "vhdl_oneshot"
    runs = cargar_runs(dir_cfg)
    if not runs:
        raise SystemExit(f"No hay runs en {dir_cfg}")
    n = len(runs)
    cuenta = lambda clave: sum(1 for r in runs if r[clave])  # noqa: E731
    exitos = [r for r in runs if r["exito"]]
    correctos = [r for r in runs if r["funcional_ok"]]

    md = [f"# Baseline VHDL — {args.bloque} (oneshot)\n",
          f"Claude escribe VHDL directamente, sin agentes y en un solo intento; {n} runs independientes. "
          "Simulación con GHDL contra el mismo golden, vector y tolerancia que L2; síntesis fuera de contexto con "
          "Vivado, mismo dispositivo y reloj (3.33 ns).\n",
          "## 1. Embudo\n", "| Etapa | Runs |", "|---|---|",
          f"| Compila (GHDL) | {pct(cuenta('compila'), n)} |",
          f"| Respeta la entidad pedida | {pct(cuenta('interfaz_ok'), n)} |",
          f"| La simulación termina (levanta done) | {pct(cuenta('sim_termina'), n)} |",
          f"| **Funcionalmente correcto** | **{pct(cuenta('funcional_ok'), n)}** |",
          f"| Síntesis termina | {pct(cuenta('sintesis_ok'), n)} |",
          f"| **Éxito (correcto + sintetiza)** | **{pct(len(exitos), n)}** |",
          f"| Éxito estricto (+ cierra timing) | {pct(cuenta('exito_estricto'), n)} |", "",
          "Etapa de fallo del intento: " + ", ".join(
              f"{e}={sum(1 for r in runs if r['etapa_fallo'] == e)}" for e in ETAPAS
              if any(r["etapa_fallo"] == e for r in runs)) + "\n"]

    md += ["## 2. Calidad de los diseños con éxito\n",
           f"Mediana [P25–P75] sobre n={len(exitos)} éxitos (latencia y t_FFT: sobre los {len(correctos)} correctos).\n",
           "| Métrica | Valor |", "|---|---|",
           f"| Latencia start→done (ciclos) | {med([r['latencia'] for r in correctos])} |",
           f"| Periodo estimado (ns) | {med([r['periodo_est_ns'] for r in exitos])} |",
           f"| t_FFT (µs) | {med([r['t_fft_us'] for r in correctos])} |",
           f"| LUT | {med([r['LUT'] for r in exitos])} |", f"| FF | {med([r['FF'] for r in exitos])} |",
           f"| DSP | {med([r['DSP'] for r in exitos])} |", f"| BRAM_18K | {med([r['BRAM_18K'] for r in exitos])} |",
           f"| Cierra timing | {sum(1 for r in exitos if r['cierra_timing'])}/{len(exitos)} |", ""]
    mejor = min((r for r in exitos if r["t_fft_us"] is not None), key=lambda r: r["t_fft_us"], default=None)
    if mejor:
        md.append(f"Mejor run ({mejor['run']}): latencia={mejor['latencia']}, t_FFT={mejor['t_fft_us']} µs, "
                  f"LUT={mejor['LUT']}, FF={mejor['FF']}, DSP={mejor['DSP']}, BRAM_18K={mejor['BRAM_18K']}, "
                  f"WNS={mejor['wns_ns']} ns\n")

    md += ["## 3. Comparación con C++ directo y con el pipeline\n",
           "| Aproximación | Éxito | t_FFT mejor (µs) | t_FFT mediana éxitos (µs) | LUT mediana éxitos |", "|---|---|---|---|---|"]
    cpp = referencia_cpp(args.bloque)
    for ii in sorted({r["objetivo_ii"] for r in cpp}, key=int, reverse=True):
        rs = [r for r in cpp if r["objetivo_ii"] == ii]
        ok = [r for r in rs if r["exito_l4"] == "True"]
        tf = [float(r["t_fft_us"]) for r in ok if r["t_fft_us"]]
        md.append(f"| C++ directo, II ≤ {ii} | {len(ok)}/{len(rs)} | {min(tf):.1f} | {statistics.median(tf):.1f} | "
                  f"{statistics.median(float(r['LUT']) for r in ok):.0f} |" if ok else f"| C++ directo, II ≤ {ii} | 0/{len(rs)} | — | — | — |")
    tf_v = [r["t_fft_us"] for r in exitos if r["t_fft_us"] is not None]
    lut_v = [r["LUT"] for r in exitos if r["LUT"] is not None]
    md.append(f"| **VHDL directo** | {len(exitos)}/{n} | {min(tf_v):.1f} | {statistics.median(tf_v):.1f} | "
              f"{statistics.median(lut_v):.0f} |" if tf_v and lut_v else f"| **VHDL directo** | {len(exitos)}/{n} | — | — | — |")
    for d in referencia_pipeline(args.bloque):
        md.append(f"| Pipeline Allo ({d['diseño']}) | convergió | {d['t_fft_us']:.1f} | — | {d['LUT']} |")
    md += ["", "## Advertencias\n",
           "- La latencia VHDL va de start a done y no incluye la carga ni la lectura de los 1024 datos; la latencia "
           "de los diseños HLS (C++ y Allo) incluye la lectura y escritura de los arrays de la interfaz.",
           "- Los recursos VHDL son de synth_design (Vivado); los de HLS son estimaciones de csynth. Ambos antes de "
           "place & route, pero no son la misma estimación.",
           "- BRAM_18K VHDL = 2 x Block RAM Tile (36 Kb) de Vivado, para compararlo con el BRAM_18K de Vitis HLS."]

    (args.salida / f"comparativa_{args.bloque}_vhdl.md").write_text("\n".join(md) + "\n")
    with open(args.salida / f"comparativa_{args.bloque}_vhdl_runs.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(runs[0]))
        w.writeheader()
        w.writerows(runs)
    print("\n".join(md))


if __name__ == "__main__":
    main()
