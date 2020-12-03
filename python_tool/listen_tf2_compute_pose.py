#!/usr/bin/env python 
import roslib
import rospy
import math
import tf2_ros

if __name__ == '__main__':
    rospy.init_node('listen_tf2_compute_pose')

    tfBuffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(tfBuffer)

    pub_num = 0
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            trans = tfBuffer.lookup_transform('map', 'base_link', rospy.Time(0))
        except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
            continue

        #compue euler angle
        x = trans.transform.rotation.x
        y = trans.transform.rotation.y
        z = trans.transform.rotation.z
        w = trans.transform.rotation.w

        yaw = math.atan2(2*w*z + 2*x*y, 1 - 2*y*y - 2*z*z) * 57.3
        pitch = math.asin(2*w*y - 2*z*x) * 57.3
        roll = math.atan2(2*w*x + 2*y*z, 1 - 2*x*x - 2*y*y) * 57.3

        if yaw < 0:
            yaw = yaw + 360

        if yaw > 360:
            yaw = yaw - 360

        if pitch < 0:
            pitch = pitch + 360

        if pitch > 360:
            pitch = pitch - 360

        if roll < 0:
            roll = roll + 360

        if roll > 360:
            roll = roll - 360
        ##
        print '----------'
        print 'Position :'
        print '  x:    ', trans.transform.translation.x
        print '  y:    ', trans.transform.translation.y
        print '  z:    ', trans.transform.translation.z
        print 'Euler angle :'
        print '  yaw:  ', yaw
        print '  roll: ', roll
        print '  pitch:', pitch

        rate.sleep()