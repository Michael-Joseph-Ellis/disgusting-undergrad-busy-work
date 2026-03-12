import numpy as np
import matplotlib.pyplot as plt

# Data
x = np.array([1, 2, 3, 4, 5], dtype=float)
y = np.array([1, 3, 9, 15, 24], dtype=float)

# fit cubic polynomial: y ≈ a3 x^3 + a2 x^2 + a1 x + a0
coeffs = np.polyfit(x, y, deg=3)
poly = np.poly1d(coeffs)

print("Cubic coefficients [a3, a2, a1, a0]:")
print(coeffs)

# curve
x_plot = np.linspace(x.min(), x.max(), 400)
y_plot = poly(x_plot)

# plotting
plt.figure()
plt.scatter(x, y)          # sample points
plt.plot(x_plot, y_plot)   # fitted curve

plt.xlabel("x")
plt.ylabel("y")
plt.title("Fitting with Polynomial Regression (Order 3)")