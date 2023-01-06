import numpy as np

A = np.array([[10., -1.,  2., 0.],
              [-1., 11., -1., 3.],
              [2.,  -1., 10., -1.],
              [0.0, 3.,  -1., 8.]])
i = 1
b = np.array([6., 25., -11., 15.])
x = np.zeros_like(b)
x_new = np.zeros_like(x)
print(A[i, :i], x_new[:i])
print(A[i, i + 1:], x[i + 1:])

for i in range(A.shape[0]):
    s1 = np.dot(A[i, :i], x_new[:i])
    s2 = np.dot(A[i, i + 1:], x[i + 1:])
    x_new[i] = (b[i] - s1 - s2) / A[i, i]
