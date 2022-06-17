#! /usr/bin/env python
# -*- coding: UTF-8 -*-
###最小二乘法试验###
import numpy as np
from scipy.optimize import leastsq
import math
import matplotlib.pyplot as plt

#需要拟合的函数func及误差error###
def func(p,x):
    k,b=p
    return k*x+b

def error(p,x,y):
    # print s
    return func(p,x)-y #x、y都是列表，故返回值也是个列表

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
X_ori = np.array([[1,0.5],[2,1],[3,2.1],[4,3],[5,4.1],[6,5],[7,6],[8,7.1],[9,8],[10,9],[11,10],[12,9],[13,8],[14,6.9],[15,6],[16,5.1],[17,3.9],[18,3],[19,2.1],[20,1]])
X = np.array([])
X2 = np.array([])
find_corner = False
for i in range(len(X_ori)):
    if i < len(X_ori)-2:
        if not find_corner:
            pt3 = [X_ori[i+2,0], X_ori[i+2,1]]
            pt2 = [X_ori[i+1,0], X_ori[i+1,1]]
            pt1 = [X_ori[i,0], X_ori[i,1]]
            theta = compute_angle(pt1, pt2, pt3)
            if X.size == 0:
                X = np.append(X, X_ori[i])
            else:
                X = np.vstack([X,X_ori[i]])
            if abs(theta) > 60:
                find_corner = True
        else:
            if X2.size == 0:
                X2 = np.append(X2, X_ori[i])
            else:
                X2 = np.vstack([X2,X_ori[i]])
    else:
        if X2.size == 0:
            X2 = np.append(X2, X_ori[i])
        else:
            X2 = np.vstack([X2,X_ori[i]])

plt.scatter(X[:, 0], X[:, 1],color="blue",label="Left Side Point",linewidth=3) #画样本点
plt.scatter(X2[:, 0], X2[:, 1],color="red",label="Right Side Point",linewidth=3) #画样本点
plt.show()

if X.size > 0 and X2.size > 0:
    #TEST
    p0=[100,2]
    #print( error(p0,Xi,Yi) )

    ###主函数从此开始###
    s="Test the number of iteration" #试验最小二乘法函数leastsq得调用几次error函数才能找到使得均方误差之和最小的k、b
    Para=leastsq(error,p0,args=(X[:,0],X[:,1])) #把error函数中除了p以外的参数打包到args中
    k1,b1=Para[0]
    # print"k=",k,'\n',"b=",b
    print "lift side: y =", k1 ,"x +", b1 

    Para=leastsq(error,p0,args=(X2[:,0],X2[:,1])) #把error函数中除了p以外的参数打包到args中
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


    plt.figure(figsize=(8,6))
    plt.scatter(X[:, 0], X[:, 1],color="blue",label="Left Side Point",linewidth=3) #画样本点
    plt.scatter(X2[:, 0], X2[:, 1],color="red",label="Right Side Point",linewidth=3) #画样本点
    plt.scatter(corner_x ,corner_y,color="black",label="Corner",linewidth=10) #画样本点
    plt.quiver(corner_x, corner_y, math.cos(docking_heading), math.sin(docking_heading), color='g', width=0.005, scale=5) 
    x=np.linspace(0,20,1000)
    y1=k1*x+b1
    y2=k2*x+b2
    plt.plot(x,y1,color="cyan",label="Left Side Line",linewidth=2) #画拟合直线
    plt.plot(x,y2,color="pink",label="Right Side Line",linewidth=2) #画拟合直线
    plt.legend()
    plt.show()