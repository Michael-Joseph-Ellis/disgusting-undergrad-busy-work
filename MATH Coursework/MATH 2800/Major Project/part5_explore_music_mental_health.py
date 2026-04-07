from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

# ============================================================
# Part 5: Exploring the Data Thoughtfully
# Music taste + time spent listening vs mental health
# Colab-friendly version
# ============================================================

# ----------------------------
# File paths
# ----------------------------
BASE_PATH = Path(r"C:\Users\unkno\OneDrive\Documents\GitHub\disgusting-undergrad-busy-work\MATH Coursework\MATH 2800\Major Project")

RAW_FILE = BASE_PATH / "mxmh_survey_results.csv"
CLEAN_FILE = BASE_PATH / "mxmh_survey_results_cleaned.csv"

OUTPUT_DIR = BASE_PATH / "part5_outputs"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# use cleaned file if it exists, otherwise raw
INPUT_FILE = CLEAN_FILE if CLEAN_FILE.exists() else RAW_FILE

print(f"Using input file: {INPUT_FILE}")
print(f"Saving outputs to: {OUTPUT_DIR}")

# ----------------------------
# Load data
# ----------------------------
df = pd.read_csv(INPUT_FILE)
df.columns = df.columns.str.strip()

# ----------------------------
# Helpers
# ----------------------------
def normalize_text(series):
    return series.astype("string").str.strip().str.replace(r"\s+", " ", regex=True)


def save_fig(filename):
    path = OUTPUT_DIR / filename
    plt.tight_layout()
    plt.savefig(path, bbox_inches="tight")
    print(f"Saved: {path}")
    plt.close()


def compare_missingness(original_df, target_col, compare_cols):
    missing_group = original_df[original_df[target_col].isna()]
    non_missing_group = original_df[original_df[target_col].notna()]

    print(f"\n--- Missingness check for: {target_col} ---")
    print(f"Missing rows: {len(missing_group)}")
    print(f"Non-missing rows: {len(non_missing_group)}")

    for col in compare_cols:
        if col in original_df.columns and pd.api.types.is_numeric_dtype(original_df[col]):
            miss_mean = missing_group[col].mean()
            nonmiss_mean = non_missing_group[col].mean()
            print(f"{col}: missing mean = {miss_mean:.3f}, non-missing mean = {nonmiss_mean:.3f}")

# ----------------------------
# If the raw file is used, clean it inline
# ----------------------------
if INPUT_FILE == RAW_FILE:
    print("Raw data detected, applying minimal cleaning for exploration...")

    numeric_cols = ["Age", "Hours per day", "BPM", "Anxiety", "Depression", "Insomnia", "OCD"]
    for col in numeric_cols:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")

    text_cols = [
        "Primary streaming service",
        "While working",
        "Instrumentalist",
        "Composer",
        "Fav genre",
        "Exploratory",
        "Foreign languages",
        "Music effects",
        "Permissions",
    ]

    for col in text_cols:
        if col in df.columns:
            df[col] = normalize_text(df[col])

    # fairness checks before any dropping/filling
    if "BPM" in df.columns:
        compare_missingness(df, "BPM", ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"])
    if "Music effects" in df.columns:
        compare_missingness(df, "Music effects", ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"])

    # cleaning choices for exploration
    key_cols = [c for c in ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"] if c in df.columns]
    df = df.dropna(subset=key_cols)

    if "BPM" in df.columns:
        df["BPM"] = df["BPM"].fillna(df["BPM"].median())

    for col in text_cols:
        if col in df.columns:
            df[col] = df[col].fillna("Unknown")

    if "Fav genre" in df.columns:
        df["Fav genre"] = df["Fav genre"].str.title()
    if "Primary streaming service" in df.columns:
        df["Primary streaming service"] = df["Primary streaming service"].str.title()
    if "Music effects" in df.columns:
        df["Music effects"] = df["Music effects"].str.title()
    for col in ["While working", "Instrumentalist", "Composer", "Exploratory", "Foreign languages", "Permissions"]:
        if col in df.columns:
            df[col] = df[col].str.title()

    if "Hours per day" in df.columns:
        df = df[(df["Hours per day"] >= 0) & (df["Hours per day"] <= 24)]
else:
    # Cleaned file: just ensure the fields are in good shape for plotting.
    for col in ["Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"]:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")
    for col in ["Fav genre", "Music effects"]:
        if col in df.columns:
            df[col] = normalize_text(df[col])

# ----------------------------
# Required columns
# ----------------------------
required_cols = [
    "Hours per day",
    "Fav genre",
    "Music effects",
    "Anxiety",
    "Depression",
    "Insomnia",
    "OCD",
]
missing_required = [c for c in required_cols if c not in df.columns]
if missing_required:
    raise ValueError(f"Missing required columns: {missing_required}")

# ----------------------------
# Summary stats
# ----------------------------
summary_file = OUTPUT_DIR / "part5_summary_stats.csv"
summary = df[["Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"]].describe()
summary.to_csv(summary_file)
print("\nSummary statistics:\n", summary)

music_effects_means = df.groupby("Music effects")[["Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"]].mean().round(3)
music_effects_means_file = OUTPUT_DIR / "music_effects_means.csv"
music_effects_means.to_csv(music_effects_means_file)
print("\nMean values by Music effects:\n", music_effects_means)

genre_counts = df["Fav genre"].value_counts(dropna=False)
genre_counts_file = OUTPUT_DIR / "genre_counts.csv"
genre_counts.to_csv(genre_counts_file, header=["count"])
print("\nTop genre counts:\n", genre_counts.head(10))

# ----------------------------
# Visualizations
# ----------------------------
plt.rcParams.update({"figure.dpi": 160, "savefig.dpi": 160, "font.size": 10})
mental_cols = ["Anxiety", "Depression", "Insomnia", "OCD"]

# 1) Hours per day distribution
plt.figure(figsize=(8, 5))
plt.hist(df["Hours per day"].dropna(), bins=20)
plt.xlabel("Hours spent listening to music per day")
plt.ylabel("Number of respondents")
plt.title("Distribution of Daily Music Listening Time")
save_fig("01_hours_per_day_distribution.png")

# 2) Mental health distributions
fig, axes = plt.subplots(2, 2, figsize=(10, 7))
for ax, col in zip(axes.ravel(), mental_cols):
    ax.hist(df[col].dropna(), bins=10)
    ax.set_title(col)
    ax.set_xlabel("Score")
    ax.set_ylabel("Count")
fig.suptitle("Distributions of Mental Health Scores", y=1.02)
save_fig("02_mental_health_distributions.png")

# 3) Scatter: hours vs mental health
fig, axes = plt.subplots(2, 2, figsize=(10, 7))
for ax, col in zip(axes.ravel(), mental_cols):
    ax.scatter(df["Hours per day"], df[col], alpha=0.6)
    ax.set_xlabel("Hours per day")
    ax.set_ylabel(col)
    ax.set_title(f"Hours per day vs {col}")
fig.suptitle("Relationship Between Listening Time and Mental Health", y=1.02)
save_fig("03_hours_vs_mental_health_scatter.png")

# 4) Boxplots by music effects
if "Unknown" in set(df["Music effects"].dropna()):
    ordered_effects = [x for x in ["Improve", "No Effect", "Worsen", "Unknown"] if x in set(df["Music effects"].dropna())]
else:
    ordered_effects = [x for x in ["Improve", "No Effect", "Worsen"] if x in set(df["Music effects"].dropna())]
    if not ordered_effects:
        ordered_effects = sorted(df["Music effects"].dropna().unique().tolist())

fig, axes = plt.subplots(2, 2, figsize=(10, 7))
for ax, col in zip(axes.ravel(), mental_cols):
    data = [df.loc[df["Music effects"] == effect, col].dropna() for effect in ordered_effects]
    ax.boxplot(data, tick_labels=ordered_effects, showfliers=False)
    ax.set_title(f"{col} by Music Effects")
    ax.set_xlabel("Music effects")
    ax.set_ylabel(col)
    ax.tick_params(axis='x', rotation=25)
fig.suptitle("Mental Health Scores by Perceived Music Effects", y=1.02)
save_fig("04_mental_health_by_music_effects_boxplots.png")

# 5) Top genres
plt.figure(figsize=(10, 6))
plot_counts = df["Fav genre"].value_counts().head(10)
plot_counts.sort_values().plot(kind="barh")
plt.xlabel("Number of respondents")
plt.ylabel("Favorite genre")
plt.title("Top Favorite Genres")
save_fig("05_top_genres.png")

# 6) Correlation matrix
correlation = df[["Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"]].corr()
plt.figure(figsize=(7, 6))
plt.imshow(correlation, interpolation="nearest")
plt.colorbar(label="Correlation")
plt.xticks(range(len(correlation.columns)), correlation.columns, rotation=30, ha="right")
plt.yticks(range(len(correlation.index)), correlation.index)
plt.title("Correlation Among Listening Time and Mental Health Scores")
for i in range(len(correlation.index)):
    for j in range(len(correlation.columns)):
        plt.text(j, i, f"{correlation.iloc[i, j]:.2f}", ha="center", va="center")
save_fig("06_correlation_matrix.png")

# 7) Average anxiety by top genres
subset = df[df["Fav genre"].isin(df["Fav genre"].value_counts().head(8).index)]
mean_anxiety_by_genre = subset.groupby("Fav genre")["Anxiety"].mean().sort_values()
plt.figure(figsize=(9, 5))
mean_anxiety_by_genre.plot(kind="barh")
plt.xlabel("Average anxiety score")
plt.ylabel("Favorite genre")
plt.title("Average Anxiety by Top Favorite Genres")
save_fig("07_average_anxiety_by_genre.png")