#!/usr/bin/env python
# -*- coding: utf-8 -* 
import rospy
from ar_track_alvar_msgs.msg import AlvarMarkers
from geometry_msgs.msg import Twist
from math import copysign
import math
import time
import numpy as np
class ARFollower():
    def __init__(self):
        rospy.init_node("ar_follower")
        rospy.on_shutdown(self.shutdown)
        self.rate = rospy.get_param("~rate", 10)
        r = rospy.Rate(self.rate)
        self.tag_id = rospy.get_param("~tag_id", 98) 
        self.lens_offest = rospy.get_param("~lens_offest", -0.0325)
        self.target_visible = False
        self.stop_tracking = False
        rospy.loginfo("Waiting for dock_task/ar_pose_marker topic...")
        rospy.wait_for_message('dock_task/ar_pose_marker', AlvarMarkers)
        rospy.Subscriber('dock_task/ar_pose_marker', AlvarMarkers, self.set_cmd_vel)
        rospy.loginfo("Marker messages detected. Starting follower...")

        self.sample_cnt = 0
        self.sample_size = 20
        self.tag_orientation_list = [0] * self.sample_size
        while (not self.stop_tracking):
            r.sleep()
    # end of __init__(self)

    def set_cmd_vel(self, msg):

        try:
            marker = msg.markers[0]
            if not self.target_visible:
                rospy.loginfo("artag detected")
            self.target_visible = True
        except:
            if self.target_visible:
                rospy.loginfo("artag not detected")
            marker = False
            return
        if self.target_visible:
            x = marker.pose.pose.orientation.x 
            y = marker.pose.pose.orientation.y 
            z = marker.pose.pose.orientation.z 
            w = marker.pose.pose.orientation.w

            yaw = math.atan2(2*w*z + 2*x*y, 1 - 2*y*y - 2*z*z) * 57.3
            pitch = math.asin(2*w*y - 2*z*x) * 57.3
            roll = math.atan2(2*w*x + 2*y*z, 1 - 2*x*x - 2*y*y) * 57.3

            rospy.logwarn("yaw = %f", yaw)
            rospy.logwarn("pitch = %f", pitch)
            rospy.logwarn("roll = %f", roll)

    # end of set_cmd_vel(self, msg)

    def shutdown(self):
        rospy.loginfo("Stopping the robot...")
        self.stop_tracking = True
        rospy.sleep(1)
    # end of shutdown(self)

if __name__ == '__main__':
    try:
        ARFollower()
        # rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("AR follower node terminated.")
