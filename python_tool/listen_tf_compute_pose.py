#!/usr/bin/env python 
import rospy
import math
import tf

if __name__ == '__main__':
    rospy.init_node('listen_tf_compute_pose')

    listener = tf.TransformListener()


    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans, rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue
        ##compue euler angle
        x = rot[0]
        y = rot[1]
        z = rot[2]
        w = rot[3]

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
        print '  x:    ', trans[0]
        print '  y:    ', trans[1]
        print '  z:    ', trans[2]
        print 'Euler angle :'
        print '  yaw:  ', yaw
        print '  roll: ', roll
        print '  pitch:', pitch

        rate.sleep()