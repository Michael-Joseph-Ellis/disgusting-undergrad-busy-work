import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.metrics import mean_squared_error

# Load dataset
url = "https://raw.githubusercontent.com/selva86/datasets/master/Auto.csv"
df = pd.read_csv(url)

# Replace missing horsepower values and drop NA
df['horsepower'] = pd.to_numeric(df['horsepower'], errors='coerce')
df = df.dropna()

# Features and target
X = df[['cylinders', 'displacement', 'horsepower', 'weight', 'acceleration']]
y = df['mpg']

# Train-test split (4:1)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=0
)

# Normalize
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# ---------------- Linear Regression ----------------
lr = LinearRegression()
lr.fit(X_train_scaled, y_train)
y_pred_lr = lr.predict(X_test_scaled)
mse_lr = mean_squared_error(y_test, y_pred_lr)

print("Linear Regression MSE:", mse_lr)

# Lambda grid
lambdas = np.logspace(-3, 3, 20)

# ---------------- Ridge Regression ----------------
ridge_mses = []
for l in lambdas:
    ridge = Ridge(alpha=l)
    ridge.fit(X_train_scaled, y_train)
    pred = ridge.predict(X_test_scaled)
    ridge_mses.append(mean_squared_error(y_test, pred))

best_ridge_lambda = lambdas[np.argmin(ridge_mses)]
best_ridge_mse = min(ridge_mses)

print("\nBest Ridge Lambda:", best_ridge_lambda)
print("Best Ridge MSE:", best_ridge_mse)

# ---------------- Lasso Regression ----------------
lasso_mses = []
lasso_models = []

for l in lambdas:
    lasso = Lasso(alpha=l, max_iter=10000)
    lasso.fit(X_train_scaled, y_train)
    pred = lasso.predict(X_test_scaled)
    lasso_mses.append(mean_squared_error(y_test, pred))
    lasso_models.append(lasso)

best_lasso_idx = np.argmin(lasso_mses)
best_lasso_lambda = lambdas[best_lasso_idx]
best_lasso_mse = lasso_mses[best_lasso_idx]
best_lasso_model = lasso_models[best_lasso_idx]

print("\nBest Lasso Lambda:", best_lasso_lambda)
print("Best Lasso MSE:", best_lasso_mse)

print("\nLasso Coefficients:")
for name, coef in zip(X.columns, best_lasso_model.coef_):
    print(f"{name}: {coef:.4f}")