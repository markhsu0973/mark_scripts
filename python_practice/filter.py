#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import numpy as np
from matplotlib import pyplot as plt
plt.figure(figsize = (20,8))

s = np.random.normal(0,25,400)
plt.plot(s,label = 'bef')
mean = []
n = 4     #一次采样的次数
for i in range(int(len(s)/n)):
    select_s = s[i*n:(i+1)*n]     #切片选取一次采样的个数
    mean_s = np.mean(select_s)
    for j in range(n):       #将取到的值都赋值为平均值，方便画图体现，实际中可以只要一次值
        mean.append(mean_s)

plt.plot(mean,label = 'aft')
plt.title('fil')
plt.legend()
plt.show()