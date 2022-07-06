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
        self.tag_1st_x = 0
        self.tag_1st_z = 0
        self.tag_1st_detected = False
        while (not self.stop_tracking):
            r.sleep()
    # end of __init__(self)

    def set_cmd_vel(self, msg):

        try:
            tag_id_1st_x_list = []
            tag_id_1st_z_list = []
            for ar_tag in msg.markers:
                detect_correct_id = False
                self.tag_1st_detected = False
                marker = ar_tag
                tag_1st_x = marker.pose.pose.position.x 
                tag_1st_z = marker.pose.pose.position.z
                tag_dis = math.sqrt(tag_1st_x * tag_1st_x + tag_1st_z * tag_1st_z)
                # print "tag_id = ", ar_tag.id, ", tag dis = ", tag_dis
                if ar_tag.id == int(98):
                    # print "update 1st"
                    self.tag_1st_detected = True
                    self.tag_1st_x = marker.pose.pose.position.x
                    self.tag_1st_z = marker.pose.pose.position.z
                    tag_id_1st_x_list.append(self.tag_1st_x)
                    tag_id_1st_z_list.append(self.tag_1st_z)
            # print len(tag_id_1st_x_list)

            if len(tag_id_1st_z_list) > 1:
                min_dis = 999
                for i in range(len(tag_id_1st_z_list)):
                    tag_d_x = tag_id_1st_x_list[i]
                    tag_d_z = tag_id_1st_z_list[i]
                    tag_dis = math.sqrt(tag_d_x * tag_d_x + tag_d_z * tag_d_z)
                    if tag_dis < min_dis:
                        min_dis = tag_dis
                        self.tag_1st_x = tag_d_x
                        self.tag_1st_z = tag_d_z
                        # print self.tag_1st_x
            if self.tag_1st_detected:
                print self.tag_1st_x
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
