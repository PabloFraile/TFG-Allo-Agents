"""
Tablas comparativas baseline (Claude -> HLS C++ -> Vitis, sin agentes) vs
pipeline (results/catalogo), con estadística sobre los N runs de cada
objetivo. Pensado para la memoria: todo sale de los resultado.json y del
catálogo, sin números a mano.

Uso (desde TFG/baseline):
  python3 comparativa.py                 # todos los bloques/modos que haya
  python3 comparativa.py --bloque fft_radix2 --modo oneshot

Escribe en results/baseline/:
  comparativa_<bloque>_<modo>.md         tablas listas para la memoria
  comparativa_<bloque>_<modo>_runs.csv   una fila por run (con t_FFT calculado)
  comparativa_<bloque>_<modo>_resumen.csv una fila por objetivo (baseline) + pipeline
  comparativa_<bloque>_<modo>.png        latencia vs área (si hay matplotlib)

Definiciones (también se imprimen al final del .md):
  - Éxito (criterio L4): csim correcta + síntesis terminada + II <= objetivo.
    Es el mismo criterio con el que el pipeline da un kernel por bueno.
  - Éxito estricto: lo anterior + reloj estimado <= periodo objetivo + latencia
    acotada (Vitis la puede calcular).
  - t_FFT = latencia_peor_caso x max(periodo objetivo, reloj estimado). Si el
    diseño no cierra timing, se usa el reloj estimado (más lento); si lo
    cierra, el diseño corre al reloj objetivo, no al estimado.
  - IC 95 %: intervalo de Wilson para una proporción.
  - pass@k: probabilidad de que al menos uno de k intentos independientes
    tenga éxito, con el estimador insesgado de Chen et al. (2021).
"""

import argparse
import csv
import json
import math
import statistics
from collections import Counter, defaultdict
from pathlib import Path

from comun import DIR_CATALOGO, DIR_RESULTADOS_BASELINE, PERIODO_RELOJ_NS_POR_DEFECTO

RECURSOS = ["LUT", "FF", "DSP", "BRAM"]


# ---------------------------------------------------------------------------
# Utilidades numéricas
# ---------------------------------------------------------------------------

def num(v):
    try:
        x = float(v)
        return x if math.isfinite(x) else None
    except (TypeError, ValueError):
        return None


def wilson(k: int, n: int, z: float = 1.96) -> tuple[float, float]:
    if n == 0:
        return (float("nan"), float("nan"))
    p = k / n
    den = 1 + z * z / n
    centro = (p + z * z / (2 * n)) / den
    semi = z * math.sqrt(p * (1 - p) / n + z * z / (4 * n * n)) / den
    return max(0.0, centro - semi), min(1.0, centro + semi)


def pass_at_k(n: int, c: int, k: int) -> float:
    if n - c < k:
        return 1.0
    return 1.0 - math.comb(n - c, k) / math.comb(n, k)


def cuartiles(vals: list[float]):
    vals = sorted(vals)
    if not vals:
        return None
    if len(vals) == 1:
        return vals[0], vals[0], vals[0]
    q = statistics.quantiles(vals, n=4, method="inclusive")
    return q[0], statistics.median(vals), q[2]


def fmt(x, dec=0):
    if x is None:
        return "–"
    if isinstance(x, float) and not math.isfinite(x):
        return "–"
    return f"{x:,.{dec}f}".replace(",", " ") if dec == 0 else f"{x:.{dec}f}"


def fmt_pct(k, n):
    lo, hi = wilson(k, n)
    return f"{k}/{n} ({100 * k / n:.0f} %; IC95 {100 * lo:.0f}–{100 * hi:.0f} %)"


def fmt_mediana_iqr(vals, dec=0):
    q = cuartiles([v for v in vals if v is not None])
    if q is None:
        return "–"
    return f"{fmt(q[1], dec)} [{fmt(q[0], dec)}–{fmt(q[2], dec)}]"


# ---------------------------------------------------------------------------
# Carga
# ---------------------------------------------------------------------------

def t_fft_us(lat, clk_est, periodo_obj):
    if lat is None or clk_est is None:
        return None
    return lat * max(periodo_obj, clk_est) / 1000.0


def cargar_config(dir_config: Path) -> list[dict]:
    cfg = json.loads((dir_config / "config.json").read_text())
    periodo = cfg.get("periodo_reloj_ns", PERIODO_RELOJ_NS_POR_DEFECTO)
    filas = []
    for ruta in sorted(dir_config.glob("run_*/resultado.json")):
        if "descartado" in ruta.parent.name:
            continue
        r = json.loads(ruta.read_text())
        f = r["final"]
        m = f.get("metricas_hls") or {}
        obj = r["objetivo_ii"]
        ii = num(m.get("II"))
        lat = num(m.get("latencia_peor_caso"))
        clk = num(m.get("periodo_reloj_estimado_ns"))
        exito_l4 = bool(f.get("csim_ok") and f.get("sintesis_ok") and ii is not None and ii <= obj)
        cierra_timing = clk is not None and clk <= periodo
        uso = (f.get("uso_sdk") or {}).get("usage") or {}
        filas.append({
            "run": ruta.parent.name,
            "objetivo_ii": obj,
            "periodo_obj_ns": periodo,
            "csim_ok": bool(f.get("csim_ok")),
            "sintesis_ok": bool(f.get("sintesis_ok")),
            "timeout": f.get("etapa_fallo") == "timeout_sintesis",
            "etapa_fallo": f.get("etapa_fallo") or "",
            "II": ii,
            "latencia": lat,
            "latencia_acotada": lat is not None,
            "clk_est_ns": clk,
            "cierra_timing": cierra_timing,
            "t_fft_us": t_fft_us(lat, clk, periodo),
            **{k: num(m.get(k)) for k in RECURSOS},
            "n_bucles_pipelineados": m.get("n_bucles_pipelineados"),
            "exito_l4": exito_l4,
            "exito_estricto": exito_l4 and cierra_timing and lat is not None,
            "t_generacion_s": num(f.get("t_generacion_s")),
            "t_vitis_s": num(f.get("t_vitis_s")),
            "t_total_s": num(r.get("t_total_s")),
            "tokens_salida": uso.get("output_tokens"),
        })
    return filas


def cargar_pipeline(bloque: str, objetivo: int, periodo: float) -> dict | None:
    ruta = DIR_CATALOGO / f"{bloque}_ii{objetivo}.json"
    if not ruta.exists():
        return None
    m = json.loads(ruta.read_text()).get("metricas_hls") or {}
    lat, clk = num(m.get("latencia_peor_caso")), num(m.get("periodo_reloj_estimado_ns"))
    return {
        "fuente": ruta.name,
        "II": num(m.get("II")),
        "latencia": lat,
        "clk_est_ns": clk,
        "cierra_timing": clk is not None and clk <= periodo,
        "t_fft_us": t_fft_us(lat, clk, periodo),
        **{k: num(m.get(k)) for k in RECURSOS},
    }


# ---------------------------------------------------------------------------
# Estadística por objetivo
# ---------------------------------------------------------------------------

def resumir(filas: list[dict]) -> dict:
    n = len(filas)
    exitos = [f for f in filas if f["exito_l4"]]
    sintetizados = [f for f in filas if f["sintesis_ok"]]
    c_l4, c_est = len(exitos), sum(f["exito_estricto"] for f in filas)
    t_total = sum(f["t_total_s"] or 0 for f in filas)

    disenos = Counter((f["II"], f["clk_est_ns"]) for f in sintetizados)
    (ii_mod, clk_mod), n_mod = disenos.most_common(1)[0] if disenos else ((None, None), 0)

    mejor = min((f for f in exitos if f["t_fft_us"] is not None), key=lambda f: f["t_fft_us"], default=None)
    return {
        "n": n,
        "csim_ok": sum(f["csim_ok"] for f in filas),
        "sintesis_ok": len(sintetizados),
        "timeouts": sum(f["timeout"] for f in filas),
        "cumple_ii": c_l4,
        "exito_l4": c_l4,
        "exito_estricto": c_est,
        "sin_timing": sum(not f["cierra_timing"] for f in sintetizados),
        "lat_no_acotada": sum(not f["latencia_acotada"] for f in sintetizados),
        "pass@1": pass_at_k(n, c_l4, 1),
        "pass@3": pass_at_k(n, c_l4, 3),
        "pass@5": pass_at_k(n, c_l4, 5),
        "pass@1_estricto": pass_at_k(n, c_est, 1),
        "pass@5_estricto": pass_at_k(n, c_est, 5),
        "diseno_modal": (ii_mod, clk_mod, n_mod),
        "exitos": exitos,
        "sintetizados": sintetizados,
        "mejor": mejor,
        "t_total_s": t_total,
        "t_por_exito_min": (t_total / c_l4 / 60) if c_l4 else None,
        "t_por_exito_estricto_min": (t_total / c_est / 60) if c_est else None,
        "t_run_mediana_min": statistics.median(f["t_total_s"] / 60 for f in filas if f["t_total_s"]),
        "t_gen_mediana_s": statistics.median(f["t_generacion_s"] for f in filas if f["t_generacion_s"]),
        "tokens_mediana": statistics.median(f["tokens_salida"] for f in filas if f["tokens_salida"]),
    }


# ---------------------------------------------------------------------------
# Markdown
# ---------------------------------------------------------------------------

def tabla(cabecera: list[str], filas: list[list[str]]) -> list[str]:
    out = ["| " + " | ".join(cabecera) + " |", "|" + "---|" * len(cabecera)]
    out += ["| " + " | ".join(f) + " |" for f in filas]
    return out + [""]


def generar_md(bloque, modo, objetivos, res, pipe, periodo) -> str:
    cols = [f"II ≤ {o}" for o in objetivos]
    L = [f"# Baseline vs pipeline — {bloque} ({modo})", "",
         f"Baseline: Claude escribe HLS C++ directamente, sin agentes; {res[objetivos[0]]['n']} runs "
         f"independientes por objetivo. Pipeline: el kernel de `results/catalogo/` para ese objetivo. "
         f"Dispositivo y reloj objetivo idénticos ({periodo} ns).", ""]

    # 1. Embudo
    L += ["## 1. Fiabilidad del baseline (embudo por etapas)", ""]
    filas = [
        ["Funcionalmente correcto (csim vs golden)"] + [fmt_pct(res[o]["csim_ok"], res[o]["n"]) for o in objetivos],
        ["Síntesis termina (< 30 min)"] + [fmt_pct(res[o]["sintesis_ok"], res[o]["n"]) for o in objetivos],
        ["**Éxito (criterio L4: correcto + II ≤ objetivo)**"] + [f"**{fmt_pct(res[o]['exito_l4'], res[o]['n'])}**" for o in objetivos],
        ["Éxito estricto (+ cierra timing + latencia acotada)"] + [fmt_pct(res[o]["exito_estricto"], res[o]["n"]) for o in objetivos],
        ["Timeout de síntesis"] + [fmt_pct(res[o]["timeouts"], res[o]["n"]) for o in objetivos],
        ["Sintetizados que NO cierran timing"] + [f"{res[o]['sin_timing']}/{res[o]['sintesis_ok']}" for o in objetivos],
        ["Sintetizados con latencia no acotada"] + [f"{res[o]['lat_no_acotada']}/{res[o]['sintesis_ok']}" for o in objetivos],
        ["Diseño más repetido (II, reloj est.) y frecuencia"] + [
            f"II={fmt(res[o]['diseno_modal'][0])}, {fmt(res[o]['diseno_modal'][1], 3)} ns: "
            f"{res[o]['diseno_modal'][2]}/{res[o]['n']}" for o in objetivos],
    ]
    L += tabla(["Etapa"] + cols, filas)

    # 2. Calidad de resultados
    L += ["## 2. Calidad del diseño (QoR): pipeline vs baseline", "",
          "Baseline: mediana [P25–P75] sobre los runs con éxito (criterio L4), y el mejor de ellos "
          "(menor t_FFT). t_FFT en µs; ver definición al final.", ""]
    for o in objetivos:
        r, p = res[o], pipe.get(o)
        ex = r["exitos"]
        m = r["mejor"]
        filas = []
        def fila(nombre, clave, dec=0):
            filas.append([nombre,
                          fmt(p[clave], dec) if p else "–",
                          fmt_mediana_iqr([f[clave] for f in ex], dec),
                          fmt(m[clave], dec) if m else "–"])
        fila("II (peor bucle)", "II")
        fila("Latencia (ciclos)", "latencia")
        fila("Reloj estimado (ns)", "clk_est_ns", 3)
        fila("**t_FFT (µs)**", "t_fft_us", 1)
        for k in RECURSOS:
            fila(k, k)
        filas.append(["Cierra timing (≤ %.2f ns)" % periodo,
                      ("sí" if p["cierra_timing"] else "no") if p else "–",
                      f"{sum(f['cierra_timing'] for f in ex)}/{len(ex)} éxitos", ("sí" if m and m["cierra_timing"] else "no") if m else "–"])
        L += [f"### Objetivo II ≤ {o}", ""]
        L += tabla(["Métrica", "Pipeline (catálogo)", f"Baseline, mediana [IQR] (n={len(ex)})", "Baseline, mejor run"], filas)

    # 3. ¿Responde al objetivo?
    L += ["## 3. ¿El objetivo de II guía al baseline?", "",
          "Si el objetivo condujera el diseño, la latencia debería bajar al endurecerlo. Se miran TODOS "
          "los diseños sintetizados (no solo los éxitos).", ""]
    filas = [
        ["Latencia, mediana [IQR] (ciclos)"] + [fmt_mediana_iqr([f["latencia"] for f in res[o]["sintetizados"]]) for o in objetivos],
        ["t_FFT, mediana [IQR] (µs)"] + [fmt_mediana_iqr([f["t_fft_us"] for f in res[o]["sintetizados"]], 1) for o in objetivos],
        ["Pipeline: latencia (ciclos)"] + [fmt(pipe[o]["latencia"]) if pipe.get(o) else "–" for o in objetivos],
        ["Pipeline: t_FFT (µs)"] + [fmt(pipe[o]["t_fft_us"], 1) if pipe.get(o) else "–" for o in objetivos],
    ]
    L += tabla(["Métrica"] + cols, filas)

    # 4. Coste
    L += ["## 4. Coste del baseline", ""]
    filas = [
        ["pass@1 / pass@3 / pass@5 (criterio L4)"] + [
            f"{res[o]['pass@1']:.2f} / {res[o]['pass@3']:.2f} / {res[o]['pass@5']:.2f}" for o in objetivos],
        ["pass@1 / pass@5 (estricto)"] + [f"{res[o]['pass@1_estricto']:.2f} / {res[o]['pass@5_estricto']:.2f}" for o in objetivos],
        ["Tiempo por run, mediana (min)"] + [fmt(res[o]["t_run_mediana_min"], 1) for o in objetivos],
        ["Tiempo total de los runs (h)"] + [fmt(res[o]["t_total_s"] / 3600, 1) for o in objetivos],
        ["Tiempo esperado por éxito L4 (min)"] + [fmt(res[o]["t_por_exito_min"], 1) for o in objetivos],
        ["Tiempo esperado por éxito estricto (min)"] + [fmt(res[o]["t_por_exito_estricto_min"], 1) for o in objetivos],
        ["Generación LLM, mediana (s)"] + [fmt(res[o]["t_gen_mediana_s"]) for o in objetivos],
        ["Tokens de salida, mediana"] + [fmt(res[o]["tokens_mediana"]) for o in objetivos],
    ]
    L += tabla(["Métrica"] + cols, filas)

    L += ["## Definiciones y advertencias", "",
          "- **Éxito (criterio L4)**: csim correcta contra el mismo golden y vector que L2 (|diff| < 1e-3) "
          "+ síntesis terminada en < 30 min + peor PipelineII ≤ objetivo. Es el criterio con el que el pipeline "
          "acepta un kernel.",
          "- **Éxito estricto**: además, reloj estimado ≤ periodo objetivo y latencia acotada por Vitis.",
          f"- **t_FFT** = latencia × max({periodo} ns, reloj estimado). Estimaciones de csynth, antes de "
          "place & route.",
          "- El **II** solo es el del peor bucle pipelineado: un diseño con II bajo pero bucles secuenciales "
          "puede ser lento. Por eso se compara sobre todo t_FFT y área.",
          "- **IC95**: Wilson. **pass@k**: estimador insesgado de Chen et al. (2021) sobre los n runs.",
          "- **Asimetría a declarar**: el pipeline aporta UN diseño convergido por objetivo (catálogo); su "
          "tasa de éxito y su coste por ejecución no están medidos con la misma n que el baseline.",
          ""]
    return "\n".join(L)


# ---------------------------------------------------------------------------
# Figura
# ---------------------------------------------------------------------------

def figura(bloque, modo, objetivos, res, pipe, ruta_png: Path) -> bool:
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        return False

    # Paleta categórica validada (orden fijo); forma de marcador como
    # codificación secundaria para que el color no sea el único canal.
    colores = ["#2a78d6", "#eb6834", "#1baf7a"]
    marcadores = ["o", "s", "^"]
    tinta, tinta2, rejilla = "#1f1f1e", "#5f5e5a", "#e6e5e0"

    fig, ax = plt.subplots(figsize=(7.2, 4.6), dpi=200)
    for i, o in enumerate(objetivos):
        c, mk = colores[i % len(colores)], marcadores[i % len(marcadores)]
        pts = [f for f in res[o]["sintetizados"] if f["t_fft_us"] and f["LUT"]]
        ok = [f for f in pts if f["exito_l4"]]
        ko = [f for f in pts if not f["exito_l4"]]
        ax.scatter([f["LUT"] for f in ok], [f["t_fft_us"] for f in ok], s=34, marker=mk, color=c,
                   edgecolors="white", linewidths=0.8, label=f"Baseline II ≤ {o} (éxito)", zorder=3)
        ax.scatter([f["LUT"] for f in ko], [f["t_fft_us"] for f in ko], s=34, marker=mk, facecolors="none",
                   edgecolors=c, linewidths=1.2, label=f"Baseline II ≤ {o} (no cumple II)", zorder=3)
        p = pipe.get(o)
        if p and p["t_fft_us"] and p["LUT"]:
            ax.scatter([p["LUT"]], [p["t_fft_us"]], s=150, marker="*", color=c, edgecolors=tinta,
                       linewidths=0.9, zorder=4)
            ax.annotate(f"pipeline II={fmt(p['II'])}", (p["LUT"], p["t_fft_us"]), xytext=(6, 4),
                        textcoords="offset points", fontsize=7.5, color=tinta)
    ax.scatter([], [], s=150, marker="*", color="white", edgecolors=tinta, label="Pipeline (catálogo)")

    # El diseño más repetido se apila en un único punto: se rotula con su
    # recuento para que no parezca uno solo.
    todos = [f for o in objetivos for f in res[o]["sintetizados"] if f["t_fft_us"] and f["LUT"]]
    if todos:
        (ii_m, clk_m), n_m = Counter((f["II"], f["clk_est_ns"]) for f in todos).most_common(1)[0]
        grupo = [f for f in todos if (f["II"], f["clk_est_ns"]) == (ii_m, clk_m)]
        if n_m >= 3:
            x = statistics.median(f["LUT"] for f in grupo)
            y = statistics.median(f["t_fft_us"] for f in grupo)
            ax.annotate(f"{n_m} runs apilados aquí\n(mismo diseño: II={fmt(ii_m)}, {fmt(clk_m, 3)} ns)",
                        (x, y), xytext=(14, -38), textcoords="offset points", fontsize=7.5, color=tinta,
                        arrowprops=dict(arrowstyle="-", color=tinta2, linewidth=0.7))

    ax.set_xscale("log")
    ax.set_xlabel("LUT (escala log)", color=tinta2, fontsize=9)
    ax.set_ylabel("t_FFT (µs)  ·  menos es mejor", color=tinta2, fontsize=9)
    ax.set_title(f"{bloque}: tiempo por FFT vs área — baseline ({modo}) y pipeline", color=tinta,
                 fontsize=10, loc="left")
    ax.grid(True, color=rejilla, linewidth=0.6)
    ax.set_axisbelow(True)
    for s in ("top", "right"):
        ax.spines[s].set_visible(False)
    for s in ("left", "bottom"):
        ax.spines[s].set_color(rejilla)
    ax.tick_params(colors=tinta2, labelsize=8)
    ax.set_ylim(bottom=0)
    ax.legend(fontsize=7, frameon=False, loc="upper left", bbox_to_anchor=(1.01, 1))
    nota = "Solo diseños sintetizados con latencia acotada; los timeouts no aparecen."
    fig.text(0.01, 0.01, nota, fontsize=7, color=tinta2)
    fig.tight_layout(rect=(0, 0.03, 1, 1))
    fig.savefig(ruta_png, facecolor="white")
    plt.close(fig)
    return True


# ---------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--bloque", default=None)
    ap.add_argument("--modo", default=None)
    ap.add_argument("--salida", type=Path, default=DIR_RESULTADOS_BASELINE)
    args = ap.parse_args()

    grupos = defaultdict(dict)
    for dir_config in sorted(DIR_RESULTADOS_BASELINE.glob("*/ii*_*")):
        if not (dir_config / "config.json").exists():
            continue
        bloque = dir_config.parent.name
        obj_txt, modo = dir_config.name.split("_", 1)
        if (args.bloque and bloque != args.bloque) or (args.modo and modo != args.modo):
            continue
        filas = cargar_config(dir_config)
        if filas:
            grupos[(bloque, modo)][int(obj_txt[2:])] = filas

    if not grupos:
        print(f"No hay runs en {DIR_RESULTADOS_BASELINE}")
        return

    for (bloque, modo), por_obj in grupos.items():
        objetivos = sorted(por_obj, reverse=True)
        periodo = por_obj[objetivos[0]][0]["periodo_obj_ns"]
        res = {o: resumir(por_obj[o]) for o in objetivos}
        pipe = {o: cargar_pipeline(bloque, o, periodo) for o in objetivos}
        base = args.salida / f"comparativa_{bloque}_{modo}"

        md = generar_md(bloque, modo, objetivos, res, pipe, periodo)
        base.with_suffix(".md").write_text(md)

        campos = list(por_obj[objetivos[0]][0].keys())
        with open(f"{base}_runs.csv", "w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=campos)
            w.writeheader()
            for o in objetivos:
                w.writerows(por_obj[o])

        with open(f"{base}_resumen.csv", "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["fuente", "objetivo_ii", "n", "exito_l4", "ic95_lo", "ic95_hi", "exito_estricto",
                        "timeouts", "II_mediana", "lat_mediana", "clk_mediana", "t_fft_us_mediana",
                        "t_fft_us_mejor", *[f"{k}_mediana" for k in RECURSOS], "t_por_exito_min"])
            for o in objetivos:
                r = res[o]
                lo, hi = wilson(r["exito_l4"], r["n"])
                med = lambda c: (cuartiles([x[c] for x in r["exitos"] if x[c] is not None]) or (None,) * 3)[1]
                w.writerow(["baseline", o, r["n"], r["exito_l4"], round(lo, 3), round(hi, 3), r["exito_estricto"],
                            r["timeouts"], med("II"), med("latencia"), med("clk_est_ns"), med("t_fft_us"),
                            r["mejor"]["t_fft_us"] if r["mejor"] else None, *[med(k) for k in RECURSOS],
                            r["t_por_exito_min"]])
                p = pipe[o]
                if p:
                    w.writerow(["pipeline", o, 1, "", "", "", "", "", p["II"], p["latencia"], p["clk_est_ns"],
                                p["t_fft_us"], p["t_fft_us"], *[p[k] for k in RECURSOS], ""])

        hay_fig = figura(bloque, modo, objetivos, res, pipe, base.with_suffix(".png"))
        print(md)
        print(f"Escrito: {base}.md, {base}_runs.csv, {base}_resumen.csv"
              + (f", {base}.png" if hay_fig else " (sin figura: falta matplotlib)"))


if __name__ == "__main__":
    main()
