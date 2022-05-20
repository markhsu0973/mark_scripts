#! /usr/bin/env python
# -*- coding: UTF-8 -*-

import math

def compute_dist(pt1, pt2):
    dif_x = pt2[0] - pt1[0]
    dif_y = pt2[1] - pt1[1]
    return math.sqrt(dif_x * dif_x + dif_y * dif_y)

def compute_angle(pt1, pt2):
    dif_x = pt2[0] - pt1[0]
    dif_y = pt2[1] - pt1[1]
    tag_ori = math.atan2(dif_y, dif_x)
    return tag_ori

def generate_point(A, B, P, d):
    Projection_theta = compute_angle(A, P) - compute_angle(A, B)
    Projection_length = compute_dist(A, P) * math.cos(Projection_theta)
    P_P = [round((Projection_length * math.cos(compute_angle(A, B) + A[0])), 2), round((Projection_length * math.sin(compute_angle(A, B) + A[1])), 2)]
    C = [round((P_P[0] + d * math.cos(compute_angle(P, P_P))), 2), round((P_P[1] + d * math.sin(compute_angle(P, P_P))), 2)]
    return C

A = [0, 0]
B = [10, 0]
P = [1, 1]
d = 1
print generate_point(A, B, P, d)