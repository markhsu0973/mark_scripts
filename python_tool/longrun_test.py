#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose2D
import math
import time
import sys, signal

class Run():
    def __init__(self):
        rospy.init_node('LongRunTest', anonymous=False)
        mode = float(sys.argv[1])
        rospy.on_shutdown(self.shutdown)
        signal.signal(signal.SIGINT, self.quit)
        signal.signal(signal.SIGTERM, self.quit)
        self.pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
        sub = rospy.Subscriber('odom', Odometry, self.callback)

        goal_distance = 1
        goal_angle= math.pi
        linear_speed = 0.05
        angular_speed = 0.1
        self.cmd = Twist()
        self.amr_pose = Pose2D()
        self.amr_pose_init = Pose2D()
        self.cmd.linear.x = 0.0
        self.cmd.angular.z = 0.0
        stop = False
        time.sleep(1)
        self.amr_pose_init.x = self.amr_pose.x
        self.amr_pose_init.y = self.amr_pose.y
        self.amr_pose_init.theta = self.amr_pose.theta
        if mode == 0:
            rospy.loginfo("Straight")
            self.cmd.linear.x = linear_speed
        elif mode == 1:
            rospy.loginfo("Spin")
            self.cmd.angular.z = angular_speed
        else:
            rospy.loginfo("Error")
            stop = True
        spin_again = True
        while (not stop):
            dis_x = self.amr_pose.x - self.amr_pose_init.x
            dis_y = self.amr_pose.y - self.amr_pose_init.y
            dis_diff = math.sqrt(dis_x * dis_x + dis_y * dis_y)
            angle_diff = abs(self.amr_pose.theta - self.amr_pose_init.theta)
            # print "dis_diff = ", dis_diff, " angle_diff = ", angle_diff
            if mode == 0:
                if dis_diff >= goal_distance:
                    stop = True
                else:
                    self.pub.publish(self.cmd)
            elif mode == 1:
                if angle_diff >= goal_angle:
                    if spin_again:
                        # print "self.amr_pose_init.theta = ", self.amr_pose_init.theta, " self.amr_pose.theta  = ", self.amr_pose.theta 
                        self.amr_pose_init.theta = self.amr_pose.theta 
                        spin_again = False
                    else:
                        stop = True
                else:
                    self.pub.publish(self.cmd)
            else:
                stop = True
            time.sleep(0.05)
            
        # self.pub.publish(self.cmd)
    
    def quit(signum, frame):
        rospy.loginfo("Stopping ...")
        self.cmd.linear.x = 0.0
        self.cmd.angular.z = 0.0
        self.pub.publish(self.cmd)
        self.pub.publish(self.cmd)
        sys.exit()
    def shutdown(self):
        # global cmd
        rospy.loginfo("Stopping the robot...")
        self.cmd.linear.x = 0.0
        self.cmd.angular.z = 0.0
        self.pub.publish(self.cmd)
        self.pub.publish(self.cmd)
        # rospy.sleep(1)
    def callback(self, msg):
        # print msg.pose.pose.position
        self.amr_pose.x = msg.pose.pose.position.x
        self.amr_pose.y = msg.pose.pose.position.y
        x = msg.pose.pose.orientation.x
        y = msg.pose.pose.orientation.y
        z = msg.pose.pose.orientation.z
        w = msg.pose.pose.orientation.w
        self. amr_pose.theta = math.atan2(2*w*z + 2*x*y, 1 - 2*y*y - 2*z*z)
 
if __name__ == '__main__':
    try:
        Run()
    except:
        rospy.loginfo("LongRunStraight node terminated.")