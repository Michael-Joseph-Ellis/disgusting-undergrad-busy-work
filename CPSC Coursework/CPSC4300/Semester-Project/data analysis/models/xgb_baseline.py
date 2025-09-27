from __future__ import annotations

import json
from pathlib import Path
import sys
from typing import Dict, List

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, f1_score
from sklearn.model_selection import StratifiedKFold, train_test_split, cross_val_score
from xgboost import XGBClassifier

# Ensure local package import works when running as a script
HERE = Path(__file__).resolve()
DATA_ANALYSIS_DIR = HERE.parents[1]  # .../data analysis
if str(DATA_ANALYSIS_DIR) not in sys.path:
    sys.path.append(str(DATA_ANALYSIS_DIR))

from eda.loader import load_dataset
from eda.paths import figures_dir, project_root
from eda.constants import GRADE_MAP


RANDOM_STATE = 42


def prepare_data(df: pd.DataFrame):
    # Target
    y = df["GradeClass"].astype(int)

    # Drop ID and GPA (leakage), keep remaining features
    feature_cols = [
        c
        for c in df.columns
        if c
        not in [
            "StudentID",
            "GPA",
            "GradeClass",
            "GradeLabel",
        ]
    ]
    X = df[feature_cols].copy()

    # Cast categoricals to 'category' for native categorical support in XGBoost
    categorical_cols = [
        "Gender",
        "Ethnicity",
        "ParentalEducation",
        "Tutoring",
        "ParentalSupport",
        "Extracurricular",
        "Sports",
        "Music",
        "Volunteering",
    ]
    for col in categorical_cols:
        if col in X.columns:
            X[col] = X[col].astype("category")

    # Ensure numerics are float
    for col in X.columns:
        if col not in categorical_cols:
            X[col] = pd.to_numeric(X[col], errors="coerce")

    return X, y, feature_cols


def train_xgb(X_train: pd.DataFrame, y_train: pd.Series, X_val: pd.DataFrame, y_val: pd.Series) -> XGBClassifier:
    model = XGBClassifier(
        objective="multi:softprob",
        num_class=5,
        tree_method="hist",
        # modest baseline params
        max_depth=6,
        learning_rate=0.1,
        n_estimators=500,
        subsample=0.9,
        colsample_bytree=0.9,
        reg_lambda=1.0,
        reg_alpha=0.0,
        random_state=RANDOM_STATE,
        enable_categorical=True,
        eval_metric="mlogloss",
        n_jobs=0,
    )
    model.fit(
        X_train,
        y_train,
        eval_set=[(X_val, y_val)],
        verbose=False,
    )
    return model


def plot_confusion(y_true: np.ndarray, y_pred: np.ndarray, out_path: Path):
    labels = [0, 1, 2, 3, 4]
    label_names = [GRADE_MAP[i] for i in labels]
    cm = confusion_matrix(y_true, y_pred, labels=labels, normalize=None)
    cm_norm = confusion_matrix(y_true, y_pred, labels=labels, normalize="true")

    fig, axes = plt.subplots(1, 2, figsize=(12, 5))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", ax=axes[0], xticklabels=label_names, yticklabels=label_names)
    axes[0].set_title("Confusion Matrix (counts)")
    axes[0].set_xlabel("Predicted")
    axes[0].set_ylabel("True")

    sns.heatmap(cm_norm, annot=True, fmt=".2f", cmap="Greens", ax=axes[1], xticklabels=label_names, yticklabels=label_names, vmin=0, vmax=1)
    axes[1].set_title("Confusion Matrix (row-normalized)")
    axes[1].set_xlabel("Predicted")
    axes[1].set_ylabel("True")

    plt.tight_layout()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(out_path, dpi=200)
    plt.close()


def plot_feature_importance(model: XGBClassifier, feature_names: List[str], out_path: Path):
    booster = model.get_booster()
    score = booster.get_score(importance_type="gain")  # dict: feature -> importance
    # Features are typically named f0, f1, ... in order of columns
    mapping = {f"f{i}": name for i, name in enumerate(feature_names)}
    items = [(mapping.get(k, k), v) for k, v in score.items()]
    if not items:
        return
    imp_df = pd.DataFrame(items, columns=["feature", "gain"]).sort_values("gain", ascending=False)
    imp_df = imp_df.head(15)

    plt.figure(figsize=(8, 6))
    sns.barplot(data=imp_df, y="feature", x="gain", color="#4C78A8")
    plt.title("XGBoost feature importance (gain)")
    plt.xlabel("Gain")
    plt.ylabel("")
    plt.tight_layout()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(out_path, dpi=200)
    plt.close()


def select_three_cases(X_test: pd.DataFrame, y_test: pd.Series, proba: np.ndarray) -> pd.DataFrame:
    # Pick one exemplar from predicted A, B, and F with highest confidence, if available; else random
    pred = proba.argmax(axis=1)
    df_cases = pd.DataFrame({
        "index": np.arange(len(y_test)),
        "true": y_test.values,
        "pred": pred,
        "conf": proba.max(axis=1),
    })
    wanted = [0, 1, 4]  # A, B, F
    rows = []
    for cls in wanted:
        subset = df_cases[df_cases["pred"] == cls]
        if len(subset) == 0:
            continue
        rows.append(subset.sort_values("conf", ascending=False).head(1))
    if not rows:
        rows.append(df_cases.sample(3, random_state=RANDOM_STATE))
    pick = pd.concat(rows).head(3)
    pick["true_label"] = pick["true"].map(GRADE_MAP)
    pick["pred_label"] = pick["pred"].map(GRADE_MAP)
    return pick


def main():
    root = project_root()
    figures_out = figures_dir()
    reports_dir = root / "Checkpoint 2"
    reports_dir.mkdir(parents=True, exist_ok=True)

    df = load_dataset()
    X, y, feature_cols = prepare_data(df)

    # Train/validation/test split
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, stratify=y, random_state=RANDOM_STATE
    )
    X_tr, X_val, y_tr, y_val = train_test_split(
        X_train, y_train, test_size=0.2, stratify=y_train, random_state=RANDOM_STATE
    )

    # Cross-validated score on training split
    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=RANDOM_STATE)
    model_cv = XGBClassifier(
        objective="multi:softprob",
        num_class=5,
        tree_method="hist",
        max_depth=6,
        learning_rate=0.1,
        n_estimators=300,
        subsample=0.9,
        colsample_bytree=0.9,
        reg_lambda=1.0,
        reg_alpha=0.0,
        random_state=RANDOM_STATE,
        enable_categorical=True,
        eval_metric="mlogloss",
        n_jobs=0,
    )
    cv_scores = cross_val_score(model_cv, X_train, y_train, scoring="f1_macro", cv=cv, n_jobs=None)

    # Train with early stopping on validation
    model = train_xgb(X_tr, y_tr, X_val, y_val)

    # Evaluate
    y_pred = model.predict(X_test)
    y_proba = model.predict_proba(X_test)
    acc = accuracy_score(y_test, y_pred)
    f1_macro = f1_score(y_test, y_pred, average="macro")
    report = classification_report(y_test, y_pred, output_dict=True)

    # Plots
    plot_confusion(y_test, y_pred, figures_out / "xgb_confusion_mats.png")
    plot_feature_importance(model, list(X.columns), figures_out / "xgb_feature_importance.png")

    # Three cases
    cases = select_three_cases(X_test, y_test, y_proba)
    cases_out = reports_dir / "xgb_three_cases.csv"
    cases.to_csv(cases_out, index=False)

    # Save summary JSON
    summary = {
        "model": "XGBClassifier",
        "params": model.get_params(),
        "best_iteration_": getattr(model, "best_iteration", None),
        "cv_f1_macro_mean": float(np.mean(cv_scores)),
        "cv_f1_macro_std": float(np.std(cv_scores)),
        "test_accuracy": float(acc),
        "test_f1_macro": float(f1_macro),
        "classification_report": report,
        "three_cases_file": str(cases_out),
        "figures": {
            "confusion_matrices": str(figures_out / "xgb_confusion_mats.png"),
            "feature_importance": str(figures_out / "xgb_feature_importance.png"),
        },
    }
    with open(reports_dir / "xgb_baseline_summary.json", "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=2)

    print(json.dumps({k: v for k, v in summary.items() if k not in ["classification_report"]}, indent=2))


if __name__ == "__main__":
    main()
