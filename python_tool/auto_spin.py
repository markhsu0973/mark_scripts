#!/usr/bin/env python
import rospy
import time
import sys
from geometry_msgs.msg import Twist

def auto_spin():
    count = 0
    cmd = Twist()
    cmd.linear.x = 0.0
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    spin_speed = float(sys.argv[1])
    cmd.angular.z = spin_speed
    count_threshold_1 = int(sys.argv[2]) * 2
    count_threshold_2 = int(sys.argv[3]) * 2

    while not rospy.is_shutdown():
        while count < count_threshold_1:
            cmd.angular.z = 0
            pub.publish(cmd)
            count = count +1
            time.sleep(0.5)
        count = 0

        while count < count_threshold_2:
            cmd.angular.z = spin_speed
            pub.publish(cmd)
            count = count +1
            time.sleep(0.5)
        count = 0


if __name__ == "__main__":
    rospy.init_node('auto_spin_node')
    try:
        auto_spin()
    except rospy.ROSInterruptException, e:
        rospy.loginfo ("'auto_spin' cannot launch.")
        rospy.loginfo(e)
        pass