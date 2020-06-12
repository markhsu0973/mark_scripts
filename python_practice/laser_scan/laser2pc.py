#!/usr/bin/env python
import rospy
from sensor_msgs.msg import PointCloud2 as pc2
from sensor_msgs import point_cloud2
from sensor_msgs.msg import LaserScan
from laser_geometry import LaserProjection
import time

class Laser2PC():
    def __init__(self):
        self.laserProj = LaserProjection()
        self.pcPub = rospy.Publisher("/laserPointCloud", pc2, queue_size=1)
        self.laserSub = rospy.Subscriber("/front_scan", LaserScan, self.laserCallback)

    def laserCallback(self,data):

        cloud_out = self.laserProj.projectLaser(data)

        self.pcPub.publish(cloud_out)
        gen = point_cloud2.read_points(cloud_out, field_names=("x", "y", "z"), skip_nans=True)
        time.sleep(1)
        print type(gen)
        for p in gen:
#            print " x : %.3f  y: %.3f  z: %.3f" %(p[0],p[1],p[2])
            print p
        
if __name__ == '__main__':
    rospy.init_node("laser2PointCloud")
    l2pc = Laser2PC()
    rospy.spin()
