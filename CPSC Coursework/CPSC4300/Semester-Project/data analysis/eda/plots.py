from __future__ import annotations

from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

from .constants import GRADE_ORDER


def setup_theme():
    sns.set_theme(style="whitegrid", context="talk")


def savefig(out_path: Path):
    out_path.parent.mkdir(parents=True, exist_ok=True)
    plt.tight_layout()
    plt.savefig(out_path, dpi=200)
    plt.close()


def plot_grade_distribution(df: pd.DataFrame, out_path: Path):
    setup_theme()
    plt.figure(figsize=(8, 5))
    sns.countplot(data=df, x="GradeLabel", order=GRADE_ORDER, color="#4C78A8")
    plt.title("GradeClass distribution")
    plt.xlabel("Grade class")
    plt.ylabel("Count")
    for i, label in enumerate(GRADE_ORDER):
        count = (df["GradeLabel"] == label).sum()
        plt.text(i, count + max(1, 0.01 * len(df)), str(count), ha="center")
    savefig(out_path)


def plot_gpa_hist(df: pd.DataFrame, out_path: Path):
    setup_theme()
    plt.figure(figsize=(8, 5))
    sns.histplot(df["GPA"], kde=True, bins=30, color="#F58518")
    plt.title("GPA distribution")
    plt.xlabel("GPA")
    plt.ylabel("Count")
    savefig(out_path)


def plot_box_by_grade(df: pd.DataFrame, y: str, title: str, y_label: str, out_path: Path):
    setup_theme()
    plt.figure(figsize=(9, 5))
    sns.boxplot(data=df, x="GradeLabel", y=y, order=GRADE_ORDER)
    plt.title(title)
    plt.xlabel("Grade class")
    plt.ylabel(y_label)
    savefig(out_path)


def plot_parental_support_stacked(df: pd.DataFrame, out_path: Path):
    setup_theme()
    plt.figure(figsize=(9, 6))
    cross = (
        pd.crosstab(df["ParentalSupport"], df["GradeLabel"], normalize="index").reindex(columns=GRADE_ORDER)
    )
    cross.plot(kind="bar", stacked=True, colormap="tab20", ax=plt.gca())
    plt.title("Grade class distribution by parental support")
    plt.xlabel("Parental support (0 None – 4 Very High)")
    plt.ylabel("Proportion")
    plt.legend(title="Grade", bbox_to_anchor=(1.02, 1), loc="upper left")
    savefig(out_path)


def plot_corr_heatmap(df: pd.DataFrame, out_path: Path):
    setup_theme()
    numeric_cols = [c for c in df.select_dtypes(include=[np.number]).columns if c not in ["StudentID", "GradeClass"]]
    corr = df[numeric_cols].corr(numeric_only=True)
    plt.figure(figsize=(10, 8))
    sns.heatmap(corr, cmap="coolwarm", center=0, annot=False)
    plt.title("Correlation heatmap (numeric features incl. GPA)")
    savefig(out_path)
