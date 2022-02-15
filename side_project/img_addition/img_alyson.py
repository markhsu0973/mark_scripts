#!/usr/bin/env python
# -*- coding: utf-8 -*-
#################################################
# Author：Alyson Chen <alyson_chen@wistron.com> #
# Date : 2022.01.18                             #
#################################################
import numpy as np
import cv2
from matplotlib import pyplot as plt
#from tqdm import tqdm 

MIN_MATCH_COUNT = 10

img1 = cv2.imread('/home/alyson/catkin_ws/src/test_map/map/6/map_1.pgm',0) 
img2 = cv2.imread('/home/alyson/catkin_ws/src/test_map/map/6/map_2.pgm',0) 

def stitchImages(img1,img2):
    # Initiate AKAZE detector
    AKAZE = cv2.AKAZE_create()

    # find the keypoints and descriptors with AKAZE
    kp1, des1 = AKAZE.detectAndCompute(img1,None)
    kp2, des2 = AKAZE.detectAndCompute(img2,None)


    FLANN_INDEX_KDTREE = 0
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
    search_params = dict(checks = 50)

    dis_matcher = cv2.BFMatcher(cv2.NORM_HAMMING)
    matches = dis_matcher.knnMatch(des1, des2, k=2)

    # store all the good matches as per Lowe's ratio test.
    good = []
    for m,n in matches:# for every descriptor, take closest two matches
        if m.distance < 0.7*n.distance: # best match has to be this much closer than second best
            good.append(m)

    if len(good)>MIN_MATCH_COUNT:
        src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
        dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)
   
        M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
        matchesMask = mask.ravel().tolist()

        h,w = img1.shape
        pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
        dst = cv2.perspectiveTransform(pts,M)
    
        #img2 = cv2.polylines(img2,[np.int32(dst)],True,255,3, cv2.LINE_AA) #draw Homograph
        dst = cv2.warpPerspective(img1,M,(img1.shape[1] + img2.shape[1], img1.shape[0]+ img2.shape[0]),
                                          flags = cv2.INTER_CUBIC, borderMode=cv2.BORDER_CONSTANT, 
                                          borderValue = [205, 205, 205, 205]) #make background gray
        print("[Alyson Debug] Stitching images... take a sweet time.....")
        for i in range(img2.shape[0]):
            for j in range(img2.shape[1]):
                if(img2[i][j]==254 or img2[i][j]==0): #Black=0,Gray=205,white=254
                    dst[i,j] = img2[i,j] 
                j=j+1
            i=j+1 
        #cv2.imwrite('stitchImage_.pgm', dst)
        return dst
    else:
        print "[Alyson Debug] Not enough matches are found - %d/%d" % (len(good),MIN_MATCH_COUNT)
        matchesMask = None

    draw_params = dict(matchColor = (0,255,0), # draw matches in green color
            singlePointColor = None,
            matchesMask = matchesMask, # draw only inliers
            flags = 2)
    #print("[Alyson Debug] kp1 =",len(kp1))
    #print("[Alyson Debug] kp2 =",len(kp2))
    #print("[Alyson Debug] matches =",len(matches))
    #print("[Alyson Debug] good =",len(good))
    #print("[Alyson Debug] inliers/matches =",len(good)/len(matches))
    #print("[Alyson Debug] M =",M)
    #img3 = cv2.drawMatches(img1,kp1,img2,kp2,good,None,**draw_params) #matches with two pictures
    return 0

def cropImage(img):
    print("[Alyson Debug] Croping images... take a sweet time.....")
    AKAZE = cv2.AKAZE_create()  
    kp1, des1 = AKAZE.detectAndCompute(img,None)
    x=[]
    y=[]
    for i in range(len(kp1)):
        x.append(kp1[i].pt[0])
        y.append(kp1[i].pt[1])
        i=i+1
    x.sort()
    y.sort()
    (x1,x2,y1,y2)=(int(x[0]),int(x[-1]),int(y[0]),int(y[-1]))
    crop_img=cv2.circle(img,(x1, y1), 15, (0, 0, 0), -1)
    crop_img=cv2.circle(img,(x1, y2), 15, (0, 0, 0), -1)
    crop_img=cv2.circle(img,(x2, y1), 15, (0, 0, 0), -1)
    crop_img=cv2.circle(img,(x2, y2), 15, (0, 0, 0), -1)

    crop_img = img[y1:y2, x1:x2]
    cv2.imwrite('cropImage_.pgm', crop_img)
    return crop_img

stitchImage_ = stitchImages(img1,img2)
cropImage_ = cropImage(stitchImage_)