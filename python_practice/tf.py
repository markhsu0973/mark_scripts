#!/usr/bin/env python
import rospy
import math
import tf
import geometry_msgs.msg

listener = tf.TransformListener()
#
#
#
# t = tf.getLatestCommonTime("/base_link", "/map")
# position, quaternion = self.tf.lookupTransform("/base_link", "/map", t)
# print position, quaternion