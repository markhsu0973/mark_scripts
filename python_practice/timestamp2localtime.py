#!/usr/bin/python

import datetime
import os
import re


# s = '1346114717972'
# fmt = "%Y-%m-%d %H:%M:%S"
#
# # local time
# t = datetime.datetime.fromtimestamp(float(s)/1000.)
# print t.strftime(fmt) # prints 2012-08-28 02:45:17

f = open('/home/mark/filezilla_download/2018-08-17-agv17_log/rosout.log', 'r')
lines = f.readline()
print lines
# for line in lines:
#     print(line)