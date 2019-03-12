#!/usr/bin/python
# -*- coding: utf-8 -*-

# import multiprocessing
#
# def worker():
#     """worker function"""
#     print 'Worker'
#     return
#
# if __name__ == '__main__':
#     jobs = []
#     for i in range(5):
#         p = multiprocessing.Process(target=worker)
#         jobs.append(p)
#         p.start()

#https://pymotw.com/3/multiprocessing/basics.html
import multiprocessing
import time
from multiprocessing import Process, Queue
# global num
# num = 0
def slow_worker(queue):
    num = 0
    while True:

        print('Starting worker')
        time.sleep(1)
        queue.put(num)
        num += 1
        queue.put(num)
        # print('Finished worker')
        # time.sleep(0.5)


if __name__ == '__main__':
    q = Queue()
    p = multiprocessing.Process(target=slow_worker, args=(q,))
    # print('BEFORE:', p, p.is_alive())
    p.start()
    # print('DURING:', p, p.is_alive())
    time.sleep(5)
    p.terminate()
    print q.get()
    # print('TERMINATED:', p, p.is_alive())
    #
    # p.join()
    # print('JOINED:', p, p.is_alive())

#https://itw01.com/VUU8EXD.html