#!/usr/bin/env python 
import rospy
import math
import tf
import tf.msg
import geometry_msgs.msg
from sensor_msgs.msg import LaserScan
from scan_qsr.scan_protector import scan_protector as scan_sub
from geometry_msgs.msg import PointStamped
import pcl

def callback(msg):
    rate = rospy.Rate(10.0)
    listener = tf.TransformListener()

#    listener.waitForTransform("/base_link", "/front_laser", rospy.Time(0), rospy.Duration(4.0))
#    (trans, rot) = listener.lookupTransform('/base_link', '/front_laser', rospy.Time(0))

        
#    laser scan convert to point stamp
    for i in range(len(msg.ranges)):
        angle = msg.angle_min + (i * msg.angle_increment)
#        print("angle: ", angle*57.3, "range: ", msg.ranges[i])
#        point = PointStamped()
#        point.header = msg.header
#        point.point.x = msg.ranges[i] * math.cos(angle)
#        point.point.y = msg.ranges[i] * math.sin(angle)
#        point.point.z = 0
        print("angle: ", angle*57.3, "range: ", msg.ranges[i])
#        tr_range = listener.transformPoint("base_link", point)
#        print ("trans range= ", tr_range)


if __name__ == '__main__':
    rospy.init_node('listen_tf_compute_pose')

    listener = tf.TransformListener()
    listener.waitForTransform("/base_link", "/front_laser", rospy.Time(0), rospy.Duration(4.0))
    (trans_f, rot_f) = listener.lookupTransform('/base_link', '/front_laser', rospy.Time(0))
    print("trans_f = ", trans_f, "rot_f=", rot_f)
    sub = rospy.Subscriber('/front_scan', LaserScan, callback)
    rospy.spin()

