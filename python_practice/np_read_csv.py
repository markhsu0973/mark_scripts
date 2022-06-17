# -*- coding: utf-8 -*-

import numpy as np
import csv

with open("v_shape.csv") as file_name:
    file_read = csv.reader(file_name)
    array = list(file_read)
float_lst = np.float_(array)
print(float_lst)