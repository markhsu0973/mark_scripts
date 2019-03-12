#! /usr/bin/env python
# -*- coding: UTF-8 -*-
import threading
import thread
import time
import signal
import paramiko
from subprocess import Popen, PIPE
import re
# class timer(threading.Thread):  # The timer class is derived from the class threading.Thread
#     def __init__(self, num, interval):
#         threading.Thread.__init__(self)
#         self.thread_num = num
#         self.interval = interval
#         self.thread_stop = False
#
#     def run(self):  # Overwrite run() method, put what you want the thread do here
#         while not self.thread_stop:
#             print 'Thread Object(%d), Time:%s/n' % (self.thread_num, time.ctime())
#             time.sleep(self.interval)
#
#     def stop(self):
#         self.thread_stop = True
#
# def test():
#     thread1 = timer(1, 1)
#     thread2 = timer(2, 2)
#     thread1.start()
#     thread2.start()
#     # thread1.stop()
#     time.sleep(10)
#     thread1.stop()
#     thread2.stop()
#     return
#
#
# if __name__ == '__main__':
#     test()

# def handler(signum, frame):
#     print "Forever is over!"
#     # raise Exception("end of time")
#     # global time2stop
#     # time2stop = 1
#     # global ssh
#     # ssh = paramiko.SSHClient()
#     # ssh.close()
#     t.start()
# signal.signal(signal.SIGALRM, handler)
# # Define a timeout for your function
# signal.alarm(5)
# import time
# from threading import Thread
#
# def myfunc(i):
#     print "sleeping 5 sec from thread", i
#     time.sleep(5)
#     print "finished sleeping from thread", i
#
# for i in range(10):
#     t = Thread(target=myfunc, args=(i,))
#     t.start()

import threading
import time

# # 子執行緒的工作函數
# def job():
#   for i in range(5):
#     # print("Child thread:", i)
#     print'Child thread:', i
#     time.sleep(1)
#
from threading import *
import time


class MyThread(Thread):
  def run(self):
    self.ifdo = True;
    while self.ifdo:
      print 'I am running...'
      time.sleep(1)

  def stop(self):
    print 'I am stopping it...'
    self.ifdo = False;


tr = MyThread()
tr.setDaemon(True)
tr.start()
print 'I will stop it...'
time.sleep(1)
tr.stop()
# tr.join()