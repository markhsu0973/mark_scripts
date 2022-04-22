#!/usr/bin/env python
# -*- coding: utf-8 -*-
import cv2
import numpy as np

def fill_color_demo(image, pt):
    copyIma = image.copy()
    h, w = image.shape[:2]
    mask = np.zeros([h+2, w+2], np.uint8)
    cv2.floodFill(copyIma, mask, (pt[0], pt[1]), (125, 125, 125), (25, 25, 25), (12, 12, 12), cv2.FLOODFILL_FIXED_RANGE)  
    img2 = np.zeros([h, w], np.uint8)
    result = np.where(copyIma == 125)
    listOfCoordinates= list(zip(result[0], result[1]))
    for cord in listOfCoordinates:
        img2[cord[0],cord[1]] = 255
    return img2

def ImageAddition(self, img1,img2):
    result = np.where(img2 == 0)
    listOfCoordinates= list(zip(result[0], result[1]))
    for cord in listOfCoordinates:
        img1[cord[0],cord[1]] = img2[cord[0],cord[1]] 

    return img1
# end of ImageAddition(img1,img2)
free_space = [1136, 2318]
img1 = cv2.imread('Forbidden_and_virtual_wall_original.pgm', 0)
img2 = fill_color_demo(img1, free_space)
cv2.imwrite('floodFill.pgm', img2)