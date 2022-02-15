#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2

img1 = cv2.imread('/home/mark/img_ts/map.pgm',0) 
img2 = cv2.imread('/home/mark/img_ts/Forbidden_zone.pgm',0)
img3 = cv2.imread('/home/mark/img_ts/virtual_wall.pgm',0) 

def ImageAddition(img1,img2):

    result = np.where(img2 == 0)
    listOfCoordinates= list(zip(result[0], result[1]))
    for cord in listOfCoordinates:
        img1[cord[0],cord[1]] = img2[cord[0],cord[1]] 

    # result = np.where(img2 == 254)
    # listOfCoordinates= list(zip(result[0], result[1]))
    # for cord in listOfCoordinates:
    #     img1[cord[0],cord[1]] = img2[cord[0],cord[1]] 

    return img1


Image_ = ImageAddition(img2, img3)
Image_ = ImageAddition(img1, Image_)
cv2.imwrite('Forbidden_and_virtual_wall.pgm', Image_)