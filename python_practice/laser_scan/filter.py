#!/usr/bin/env python

from __future__ import print_function
import sys
import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String

class DoFilter:
    def __init__(self):

        self.sub = rospy.Subscriber("front_scan", LaserScan, self.callback)
        self.pub = rospy.Publisher("front_scan_filt", LaserScan, queue_size=10)

    def callback(self, data):

        newdata = data
        newdata.ranges = list(data.ranges)
        newdata.intensities = list(data.intensities)

#        for x in range(120,240):
#            newdata.ranges[x]=0
#            newdata.intensities[x]=0

        #for x in range(90,270):
        #    newdata.ranges[x]=0
        #    newdata.intensities[x]=0

        #for x in range(30,330):
        #    newdata.ranges[x]=0
        #    newdata.intensities[x]=0
        
        for i in range (len(data.ranges)):
            angle = data.angle_min + (i * data.angle_increment)
            if angle >= 0:
                newdata.ranges[i] = 1
            else:
                newdata.ranges[i] = 6
            newdata.intensities[i] = 2
        
        self.pub.publish(newdata)
#        rospy.loginfo(data)


if __name__ == '__main__':

    # Initialize
    rospy.init_node('LidarFilter', anonymous=False)
    lidar = DoFilter()

    rospy.spin()
