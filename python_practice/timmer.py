#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
starttime = datetime.datetime.now()
#long running
a = 0
for i in range(100):
    a +=1
endtime = datetime.datetime.now()
print (endtime - starttime).seconds

