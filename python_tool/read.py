#!/usr/bin/python
import rosbag
bag = rosbag.Bag('2019-01-09-14-39-55_22.bag')
for topic, msg, t in bag.read_messages(topics=['/battery/arriving', '/cmd_vel']):
    print msg
bag.close()
