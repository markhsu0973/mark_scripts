#!/usr/bin/python
# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs, make_circles

# 下面我們生成三組數據
X1, y1 = make_circles(n_samples=100, factor=0.6, noise=0.05)
X2, y2 = make_blobs(n_samples=100, n_features=2, centers=[[1.2, 1.2]],
                    cluster_std=[[0.1]], random_state=9)
X = np.concatenate((X1, X2))
print len(X)
# plt.scatter(X[:, 0], X[:, 1], marker='o')
# plt.show()

# from sklearn.cluster import KMeans

# y_pred = KMeans(n_clusters=3, random_state=9).fit_predict(X)
# plt.scatter(X[:, 0], X[:, 1], c=y_pred)
# plt.show()

from sklearn.cluster import DBSCAN

y_pred = DBSCAN(eps = 0.1).fit_predict(X)
print y_pred
print len(y_pred)
# for i in range(len(y_pred)):
#     print y_pred[i]

plt.scatter(X[:, 0], X[:, 1], c=y_pred)
plt.show()