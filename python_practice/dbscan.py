#!/usr/bin/python
# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs, make_circles

# 下面我們生成三組數據
X1, y1 = make_circles(n_samples=100, factor=0.6, noise=0.05)
X2, y2 = make_blobs(n_samples=100, n_features=2, centers=[[1.2, 1.2]],
                    cluster_std=[[0.1]], random_state=9)
# print y1
X = np.concatenate((X1, X2))
# print type(X)
# print X
# print len(X)
# plt.scatter(X[:, 0], X[:, 1], marker='o')
# plt.show()

# from sklearn.cluster import KMeans

# y_pred = KMeans(n_clusters=3, random_state=9).fit_predict(X)
# plt.scatter(X[:, 0], X[:, 1], c=y_pred)
# plt.show()

from sklearn.cluster import DBSCAN

y_pred = DBSCAN(eps = 0.1).fit_predict(X)
# print type(y_pred)
# print y_pred
# print len(y_pred)
p = y_pred.tolist()
# print type(p)
# for i in p:
#     print i
# for i in y_pred:
    # print i
max_class_number = max(y_pred)
for i in (-1, max_class_number):
    if i != -1:
        np_temp = np.array([])
        for j in range(len(y_pred)):
            if y_pred[j] == i:
                if np_temp.size == 0:
                    np_temp = np.append(np_temp, X[j])
                else:
                    np_temp = np.vstack([np_temp,X[j]])
        # print np_temp

# print np_temp
plt.scatter(X[:, 0], X[:, 1], c=y_pred)
plt.show()

plt.scatter(np_temp[:, 0], np_temp[:, 1], marker='o')
plt.show()