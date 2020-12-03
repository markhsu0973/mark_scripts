#!/usr/bin/env python
import rospy
import time
import sys
from geometry_msgs.msg import Twist
from threading import *

class MyThread(Thread):
  def run(self):
	while True:
		pub.publish(cmd)

  def stop(self):
    self.ifdo = False;


def auto_spin():
    round = float(sys.argv[1])
    global cmd
    cmd = Twist()
    cmd.linear.x = 0
    global pub
    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
    cmd.angular.z = 0.314
    tr1 = MyThread();tr1.setDaemon(True);tr1.start()
    time.sleep(round * 20)
    tr1.stop()
    cmd.linear.x = 0.0
    cmd.angular.z = 0.0
    pub.publish(cmd)


if __name__ == "__main__":
    rospy.init_node('auto_spin_node')
    try:
        auto_spin()
    except rospy.ROSInterruptException, e:
        rospy.loginfo ("'auto_spin' cannot launch.")
        rospy.loginfo(e)
        pass
