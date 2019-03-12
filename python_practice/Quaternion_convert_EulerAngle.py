#!/usr/bin/python
import math
import sys
import rospy
import tf
import geometry_msgs.msg

# x = input('x = ')
# y = input('y = ')
# z = input('z = ')
# w = input('w = ')
# (trans,rot) = listener.lookupTransform('/turtle2', '/turtle1', rospy.Time(0))
# yaw = math.atan2(2*w*z + 2*x*y, 1 - 2*y*y - 2*z*z) * 57.3
# pitch = math.asin(2*w*y - 2*z*x) * 57.3
# roll = math.atan2(2*w*x + 2*y*z, 1 - 2*x*x - 2*y*y) * 57.3
#
# if yaw < 0:
#     yaw = yaw + 360
#
# if yaw > 360:
#     yaw = yaw - 360
#
# if pitch < 0:
#     pitch = pitch + 360
#
# if pitch > 360:
#     pitch = pitch - 360
#
# if roll < 0:
#     roll = roll + 360
#
# if roll > 360:
#     roll = roll - 360
#
# print "yaw = ",  yaw
# print "pitch = ",  pitch
# print "roll = ",  roll
(trans,rot) = listener.lookupTransform('/base_link', '/map', rospy.Time(0))