#!/usr/bin/env python

import cv2
import numpy as np
from pyzbar.pyzbar import decode

img = cv2.imread('Dock_SN.png')

print len(decode(img))
for barcode in decode(img):
    myData = barcode.data.decode('utf-8')
    print(myData)
