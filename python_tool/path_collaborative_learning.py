#!/usr/bin/env python
import threading, time, signal
import sys
import rospy
import time
import sys
from geometry_msgs.msg import Twist
from threading import *
import math
import tf
import tf.msg
import geometry_msgs.msg
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose2D
from std_msgs.msg import Int8
import csv

rad2deg = (180 / math.pi)

amr_pose = Pose2D
amr_pose_list_x = []
amr_pose_list_y = []
amr_pose_list_theta =[]

def amr_pose_compute():
    rate = rospy.Rate(10.0)
    listener = tf.TransformListener()
    while not rospy.is_shutdown():
        try:
            (trans, rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue
        x = rot[0]
        y = rot[1]
        z = rot[2]
        w = rot[3]
        
        amr_pose.x = trans[0]
        amr_pose.y = trans[1]
        amr_pose.theta = math.atan2(2*w*z + 2*x*y, 1 - 2*y*y - 2*z*z)
# end of amr_pose_compute()

def pose_callback(msg):
    if msg.data == 1:
        rospy.loginfo("Record AMR Pose")
        amr_pose_list_x.append(amr_pose.x)
        amr_pose_list_y.append(amr_pose.y)
        amr_pose_list_theta.append(amr_pose.theta)
    if msg.data == 2:
        rospy.loginfo("Start save to CSV")
        list_size = len(amr_pose_list_x)
        with open('nav_waypoint.csv', 'w') as csvfile:
	    	writer = csv.writer(csvfile)
	    	for k in range(list_size):
	    		writer.writerow([amr_pose_list_x[k], amr_pose_list_y[k], amr_pose_list_theta[k]])
        rospy.loginfo("Finish save to CSV")
        

# end of pose_callback(msg)

def quit(signum, frame):
    rospy.loginfo("### record_amr_pose_node stop ###")
    sys.exit()
# end of quit(signum, frame)

if __name__ == '__main__':
    rospy.init_node('path_collaborative_learning_node')
    rospy.loginfo("Start path_collaborative_learning_node")
    try:
        signal.signal(signal.SIGINT, quit)
        signal.signal(signal.SIGTERM, quit)
        rospy.Subscriber("record_amr_pose_msg", Int8, pose_callback)

        amr_pose_compute_thread = threading.Thread(target = amr_pose_compute)
        amr_pose_compute_thread.setDaemon(True)
        amr_pose_compute_thread.start()

        while True:
            pass
    except Exception, exc:
        print exc
