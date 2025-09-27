from pathlib import Path


def project_root() -> Path:
    # data analysis/eda/paths.py -> .../Semester-Project
    # __file__ .../Semester-Project/data analysis/eda/paths.py
    # parents[0]=eda, [1]=data analysis, [2]=Semester-Project
    return Path(__file__).resolve().parents[2]


def data_csv_path() -> Path:
    return project_root() / "student performance dataset" / "Student_performance_data _.csv"


def figures_dir() -> Path:
    return project_root() / "Checkpoint 1" / "figures"
