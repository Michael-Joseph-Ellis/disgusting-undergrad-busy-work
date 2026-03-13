# ISTA (Algorithm 1) for Lasso + comparison with sklearn
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import Lasso

np.random.seed(0)

# Problem size
m, n = 100, 50

# Data (random example)
A = np.random.randn(m, n)
y = np.random.randn(m)

# Parameters
lambdas = [1.0, 2.0]      # lambda values to test
K = 200                   # iterations for ISTA

def objective(A, y, x, lam):
    r = A @ x - y
    return 0.5 * np.linalg.norm(r)**2 + lam * np.linalg.norm(x, 1)

def ista(A, y, lam, K, x0=None):
    m, n = A.shape
    if x0 is None:
        x = np.zeros(n)
    else:
        x = x0.copy()
    # compute sigma1(AA^T) (largest singular value of AA^T)
    sigma1 = np.linalg.svd(A @ A.T, compute_uv=False)[0]
    t = 1.0 / sigma1   # step size as in the algorithm
    objs = []
    for k in range(K):
        # gradient step on smooth part
        grad = A.T @ (A @ x - y)   # gradient of 0.5||Ax-y||^2 is A^T(Ax-y)
        z = x - t * grad
        # soft-thresholding (proximal operator)
        x = np.sign(z) * np.maximum(np.abs(z) - t * lam, 0.0)
        objs.append(objective(A, y, x, lam))
    return x, np.array(objs), t

# Run ISTA and compare with sklearn Lasso
results = {}
for lam in lambdas:
    x_ista, objs, t_used = ista(A, y, lam, K)
    results[lam] = {'x_ista': x_ista, 'objs': objs, 't': t_used}
    # sklearn Lasso mapping: sklearn minimizes (1/(2*m))||Ax-y||^2 + alpha ||x||_1
    alpha = lam / m
    lasso = Lasso(alpha=alpha, fit_intercept=False, max_iter=10000, tol=1e-8)
    lasso.fit(A, y)
    x_skl = lasso.coef_.copy()
    # compute objectives for both
    f_ista = objective(A, y, x_ista, lam)
    f_skl = objective(A, y, x_skl, lam)
    # proximity metrics
    coef_diff_norm = np.linalg.norm(x_ista - x_skl)
    coef_diff_max = np.max(np.abs(x_ista - x_skl))
    print(f"lambda={lam: .3g} | t_used={t_used:.4g} | ISTA obj={f_ista:.6g} | sklearn obj={f_skl:.6g}")
    print(f"             ||x_ista - x_skl||_2 = {coef_diff_norm:.6g}, max abs diff = {coef_diff_max:.6g}")
    print("             # nonzeros (ISTA, sklearn):", np.sum(np.abs(x_ista)>1e-8), np.sum(np.abs(x_skl)>1e-8))
    print()

# Plot objective curves
plt.figure(figsize=(8,5))
for lam in lambdas:
    objs = results[lam]['objs']
    plt.plot(np.arange(1, len(objs)+1), objs, label=f"lambda={lam}")
# Add horizontal lines for sklearn objectives
for lam in lambdas:
    alpha = lam / m
    lasso = Lasso(alpha=alpha, fit_intercept=False, max_iter=10000, tol=1e-8)
    lasso.fit(A, y)
    x_skl = lasso.coef_
    f_skl = objective(A, y, x_skl, lam)
    plt.axhline(f_skl, linestyle='--', label=f"sklearn lambda={lam} obj")

plt.xlabel("Iteration")
plt.ylabel("Objective value")
plt.title("ISTA (Algorithm 1) objective vs iteration for Lasso")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("lasso_ista_vs_sklearn.png", dpi=150)
plt.show()