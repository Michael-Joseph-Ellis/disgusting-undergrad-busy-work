from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path
from typing import Dict

import numpy as np
import pandas as pd

from .constants import GRADE_ORDER


def spearman_rank(x: pd.Series, y: pd.Series) -> float:
    # Pearson correlation of ranks (SciPy-free)
    return x.rank(method="average").corr(y.rank(method="average"), method="pearson")


def build_summary(df: pd.DataFrame) -> Dict:
    n_rows, n_cols = df.shape
    unique_students = df["StudentID"].nunique()
    missing_counts = df.isna().sum()
    any_missing = bool((missing_counts > 0).any())
    rows_with_missing = int(df.isna().any(axis=1).sum())

    gpa_stats = df["GPA"].describe().to_dict()
    grade_counts = df["GradeLabel"].value_counts().reindex(GRADE_ORDER).fillna(0).astype(int)

    spearman = {
        "StudyTimeWeekly": float(spearman_rank(df["StudyTimeWeekly"], df["GPA"])),
        "Absences": float(spearman_rank(df["Absences"], df["GPA"])),
        "ParentalSupport": float(spearman_rank(df["ParentalSupport"], df["GPA"]))
    }

    med_study_by_grade = df.groupby("GradeLabel")["StudyTimeWeekly"].median().reindex(GRADE_ORDER).to_dict()
    med_abs_by_grade = df.groupby("GradeLabel")["Absences"].median().reindex(GRADE_ORDER).to_dict()

    ab_mask = df["GradeLabel"].isin(["A", "B"])
    high_support = df["ParentalSupport"] >= 3
    low_support = df["ParentalSupport"] <= 1

    prop_ab_high = float(((ab_mask) & high_support).sum() / max(1, high_support.sum()))
    prop_ab_low = float(((ab_mask) & low_support).sum() / max(1, low_support.sum()))

    return {
        "n_rows": int(n_rows),
        "n_cols": int(n_cols),
        "unique_students": int(unique_students),
        "rows_with_missing": int(rows_with_missing),
        "any_missing": any_missing,
        "gpa_stats": {k: float(v) for k, v in gpa_stats.items()},
        "grade_counts": grade_counts.to_dict(),
        "spearman_with_gpa": spearman,
        "median_study_by_grade": med_study_by_grade,
        "median_absences_by_grade": med_abs_by_grade,
        "prop_AB_high_parental_support": prop_ab_high,
        "prop_AB_low_parental_support": prop_ab_low,
    }


def write_summary(summary: Dict, out_dir: Path):
    out_dir.mkdir(parents=True, exist_ok=True)
    with open(out_dir / "eda_summary.json", "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=2)
