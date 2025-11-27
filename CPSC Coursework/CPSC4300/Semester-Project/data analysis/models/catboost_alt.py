from __future__ import annotations

import json
from pathlib import Path
import sys
from typing import List

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from catboost import CatBoostClassifier, Pool
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, f1_score
from sklearn.model_selection import StratifiedKFold, train_test_split, cross_val_score

# Ensure local package import works when running as a script
HERE = Path(__file__).resolve()
DATA_ANALYSIS_DIR = HERE.parents[1]  # .../data analysis
if str(DATA_ANALYSIS_DIR) not in sys.path:
    sys.path.append(str(DATA_ANALYSIS_DIR))

from eda.loader import load_dataset
from eda.paths import figures_dir, project_root
from eda.constants import GRADE_MAP
from models.xgb_baseline import prepare_data, select_three_cases


RANDOM_STATE = 42


def plot_confusion(y_true: np.ndarray, y_pred: np.ndarray, out_path: Path):
    labels = [0, 1, 2, 3, 4]
    label_names = [GRADE_MAP[i] for i in labels]
    cm = confusion_matrix(y_true, y_pred, labels=labels, normalize=None)
    cm_norm = confusion_matrix(y_true, y_pred, labels=labels, normalize="true")

    fig, axes = plt.subplots(1, 2, figsize=(12, 5))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", ax=axes[0], xticklabels=label_names, yticklabels=label_names)
    axes[0].set_title("Confusion Matrix (counts) - CatBoost")
    axes[0].set_xlabel("Predicted")
    axes[0].set_ylabel("True")

    sns.heatmap(cm_norm, annot=True, fmt=".2f", cmap="Greens", ax=axes[1], xticklabels=label_names, yticklabels=label_names, vmin=0, vmax=1)
    axes[1].set_title("Confusion Matrix (row-normalized) - CatBoost")
    axes[1].set_xlabel("Predicted")
    axes[1].set_ylabel("True")

    plt.tight_layout()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(out_path, dpi=200)
    plt.close()


def plot_feature_importance(model: CatBoostClassifier, feature_names: List[str], out_path: Path):
    importances = model.get_feature_importance(type="FeatureImportance")
    imp_df = pd.DataFrame({"feature": feature_names, "importance": importances})
    imp_df = imp_df.sort_values("importance", ascending=False).head(15)

    plt.figure(figsize=(8, 6))
    sns.barplot(data=imp_df, y="feature", x="importance", color="#F58518")
    plt.title("CatBoost feature importance")
    plt.xlabel("Importance")
    plt.ylabel("")
    plt.tight_layout()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(out_path, dpi=200)
    plt.close()


def main():
    root = project_root()
    figures_out = figures_dir()
    reports_dir = root / "Checkpoint 2"
    reports_dir.mkdir(parents=True, exist_ok=True)

    df = load_dataset()
    X, y, feature_cols = prepare_data(df)

    # Identify categorical feature indices for CatBoost
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
    cat_features = [i for i, c in enumerate(X.columns) if c in categorical_cols]

    # Train/validation/test split (match XGBoost baseline)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, stratify=y, random_state=RANDOM_STATE
    )
    X_tr, X_val, y_tr, y_val = train_test_split(
        X_train, y_train, test_size=0.2, stratify=y_train, random_state=RANDOM_STATE
    )

    # Cross-validated macro F1 on training split
    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=RANDOM_STATE)

    def make_model():
        return CatBoostClassifier(
            loss_function="MultiClass",
            random_seed=RANDOM_STATE,
            depth=6,
            learning_rate=0.1,
            iterations=500,
            l2_leaf_reg=3.0,
            eval_metric="TotalF1:average=Macro",
            auto_class_weights="Balanced",
            verbose=False,
        )

    def cv_fit_predict(estimator, X_cv, y_cv):
        # CatBoost needs Pool with cat_features; we just fit in-place for each fold
        estimator.fit(X_cv, y_cv, cat_features=cat_features, verbose=False)
        preds = estimator.predict(X_cv)
        # predictions are shape (n_samples, 1) with class labels
        preds = preds.reshape(-1).astype(int)
        return preds

    # Manual CV loop for macro F1
    cv_scores = []
    for train_idx, val_idx in cv.split(X_train, y_train):
        model_cv = make_model()
        X_tr_cv, X_val_cv = X_train.iloc[train_idx], X_train.iloc[val_idx]
        y_tr_cv, y_val_cv = y_train.iloc[train_idx], y_train.iloc[val_idx]
        model_cv.fit(
            X_tr_cv,
            y_tr_cv,
            cat_features=cat_features,
            eval_set=(X_val_cv, y_val_cv),
            verbose=False,
        )
        y_val_pred = model_cv.predict(X_val_cv).reshape(-1).astype(int)
        score = f1_score(y_val_cv, y_val_pred, average="macro")
        cv_scores.append(score)

    # Train final model with early stopping
    train_pool = Pool(X_tr, y_tr, cat_features=cat_features)
    val_pool = Pool(X_val, y_val, cat_features=cat_features)

    model = make_model()
    model.fit(
        train_pool,
        eval_set=val_pool,
        use_best_model=True,
        verbose=False,
    )

    # Evaluate on held-out test set
    test_pool = Pool(X_test, cat_features=cat_features)
    y_pred = model.predict(test_pool).reshape(-1).astype(int)
    y_proba = model.predict_proba(test_pool)

    acc = accuracy_score(y_test, y_pred)
    f1_macro = f1_score(y_test, y_pred, average="macro")
    report = classification_report(y_test, y_pred, output_dict=True)

    # Plots
    plot_confusion(y_test.values, y_pred, figures_out / "catboost_confusion_mats.png")
    plot_feature_importance(model, list(X.columns), figures_out / "catboost_feature_importance.png")

    # Three illustrative cases
    cases = select_three_cases(X_test, y_test, y_proba)
    cases_out = reports_dir / "catboost_three_cases.csv"
    cases.to_csv(cases_out, index=False)

    # Summary JSON
    summary = {
        "model": "CatBoostClassifier",
        "params": model.get_params(),
        "cv_f1_macro_mean": float(np.mean(cv_scores)),
        "cv_f1_macro_std": float(np.std(cv_scores)),
        "test_accuracy": float(acc),
        "test_f1_macro": float(f1_macro),
        "classification_report": report,
        "three_cases_file": str(cases_out),
        "figures": {
            "confusion_matrices": str(figures_out / "catboost_confusion_mats.png"),
            "feature_importance": str(figures_out / "catboost_feature_importance.png"),
        },
    }

    with open(reports_dir / "catboost_alt_summary.json", "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=2)

    print(json.dumps({k: v for k, v in summary.items() if k not in ["classification_report"]}, indent=2))


if __name__ == "__main__":
    main()
