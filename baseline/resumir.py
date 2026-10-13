"""
Agrega los runs del baseline y los pone al lado del resultado del pipeline
(results/catalogo/<bloque>_ii<N>.json) para la memoria.

Uso (desde TFG/baseline):
  python3 resumir.py
Escribe además results/baseline/resumen.md y results/baseline/runs.csv.
"""

import csv
import json
import statistics
from collections import defaultdict
from pathlib import Path

from comun import DIR_CATALOGO, DIR_RESULTADOS_BASELINE

CAMPOS_METRICAS = ["II", "latencia_peor_caso", "periodo_reloj_estimado_ns", "BRAM", "DSP", "LUT", "FF"]


def _num(v):
    try:
        return float(v)
    except (TypeError, ValueError):
        return None


def cargar_runs(dir_base: Path) -> list[dict]:
    runs = []
    for ruta in sorted(dir_base.glob("*/ii*_*/run_*/resultado.json")):
        r = json.loads(ruta.read_text())
        r["_ruta"] = str(ruta.parent.relative_to(dir_base))
        runs.append(r)
    return runs


def metricas_catalogo(bloque: str, objetivo_ii: int) -> dict | None:
    ruta = DIR_CATALOGO / f"{bloque}_ii{objetivo_ii}.json"
    if not ruta.exists():
        return None
    return json.loads(ruta.read_text()).get("metricas_hls")


def pct(n, d):
    return f"{n}/{d} ({100 * n / d:.0f}%)" if d else "-"


def resumir_grupo(runs: list[dict]) -> dict:
    n = len(runs)
    finales = [r["final"] for r in runs]
    # "alguna vez" = en cualquier intento del run (importa en modo feedback)
    def alguna(r, campo):
        return any(i.get(campo) for i in r["intentos"])

    exitos = [r for r in runs if r["exito"]]
    mejor = None
    if exitos:
        mejor = min((r["final"]["metricas_hls"] for r in exitos),
                    key=lambda m: _num(m.get("latencia_peor_caso")) or float("inf"))
    medianas = {}
    for c in CAMPOS_METRICAS:
        vals = [_num(r["final"]["metricas_hls"].get(c)) for r in exitos if r["final"]["metricas_hls"]]
        vals = [v for v in vals if v is not None]
        medianas[c] = statistics.median(vals) if vals else None

    etapas = defaultdict(int)
    for f in finales:
        etapas[f["etapa_fallo"] or "ninguna (éxito)"] += 1

    return {
        "n": n,
        "codigo": sum(bool(f.get("codigo_extraido")) for f in finales),
        "compila": sum(alguna(r, "csim_compila") for r in runs),
        "correcto": sum(alguna(r, "csim_ok") for r in runs),
        "sintetiza": sum(alguna(r, "sintesis_ok") for r in runs),
        "sintetiza_incorrecto": sum(any(i.get("sintesis_ok") and not i.get("csim_ok") for i in r["intentos"]) for r in runs),
        "cumple_ii": sum(alguna(r, "cumple_ii") for r in runs),
        "exito_y_reloj": sum(bool(r["exito"] and r["final"].get("cumple_reloj_estimado")) for r in runs),
        "exito": len(exitos),
        "intentos_medios": statistics.mean(r["n_intentos"] for r in runs),
        "intentos_medios_exito": statistics.mean(r["n_intentos"] for r in exitos) if exitos else None,
        "t_medio_s": statistics.mean(r["t_total_s"] for r in runs),
        "etapas_fallo": dict(etapas),
        "mejor": mejor,
        "medianas_exito": medianas,
    }


def fila_metricas(nombre: str, m: dict | None) -> str:
    if not m:
        return f"| {nombre} | " + " | ".join("-" for _ in CAMPOS_METRICAS) + " |"
    def fmt(v):
        x = _num(v)
        return "-" if x is None else (f"{x:g}")
    return f"| {nombre} | " + " | ".join(fmt(m.get(c)) for c in CAMPOS_METRICAS) + " |"


def main():
    runs = cargar_runs(DIR_RESULTADOS_BASELINE)
    if not runs:
        print(f"No hay runs en {DIR_RESULTADOS_BASELINE}")
        return

    grupos = defaultdict(list)
    for r in runs:
        grupos[(r["bloque"], r["objetivo_ii"], r["modo"])].append(r)

    md = ["# Baseline: Claude → HLS C++ → Vitis HLS (sin agentes)\n"]
    for (bloque, ii, modo), rs in sorted(grupos.items()):
        s = resumir_grupo(rs)
        cat = metricas_catalogo(bloque, ii)
        md += [
            f"## {bloque} · objetivo_ii={ii} · modo={modo} · {s['n']} runs\n",
            "| Etapa | Runs que la superan |", "|---|---|",
            f"| Devuelve código | {pct(s['codigo'], s['n'])} |",
            f"| Compila (csim) | {pct(s['compila'], s['n'])} |",
            f"| Funcionalmente correcto (csim vs golden) | {pct(s['correcto'], s['n'])} |",
            f"| Sintetiza (csynth) | {pct(s['sintetiza'], s['n'])} |",
            f"| Sintetiza pero es INCORRECTO | {pct(s['sintetiza_incorrecto'], s['n'])} |",
            f"| Cumple II <= {ii} | {pct(s['cumple_ii'], s['n'])} |",
            f"| **Éxito (correcto y cumple II)** | **{pct(s['exito'], s['n'])}** |",
            f"| Éxito y además reloj estimado <= objetivo | {pct(s['exito_y_reloj'], s['n'])} |",
            "",
            f"Intentos medios por run: {s['intentos_medios']:.2f}"
            + (f" (en runs con éxito: {s['intentos_medios_exito']:.2f})" if s["intentos_medios_exito"] else "")
            + f" · tiempo medio por run: {s['t_medio_s'] / 60:.1f} min",
            "",
            "Etapa de fallo del intento final: "
            + ", ".join(f"{k}={v}" for k, v in sorted(s["etapas_fallo"].items())),
            "",
            "| Diseño | " + " | ".join(CAMPOS_METRICAS) + " |",
            "|---|" + "---|" * len(CAMPOS_METRICAS),
            fila_metricas("Pipeline (catálogo)", cat),
            fila_metricas("Baseline: mejor éxito (menor latencia)", s["mejor"]),
            fila_metricas("Baseline: mediana de éxitos", s["medianas_exito"]),
            "",
        ]
        if cat is None:
            md.append(f"_No hay results/catalogo/{bloque}_ii{ii}.json para comparar._\n")

    texto = "\n".join(md)
    print(texto)
    (DIR_RESULTADOS_BASELINE / "resumen.md").write_text(texto)

    with open(DIR_RESULTADOS_BASELINE / "runs.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["ruta", "bloque", "objetivo_ii", "modo", "exito", "n_intentos", "t_total_s", "etapa_fallo",
                    "csim_compila", "csim_ok", "sintesis_ok", "cumple_ii", *CAMPOS_METRICAS])
        for r in runs:
            fin = r["final"]
            m = fin.get("metricas_hls") or {}
            w.writerow([r["_ruta"], r["bloque"], r["objetivo_ii"], r["modo"], r["exito"], r["n_intentos"],
                        r["t_total_s"], fin.get("etapa_fallo"), fin.get("csim_compila"), fin.get("csim_ok"),
                        fin.get("sintesis_ok"), fin.get("cumple_ii"), *[m.get(c) for c in CAMPOS_METRICAS]])
    print(f"\nEscrito {DIR_RESULTADOS_BASELINE / 'resumen.md'} y runs.csv")


if __name__ == "__main__":
    main()
