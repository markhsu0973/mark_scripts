#! /usr/bin/env python

import rospy
import math
import csv
import numpy as np
from sensor_msgs.msg import LaserScan

sample_cnt = 0
sample_size = 200
sample = [0] * sample_size
def callback(msg):
    global sample_cnt
    rad2deg = (180 / math.pi)
    angle = 0
    angle_index = (angle / rad2deg - msg.angle_min) / msg.angle_increment
    
    if sample_cnt < sample_size:
    	sample[sample_cnt] = msg.ranges[int(angle_index)]

    else:
    	sample[sample_cnt % sample_size] = 	msg.ranges[int(angle_index)]

#    for z in range(sample_size):
#    	print z, "= ", sample[z]

    if sample_cnt == sample_size:
    	with open('3m_0deg_scan_output.csv', 'w') as csvfile:
	    	writer = csv.writer(csvfile)
	    	for k in range(sample_size):
	    		writer.writerow([sample[k]])
    	print "Write CSV!"
    sample_cnt = sample_cnt + 1

rospy.init_node('scan_values')
sub = rospy.Subscriber('scan', LaserScan, callback)
rospy.spin()