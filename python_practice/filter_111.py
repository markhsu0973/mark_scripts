#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math
from matplotlib import pyplot as plt 

def med_avg_filter(data, num):
    data.sort()
    median = math.ceil(len(data) / 2)
    sum  = data[median]
    for i in range(num):
        sum  =  sum  + data[median -i - 1]
        sum  = sum  + data[median + i + 1]
    return  sum  / (num *2  +1)
# end of med_avg_filter(self, data, num)


def ShakeOff(data,N):
    usenum = data[0]
    i = 0 
    for index,tmp in enumerate(data):
        if tmp != usenum:
            i = i + 1
            if i >= N:
                i = 0
                data[index] = usenum
	return data

# s = np.random.normal(0,25,15)
s=np.random.random_sample((15,))
plt.plot(s,label = '1')
mean = []
n = 7     
for i in range(int(len(s)/n)):
    select_s = s[i*n:(i+1)*n]     
    mean_s = np.mean(select_s)
    for j in range(n):       
        mean.append(mean_s)
print("raw data mean = ", np.mean(s))
print("算术平均滤波法 mean = ", np.mean(mean))

a = 0.3    
list_s = []
for i in range(len(s)-1):
    s[i+1] = (1-a) * s[i+1] + a * s[i]
    list_s.append(s[i+1])

sss = ShakeOff(s,6)
print("消抖滤波法 mean = ",np.mean(sss))
print("一阶滞后滤波法  mean = ",np.mean(list_s))
plt.plot(mean,label = '2')
plt.plot(sss,label = '3')
plt.plot(list_s,label = '4')
mean = []
n = 7     
for i in range(int(len(s)/n)):
    select_s = s[i*n:(i+1)*n]    
    select_s = sorted(select_s)
    select_s.remove(select_s[0])
    select_s.remove(select_s[-1])

    mean_s = np.mean(select_s)
    for j in range(n):      
        mean.append(mean_s) 
print("中位值平均滤波法 mean = ",np.mean(mean))
# print("mark_filter = ", med_avg_filter(s, 5))
plt.plot(mean,label = '5')
plt.title('3')
plt.legend()
plt.show() 
