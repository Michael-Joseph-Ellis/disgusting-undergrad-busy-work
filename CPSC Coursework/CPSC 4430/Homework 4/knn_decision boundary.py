import numpy as np
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier

# Data using only X1 and X2
X = np.array([
    [0, 3],
    [2, 0],
    [0, 1],
    [0, 1],
    [-1, 0],
    [1, 1]
])

y = np.array(['Red', 'Red', 'Red', 'Green', 'Green', 'Red'])

# Encode labels for plotting
y_num = np.array([1 if label == 'Red' else 0 for label in y])

# Choose K
k = 3
knn = KNeighborsClassifier(n_neighbors=k)
knn.fit(X, y_num)

# Mesh grid
h = 0.02
x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

Z = knn.predict(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

# Plot decision boundary
plt.figure(figsize=(8,6))
plt.contourf(xx, yy, Z, alpha=0.3)

# Scatter points
for i in range(len(X)):
    if y[i] == 'Red':
        plt.scatter(X[i,0], X[i,1], marker='o', s=100, label='Red' if i == 0 else "")
    else:
        plt.scatter(X[i,0], X[i,1], marker='^', s=100, label='Green' if i == 3 else "")

plt.xlabel(r'$X_1$')
plt.ylabel(r'$X_2$')
plt.title(f'{k}-NN Decision Boundary using $X_1$ and $X_2$')
plt.legend()
plt.show()