#!/usr/bin/env python
# -*- coding: utf-8 -*-
import math
import numpy as np

def med_avg_filter(data, num):
    data.sort()
    print data
    # print len(data)
    if (len(data) / 2)%2:
        median = len(data) / 2
    else:
        median = len(data) / 2 + 1
        print data[median]
    sum  = data[median]
    print "median = ", median
    for i in range(num):
        sum  =  sum  + data[median -i - 1]
        print "median -i - 1 = ", median -i - 1
        print "data[median -i - 1] = ", data[median -i - 1]
        print "sum  = ", sum 
        sum  = sum  + data[median + i + 1]
        print "median +i + 1 = ", median +i + 1
        print "data[median +i + 1] = ", data[median +i + 1]
        print "sum  = ", sum 
    return  sum  / (num *2  +1)

a = [1.1, 1.2, 1.3, 1.1, 1.0, 1.2, 1.4, 5.0, 6.0, 1.5,1.2]


# print np.median(a)
print med_avg_filter(a, 2)