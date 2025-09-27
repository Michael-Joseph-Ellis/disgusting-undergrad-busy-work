from __future__ import annotations

import pandas as pd

from .paths import data_csv_path
from .constants import GRADE_MAP


def load_dataset() -> pd.DataFrame:
    df = pd.read_csv(data_csv_path())
    df["GradeLabel"] = df["GradeClass"].map(GRADE_MAP)
    return df
