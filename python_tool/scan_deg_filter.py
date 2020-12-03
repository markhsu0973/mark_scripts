#! /usr/bin/env python

import rospy
import math

from sensor_msgs.msg import LaserScan


def callback(msg):
    global sample_cnt
    rad2deg = (180 / math.pi)
    angle = 0
    angle_index = (angle / (180 / math.pi) - msg.angle_min) / msg.angle_increment
    scan_filter = LaserScan()
    scan_filter.header.stamp = msg.header.stamp
    scan_filter.header.frame_id =msg.header.frame_id
    scan_filter.angle_min = msg.angle_min
    scan_filter.angle_max = msg.angle_max
    scan_filter.angle_increment = msg.angle_increment
    scan_filter.time_increment = msg.time_increment
    scan_filter.range_min = msg.range_min
    scan_filter.range_max = msg.range_max

    scan_filter.ranges = [0] * len(msg.ranges)
    scan_filter.ranges[int(angle_index)] = msg.ranges[int(angle_index)]
    scan_filter.intensities = msg.intensities

    scan_pub.publish(scan_filter)
    
    

rospy.init_node('scan_deg_filter')
sub = rospy.Subscriber('scan', LaserScan, callback)
scan_pub = rospy.Publisher('scan_deg_filter', LaserScan, queue_size=50)
rospy.spin()
