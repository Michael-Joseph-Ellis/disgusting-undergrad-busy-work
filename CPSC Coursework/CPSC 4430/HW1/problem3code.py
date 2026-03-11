import numpy as np

np.random.seed(0)

m, n = 10, 5
A = np.random.randn(m, n)

# Build projection matrix P = A (A^T A)^{-1} A^T
AtA = A.T @ A
P = A @ np.linalg.inv(AtA) @ A.T

# 1) Verify P^n = P (numerically)
for power in [2, 3, 5, 10]:
    diff = np.linalg.norm(np.linalg.matrix_power(P, power) - P, ord='fro')
    print(f"||P^{power} - P||_F = {diff:.3e}")

# 2) Eigenvalues should be ~ 0 or 1
eigvals = np.linalg.eigvals(P)
eigvals_sorted = np.sort(np.real(eigvals))[::-1] 
print("\nEigenvalues (sorted):")
print(np.round(eigvals_sorted, 10))

# Check closeness to 0 or 1
dist_to_0 = np.min(np.abs(eigvals_sorted - 0))
dist_to_1 = np.min(np.abs(eigvals_sorted - 1))
print(f"\nMin distance to 0: {dist_to_0:.3e}")
print(f"Min distance to 1: {dist_to_1:.3e}")

# 3) trace(P) = rank(P)
tr = np.trace(P)
rk = np.linalg.matrix_rank(P)
print(f"\ntrace(P) = {tr:.10f}")
print(f"rank(P)  = {rk}")