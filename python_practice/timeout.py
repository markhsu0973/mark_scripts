#!/usr/bin/python
# -*- coding: utf-8 -*-
import time
import threading
import signal

def handler(signum, frame):
     print "Forever is over!"
     # raise Exception("end of time")
     global var1
     var1 = 1



# This function *may* run for an indetermined time...
def loop_forever():
    import time
    # while 1:
    #     print "sec"
    #     print var1
    #     time.sleep(1)
    print "sec"
    print var1
    time.sleep(1)


# Register the signal function handler
signal.signal(signal.SIGALRM, handler)
# Define a timeout for your function
signal.alarm(3)

var1 = 0

try:
    # while var1 !=1:
    #     loop_forever()

    while True:
        loop_forever()

except Exception, exc:
        print exc
