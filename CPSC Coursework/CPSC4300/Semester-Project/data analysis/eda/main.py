from __future__ import annotations

import pandas as pd

from .constants import GRADE_ORDER
from .loader import load_dataset
from .paths import figures_dir
from .plots import (
    plot_box_by_grade,
    plot_corr_heatmap,
    plot_gpa_hist,
    plot_grade_distribution,
    plot_parental_support_stacked,
)
from .stats import build_summary, write_summary


def run_eda():
    df = load_dataset()
    out_dir = figures_dir()

    # Plots
    plot_grade_distribution(df, out_dir / "gradeclass_distribution.png")
    plot_gpa_hist(df, out_dir / "gpa_histogram.png")
    plot_box_by_grade(df, "StudyTimeWeekly", "Weekly study time by grade class", "Study time (hours/week)", out_dir / "studytime_by_gradeclass.png")
    plot_box_by_grade(df, "Absences", "Absences by grade class", "Absences (count)", out_dir / "absences_by_gradeclass.png")
    plot_parental_support_stacked(df, out_dir / "parental_support_vs_gradeclass.png")
    plot_corr_heatmap(df, out_dir / "correlation_heatmap.png")

    # Missingness table
    (df.isna().sum().to_frame("missing_count")
       .assign(missing_pct=lambda x: (x["missing_count"]/len(df)*100).round(3))
       .sort_values("missing_count", ascending=False)
       .to_csv(out_dir / "missingness.csv"))

    # Summary json
    summary = build_summary(df)
    write_summary(summary, out_dir)

    print("EDA complete. Figures saved to:", out_dir)
    import json
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    run_eda()
