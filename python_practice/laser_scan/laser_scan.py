#!/usr/bin/env python 

import rospy
import roslib
import tf 
from sensor_msgs.msg import LaserScan
from scan_qsr.scan_protector import scan_protector as scan_sub
from geometry_msgs.msg import PointStamped

def callback(msg):
#	print msg.header.frame_id

	
#	for i in range(len(msg.ranges)):
#		angle = msg.angle_min + (i * msg.angle_increment)
#		print("angle: ", angle*57.3, "range: ", msg.ranges[i]) 
	data_intensity_filter =[]
	laser_data =[]
	newdata = msg
	newdata.ranges = list(msg.ranges)
	newdata.intensities = list(msg.intensities)
	listener = tf.TransformListener()
	listener.waitForTransform("/base_link", "/front_laser", rospy.Time(0), rospy.Duration(4.0))
	for i in range (len(msg.ranges)):
		laser_data =[]
		angle = msg.angle_min + (i * msg.angle_increment)
		laser_data.append(msg.ranges[i]*math.cos(angle))
		laser_data.append(msg.ranges[i]*math.sin(angle))
		laser_data.append(angle)
		data_intensity_filter.append(laser_data)
		if angle >= 0:
			newdata.ranges[i] = 1
		else:
			newdata.ranges[i] = 6
		newdata.intensities[i] = 2
		
#	transfor to base_link
	laser_point=PointStamped()
	laser_point.header.frame_id = msg.header.frame_id
	laser_point.header.stamp =rospy.Time(0)
	laser_point.point.x=0.0
	laser_point.point.y=0.0
	laser_point.point.z=0.0
	p = listener.transformPoint("base_link",laser_point)
	print("x: ", p.point.x, "y: ", p.point.y)


rospy.init_node('laser_scan_values')
sub = rospy.Subscriber('/front_scan', LaserScan, callback)
#scan_step = rospy.get_param('~scan_step', 10)
#scan_f = scan_sub("front_scan_original", step = scan_step, is_stage = True)
#print scan_f

rospy.spin()
