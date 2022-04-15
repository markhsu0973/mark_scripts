#! /usr/bin/env python
# -*- coding: UTF-8 -*-
###最小二乘法试验###
import numpy as np
from scipy.optimize import leastsq
import math

def compute_angle(pt1, pt2, pt3):
    dif_x = pt2[0] - pt1[0]
    dif_y = pt2[1] - pt1[1]
    tag_ori_1 = math.atan2(dif_y, dif_x)
    dif_x = pt3[0] - pt2[0]
    dif_y = pt3[1] - pt2[1]
    tag_ori_2 = math.atan2(dif_y, dif_x)
    tag_ori = tag_ori_2 - tag_ori_1
    tag_ori = tag_ori * 57.3
    return tag_ori

###采样点(Xi,Yi)###
# Xi=np.array([8.19,2.72,6.39,8.71,4.7,2.66,3.78])
# Yi=np.array([7.01,2.78,6.47,6.71,4.1,4.23,4.05])
# Xi=np.array([8.19,2.72,6.39])
# Yi=np.array([7.01,2.78,6.47])
# Xi=np.array([1,2,3,4,5,6,7,8,9,10])
# Yi=np.array([1,2.1,3,4.1,5,6,7.1,8,9,10])
# Xi=np.array([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19])
# Yi=np.array([1,2.1,3,4.1,5,6,7.1,8,9,10,9,8,6.9,6,5.1,3.9,3,2.1,1])
Xi_ori = np.array([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19])
Yi_ori=np.array([1,2.1,3,4.1,5,6,7.1,8,9,10,9,8,6.9,6,5.1,3.9,3,2.1,1])
Xi = np.array([])
Yi = np.array([])
Xi_2 = np.array([])
Yi_2 = np.array([])
find_corner = False
for i in range(len(Xi_ori)):
    if i < len(Xi_ori)-2:
        if not find_corner:
            pt3 = [Xi_ori[i+2], Yi_ori[i+2]]
            pt2 = [Xi_ori[i+1], Yi_ori[i+1]]
            pt1 = [Xi_ori[i], Yi_ori[i]]
            theta = compute_angle(pt1, pt2, pt3)
            Xi = np.append(Xi, Xi_ori[i])
            Yi = np.append(Yi, Yi_ori[i])
            if abs(theta) > 60:
                find_corner = True
        else:
            Xi_2 = np.append(Xi_2 , Xi_ori[i])
            Yi_2 = np.append(Yi_2, Yi_ori[i])
    else:
        Xi_2 = np.append(Xi_2 , Xi_ori[i])
        Yi_2 = np.append(Yi_2, Yi_ori[i])



#需要拟合的函数func及误差error###
def func(p,x):
    k,b=p
    return k*x+b

def error(p,x,y):
    # print s
    return func(p,x)-y #x、y都是列表，故返回值也是个列表

#TEST
p0=[100,2]
#print( error(p0,Xi,Yi) )

###主函数从此开始###
s="Test the number of iteration" #试验最小二乘法函数leastsq得调用几次error函数才能找到使得均方误差之和最小的k、b
Para=leastsq(error,p0,args=(Xi,Yi)) #把error函数中除了p以外的参数打包到args中
k1,b1=Para[0]
# print"k=",k,'\n',"b=",b
print "lift side: y =", k1 ,"x +", b1 

Para=leastsq(error,p0,args=(Xi_2,Yi_2)) #把error函数中除了p以外的参数打包到args中
k2,b2=Para[0]
# print"k=",k,'\n',"b=",b
print "right side: y =", k2, "x +", b2 

corner_x = ((b2 - b1) / (k1 - k2))
corner_y = k1 * corner_x + b1
corner = [corner_x, corner_y]
print "corner = ", corner

corner_theta = math.atan((k1 - k2) / (1 + k1 * k2)) 
print "corner theta = ", corner_theta* 57.3
print "left side line theta = ", math.atan(k1)* 57.3
print "right side line theta = ", math.atan(k2)* 57.3

corner_side_theta = (abs(math.atan(k1)) + abs(math.atan(k2)))/2
docking_heading = -(math.pi - corner_side_theta - (corner_theta/2))
print "docking_heading = ", docking_heading* 57.3


###绘图，看拟合效果###
import matplotlib.pyplot as plt

plt.figure(figsize=(8,6))
plt.scatter(Xi,Yi,color="blue",label="Left Side Point",linewidth=3) #画样本点
plt.scatter(Xi_2,Yi_2,color="red",label="Right Side Point",linewidth=3) #画样本点
plt.scatter(corner_x ,corner_y,color="black",label="Corner",linewidth=10) #画样本点
plt.quiver(corner_x, corner_y, math.cos(docking_heading), math.sin(docking_heading), color='g', width=0.005, scale=5) 
x=np.linspace(0,20,1000)
y1=k1*x+b1
y2=k2*x+b2
plt.plot(x,y1,color="cyan",label="Left Side Line",linewidth=2) #画拟合直线
plt.plot(x,y2,color="pink",label="Right Side Line",linewidth=2) #画拟合直线
plt.legend()
plt.show()