import numpy as np
import matplotlib.pyplot as plt

data = {
    "Mercury": (0.38710, 87.9693),
    "Venus":   (0.72333, 224.7008),
    "Earth":   (1.00000, 365.2564),
    "Mars":    (1.52366, 686.9796),
    "Jupiter": (5.20336, 4332.8201),
    "Saturn":  (9.53707, 10775.599),
    "Uranus":  (19.1913, 30687.153),
    "Neptune": (30.0690, 60190.03),
}

train_planets = ["Mercury", "Venus", "Earth", "Mars", "Jupiter"]
test_planets = ["Uranus", "Neptune"]

# ----- 1) Build training arrays in log-space -----
X = np.array([np.log(data[p][0]) for p in train_planets], dtype=float)  # log(a)
Y = np.array([np.log(data[p][1]) for p in train_planets], dtype=float)  # log(T)

xbar = X.mean()
ybar = Y.mean()

# ----- 2) Closed-form slope/intercept (Problem 1) -----
num = ((X - xbar) * (Y - ybar)).sum()
den = ((X - xbar) ** 2).sum()

k = num / den
b = ybar - k * xbar

c = np.exp(b)  # because b = log(c)

print("Fitted parameters (natural log):")
print(f"  k = {k:.8f}")
print(f"  b = {b:.8f}")
print(f"  c = exp(b) = {c:.8f}")
print()
print(f"Model: log(T) = {k:.6f} log(a) + {b:.6f}")
print(f"      T = {c:.6f} * a^{k:.6f}")
print()

# ----- 3) Predict Uranus and Neptune -----
print("Predictions:")
print(f"{'Planet':<10} {'a(AU)':>10} {'T_true(days)':>14} {'T_pred(days)':>14} {'Error(%)':>10}")
for p in test_planets:
    a, T_true = data[p]
    T_pred = np.exp(k * np.log(a) + b)
    err_pct = 100.0 * (T_pred - T_true) / T_true
    print(f"{p:<10} {a:>10.4f} {T_true:>14.3f} {T_pred:>14.3f} {err_pct:>10.4f}")

# ----- 4) Plot all planets in one figure (log a vs log T) -----
planets = list(data.keys())
xa = np.array([np.log(data[p][0]) for p in planets])
yt = np.array([np.log(data[p][1]) for p in planets])

plt.figure()
plt.scatter(xa, yt)

# label points
for p in planets:
    plt.text(np.log(data[p][0]), np.log(data[p][1]), p, fontsize=9)

# regression line across the x-range
xline = np.linspace(xa.min(), xa.max(), 200)
yline = k * xline + b
plt.plot(xline, yline)

plt.xlabel("log a")
plt.ylabel("log T")
plt.title("Log-Log Plot of Planets with Fitted Regression Line")
plt.show()