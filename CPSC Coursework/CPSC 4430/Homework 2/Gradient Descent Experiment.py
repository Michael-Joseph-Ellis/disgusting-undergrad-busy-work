import numpy as np
import matplotlib.pyplot as plt

np.random.seed(0)
m, n = 100, 50
A = np.random.randn(m, n)
y = np.random.randn(m)
gamma = 1.0
iterations = 100

def objective(x):
    r = A @ x - y
    return np.linalg.norm(r)**2 + gamma * np.linalg.norm(x)**2

def gradient(x):
    return 2 * A.T @ (A @ x - y) + 2 * gamma * x

# compute sigma_max(A)
s = np.linalg.svd(A, compute_uv=False)
sigma_max = s[0]
lambda_safe = 1.0 / (2.0 * (sigma_max**2 + gamma))

# choose step sizes around the safe value
lambdas = [lambda_safe * f for f in [0.1, 0.5, 1.0, 2.0]]
labels = [f"{f:.1g} * lambda_safe" for f in [0.1, 0.5, 1.0, 2.0]]

results = {}
for lam, lab in zip(lambdas, labels):
    x = np.zeros(n)
    objs = []
    diverged = False
    for it in range(iterations):
        val = objective(x)
        if not np.isfinite(val) or val > 1e100:
            # stop on divergence
            objs.append(np.nan)
            diverged = True
            break
        objs.append(val)
        x = x - lam * gradient(x)
    # pad to uniform length for plotting
    if len(objs) < iterations:
        objs += [np.nan] * (iterations - len(objs))
    results[lab] = np.array(objs)

# closed-form solution objective for reference
x_star = np.linalg.solve(A.T @ A + gamma * np.eye(n), A.T @ y)
f_star = objective(x_star)

plt.figure(figsize=(8,5))
for lab, vals in results.items():
    mask = np.isfinite(vals)
    if mask.any():
        plt.plot(np.arange(len(vals))[mask], vals[mask], label=lab)
plt.axhline(f_star, linestyle='--', label='closed-form optimum')
plt.yscale('log')
plt.xlabel('Iteration')
plt.ylabel('Objective value (log scale)')
plt.title('GD on Ridge regression (safe step sizes tested)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('ridge_gd_safe.png', dpi=150)
plt.show()