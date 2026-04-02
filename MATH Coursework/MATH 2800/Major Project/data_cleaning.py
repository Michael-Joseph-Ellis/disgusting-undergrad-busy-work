from pathlib import Path
import pandas as pd

# ----------------------------
# File paths
# ----------------------------
INPUT_FILE = Path(r"C:\Users\unkno\OneDrive\Documents\GitHub\disgusting-undergrad-busy-work\MATH Coursework\MATH 2800\Major Project\mxmh_survey_results.csv")
OUTPUT_FILE = INPUT_FILE.with_name("mxmh_survey_results_cleaned.csv")
REPORT_FILE = INPUT_FILE.with_name("data_cleaning_report.txt")

# ----------------------------
# Load data
# ----------------------------
df_raw = pd.read_csv(INPUT_FILE)
df = df_raw.copy()

print("Initial shape:", df.shape)
print("\nInitial info:")
print(df.info())

print("\nInitial summary stats:")
print(df.describe(include="all"))

print("\nInitial missing values:")
missing_counts = df.isnull().sum()
print(missing_counts)

# ----------------------------
# data cleaning helpers
# ----------------------------
def normalize_text(series):
    """
    Strip leading/trailing whitespace and normalize internal spacing.
    Keeps missing values as missing for now.
    """
    return series.astype("string").str.strip().str.replace(r"\s+", " ", regex=True)

def compare_missingness(original_df, target_col, compare_cols):
    """
    Compare rows with missing vs non-missing values in target_col.
    Useful for fairness checks before dropping data.
    """
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
# Standardize column names a little
# ----------------------------
df.columns = df.columns.str.strip()

# ----------------------------
# Convert numeric columns
# ----------------------------
numeric_cols = ["Age", "Hours per day", "BPM", "Anxiety", "Depression", "Insomnia", "OCD"]

for col in numeric_cols:
    if col in df.columns:
        df[col] = pd.to_numeric(df[col], errors="coerce")

# ----------------------------
# fairness checks BEFORE cleaning
# ----------------------------
# Compare characteristics of rows missing BPM and Music effects
# using the original data btw
compare_missingness(df_raw, "BPM", ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"])
compare_missingness(df_raw, "Music effects", ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"])

# ----------------------------
# Clean text / categorical columns
# ----------------------------
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

# Standardize a few important categorical variables more consistently
if "Fav genre" in df.columns:
    df["Fav genre"] = df["Fav genre"].str.title()

if "Primary streaming service" in df.columns:
    df["Primary streaming service"] = df["Primary streaming service"].str.title()

if "Music effects" in df.columns:
    df["Music effects"] = df["Music effects"].str.title()

# Normalize yes/no style variables
for col in ["While working", "Instrumentalist", "Composer", "Exploratory", "Foreign languages", "Permissions"]:
    if col in df.columns:
        df[col] = df[col].str.title()

# ----------------------------
# Handle missing values
# ----------------------------

# 1) Drop rows missing key analysis variables
# These are the rows that cannot support the main research question.
key_cols = ["Age", "Hours per day", "Anxiety", "Depression", "Insomnia", "OCD"]
existing_key_cols = [col for col in key_cols if col in df.columns]
before_drop = len(df)
df = df.dropna(subset=existing_key_cols)
after_drop = len(df)

# 2) Fill BPM with median
# BPM has a large number of missing values, but it is not the main variable of interest.
# Median imputation preserves sample size and avoids extreme values.
if "BPM" in df.columns:
    bpm_median = df["BPM"].median()
    df["BPM"] = df["BPM"].fillna(bpm_median)

# 3) Fill remaining categorical missing values with "Unknown"
# This keeps rows in the dataset while making missingness explicit.
for col in text_cols:
    if col in df.columns:
        df[col] = df[col].fillna("Unknown")

# ----------------------------
# sanity filters
# ----------------------------
# Keep only plausible listening hours.
# These bounds match the observed dataset and avoid impossible values.
if "Hours per day" in df.columns:
    df = df[(df["Hours per day"] >= 0) & (df["Hours per day"] <= 24)]

# ----------------------------
# final checks
# ----------------------------
print("\nAfter cleaning shape:", df.shape)

print("\nMissing values after cleaning:")
print(df.isnull().sum())

print("\nCleaned summary stats:")
print(df.describe(include="all"))

# Compare missing vs non-missing groups after cleaning is not useful for columns already filled,
# so we only report what happened.
print("\nRows before dropping key missing values:", before_drop)
print("Rows after dropping key missing values:", after_drop)
print("Rows removed for key missing values:", before_drop - after_drop)

# ----------------------------
# save cleaned data
# ----------------------------
df.to_csv(OUTPUT_FILE, index=False)
print(f"\nCleaned data saved to: {OUTPUT_FILE}")

# ----------------------------
# write a simple cleaning report
# ----------------------------
report_lines = [
    "Data Cleaning Report",
    "====================",
    f"Original rows: {len(df_raw)}",
    f"Rows after cleaning: {len(df)}",
    "",
    "steps completed:",
    "- Converted numeric columns to numeric types",
    "- Standardized text categories",
    "- Dropped rows missing key analysis variables",
    "- Imputed missing BPM values with the median",
    "- Filled remaining categorical missing values with 'Unknown'",
    "- Removed impossible values outside plausible ranges",
    "",
    "notes:",
    "- Missing data was checked before cleaning to assess fairness",
    "- Cleaning steps were documented for transparency",
    "- Data was not fabricated or altered beyond necessary preprocessing",
]

with open(REPORT_FILE, "w", encoding="utf-8") as f:
    f.write("\n".join(report_lines))

print(f"Cleaning report saved to: {REPORT_FILE}")