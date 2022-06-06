#!/usr/bin/env python
import rospy
import time
import sys
from geometry_msgs.msg import Twist

def test_pogo_ping():
    cmd_vel_pub = rospy.Publisher('cmd_vel', Twist, queue_size=5)
    move_cmd = Twist()
    final_dis_cnt = 0.04 * 1000
    loop = 5
    localtime = time.localtime()
    result = time.strftime("%Y-%m-%d %I:%M:%S %p", localtime)
    rospy.logwarn("Start")
    rospy.logwarn(result)
    for i in range(loop):
        cnt = 0
        while (cnt <= final_dis_cnt):
            move_cmd.linear.x = -0.01
            move_cmd.angular.z = 0.0
            cmd_vel_pub.publish(move_cmd)
            cnt = cnt + 1
            rospy.sleep(0.1)
        move_cmd.linear.x = 0.0
        move_cmd.angular.z = 0.0
        cmd_vel_pub.publish(move_cmd)
        cnt = 0
        while (cnt <= final_dis_cnt):
            move_cmd.linear.x = 0.01
            move_cmd.angular.z = 0.0
            cmd_vel_pub.publish(move_cmd)
            cnt = cnt + 1
            rospy.sleep(0.1)
        rospy.logwarn("(%d / %d)", i+1, loop)
        localtime = time.localtime()
        result = time.strftime("%Y-%m-%d %I:%M:%S %p", localtime)
        rospy.logwarn(result)
    
    move_cmd.linear.x = 0.0
    move_cmd.angular.z = 0.0
    cmd_vel_pub.publish(move_cmd)
    rospy.logwarn("Stop")

if __name__ == "__main__":
    rospy.init_node('test_pogo_ping_node')
    try:
        test_pogo_ping()
    except rospy.ROSInterruptException, e:
        rospy.loginfo ("'test_pogo_ping_node' cannot launch.")
        rospy.loginfo(e)
        pass