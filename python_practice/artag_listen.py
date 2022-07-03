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
            for ar_tag in msg.markers:
                detect_correct_id = False
                marker = ar_tag
                tag_1st_x = marker.pose.pose.position.x 
                tag_1st_z = marker.pose.pose.position.z
                tag_dis = math.sqrt(tag_1st_x * tag_1st_x + tag_1st_z * tag_1st_z)
                print "tag_id = ", ar_tag.id, ", tag dis = ", tag_dis
        except:
            return

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
