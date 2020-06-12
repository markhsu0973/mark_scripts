#!/usr/bin/env python

from __future__ import print_function
import sys
import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String
from sensor_msgs.msg import PointCloud2 as pc2
from sensor_msgs import point_cloud2
from laser_geometry import LaserProjection
import tf
import tf.msg
from geometry_msgs.msg import PointStamped
class DoFilter2PC:
    def __init__(self):
        self.laserProj = LaserProjection()
        self.sub = rospy.Subscriber("front_scan", LaserScan, self.callback)
        self.pub = rospy.Publisher("front_scan_filt", LaserScan, queue_size=10)
        self.pcPub = rospy.Publisher("/laserPointCloud", pc2, queue_size=1)

    def callback(self, data):

        newdata = data
        newdata.ranges = list(data.ranges)
        newdata.intensities = list(data.intensities)
        listener = tf.TransformListener()
        listener.waitForTransform("/base_link", "/front_laser", rospy.Time(0), rospy.Duration(4.0))
        for i in range (len(data.ranges)):
            angle = data.angle_min + (i * data.angle_increment)
            if angle >= 0:
                newdata.ranges[i] = 1
            else:
                newdata.ranges[i] = 6
            newdata.intensities[i] = 2
        cloud_out = self.laserProj.projectLaser(newdata)
        self.pcPub.publish(cloud_out)
        self.pub.publish(newdata)
        laser_point=PointStamped()
        laser_point.header.frame_id = "base_link"
        laser_point.header.stamp =rospy.Time(0)
        laser_point.point.x=1.0
        laser_point.point.y=1.0
        laser_point.point.z=0.0
        p = listener.transformPoint("front_laser",laser_point)
        pp = listener.transformPointCloud("front_laser",cloud_out)
#        print (p.point.x)
#        rospy.loginfo(data)


if __name__ == '__main__':

    # Initialize
    rospy.init_node('LidarFilter', anonymous=False)
    lidar = DoFilter2PC()

    rospy.spin()
