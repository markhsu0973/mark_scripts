#!/usr/bin/env python
import math
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
# from TaskStatusService.srv import *
from decision_manager.srv import TaskStatusService


def callback_amcl_pose(data):
    global dis
    amcl_pose_x = data.pose.pose.position.x
    amcl_pose_y = data.pose.pose.position.y
    dis_x = amcl_pose_x - target_pose_x
    dis_y = amcl_pose_y - target_pose_y
    dis = math.sqrt(dis_x * dis_x + dis_y * dis_y)


def callback_cmd_vel(data):
    cmd.linear.x = data.linear.x
    if dis < dis_threshold:
        cmd.linear.x = data.linear.x / 2
    cmd.angular.z = data.angular.z


def deceleration():
    global target_pose_x
    global target_pose_y
    global cmd
    global dis_threshold

    cmd = Twist()
    cmd.linear.x = 0
    cmd.angular.z = 0

    target_pose_x = 0
    target_pose_y = 0

    dis_threshold = rospy.get_param('~dis_threshold', 3)

    rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, callback_amcl_pose)
    rospy.Subscriber("/cmd_vel", Twist, callback_cmd_vel)
    pub = rospy.Publisher('/cmd_vel_deceleration', Twist, queue_size=10)
    task_status_service = rospy.ServiceProxy('/TaskStatusService', TaskStatusService)

    while not rospy.is_shutdown():
        task = task_status_service(2, '')
        if len(task.goal_status.info) == 44 or len(task.goal_status.info) == 45:
            char= 'position'
            nPos = task.goal_status.json.index(char)
            str_filter_x_start = nPos + 12
            str_filter_x_end = str_filter_x_start + 16
            str_filter_y_start = str_filter_x_end + 2
            str_filter_y_end = str_filter_y_start + 16
            target_pose_x = float(task.goal_status.json[str_filter_x_start:str_filter_x_end])
            target_pose_y = float(task.goal_status.json[str_filter_y_start:str_filter_y_end])
        pub.publish(cmd)
if __name__ == '__main__':
    rospy.init_node('deceleration_node')
    try:
        deceleration()
    except rospy.ROSInterruptException, e:
        rospy.loginfo ("deceleration fail")
        rospy.loginfo(e)
        pass
