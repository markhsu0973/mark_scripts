#!/usr/bin/python
# -*- coding: utf-8 -*-
import numpy as np
myArray = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
newArray1 = myArray[myArray < 6] # Line 1
newArray2 = myArray[myArray % 2 == 0] # Line 2
newArray3 = myArray[myArray % 2 != 0] # Line 3
newArray4 = myArray[np.logical_and(myArray > 1, myArray < 5)] # Line 4
newArray5 = myArray[np.logical_or(myArray % 2 == 0, myArray < 5)] # Line 5
print(myArray)
print(newArray1)
print(newArray2)
print(newArray3)
print(newArray4)
print(newArray5)