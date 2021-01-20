#! /usr/bin/env python

import roslib 
import rospy
import actionlib
import geometry_msgs
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import tf.transformations
import time
import csv

def goal_action(x, y, heading):
    # Creates the SimpleActionClient
    move_base_client = actionlib.SimpleActionClient('move_base', MoveBaseAction)

    # Waits until the action server has started up and started
    # listening for goals.
    print 'Waiting for server...'
    move_base_client.wait_for_server()

    # Creates a goal to send to the action server.
    pose = geometry_msgs.msg.Pose()
    pose.position.x = x
    pose.position.y = y
    pose.position.z = 0.0

    q = tf.transformations.quaternion_from_euler(0, 0, heading)
    pose.orientation = geometry_msgs.msg.Quaternion(*q)
    goal = MoveBaseGoal()
    goal.target_pose.pose = pose
    goal.target_pose.header.frame_id = 'map'
    goal.target_pose.header.stamp = rospy.Time.now()


    # Sends the goal to the action server.
    print 'Sending goal to action server: %s' % goal
    move_base_client.send_goal(goal)

    print 'Waiting for result...'
    move_base_client.wait_for_result()

    print 'Result received. Action state is %s' % move_base_client.get_state()
    print 'Goal status message is %s' % move_base_client.get_goal_status_text()

    return move_base_client.get_result()  

if __name__ == '__main__':
    try:
        rospy.init_node('goal_action_client_example')

        with open("nav_waypoint.csv","r") as csvfile:
        reader = csv.reader(csvfile)
        for goal in reader:
            goal_action(float(goal[0]), float(goal[1]), float(goal[2]))
            time.sleep(0.5)


    except rospy.ROSInterruptException:
        print "program interrupted before completion"