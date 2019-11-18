#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import multiprocessing,os,subprocess
import datetime
import time
import signal
import copy
import argparse
import paramiko
import re
import subprocess
import ipaddress
from subprocess import Popen, PIPE
import rospy
from Tkinter import *
import time
import tkMessageBox
def ssh(agv_ip,ssh_cmd):
	if ping_agv(agv_ip) == 0:
		global source_ros
		global output_msg
		source_ros = 'source /opt/ros/kinetic/setup.bash && source /home/robot/catkin_ws/AGV3/setup.bash'
		ssh = paramiko.SSHClient()
		ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
		ssh.connect(hostname=agv_ip, username='mark', password='1111')
		stdin, stdout, stderr = ssh.exec_command(ssh_cmd)
		output_msg = stdout.read()
		return output_msg

def ping_agv(IP):
    # tStart = time.time()
    toping = Popen(['ping', '-c', '2', '-w', '2', IP], stdout=PIPE)# The -c means that the ping will stop afer 5 package is replied and the -W 5 is the timelimit
    output = toping.communicate()[0]
    hostalive = toping.returncode
    return hostalive
    
class App:
    def __init__(self,master):
        frame = Frame(master)
        frame.pack()
        self.L1 = Label(frame, text="AGV IP ",font=10)
        self.L1.pack( side = LEFT)
        self.entryWidget = Entry(frame,bd =6)
        # self.entryWidget["width"] = 35
        self.entryWidget.pack(side=LEFT)
        self.hi_there = Button(frame, text="Load", height=2, width=6,command=self.Load)
        self.hi_there.pack(side=LEFT)
        self.hi_there = Button(frame, text="UnLoad",height=2, width=6, command=self.UnLoad)
        self.hi_there.pack(side=LEFT)
        self.button = Button(frame, text="QUIT", fg="red",height=2, width=6, command=frame.quit)
        self.button.pack(side=LEFT)

    def Load(self):
    	cmd = "pwd"
        lbl1.config(bg='gray')
        lbl1.config(height=3, font=10)
        lbl1.config(fg='black')
        lbl1["text"] = ""

    	if self.entryWidget.get().strip() !="":
    		self.show_msg(ssh(self.entryWidget.get().strip(),cmd))


        # text = self.entryWidget.get().strip()
        # # print (ssh(text))
        # if text != "":
        #     self.show_msg(text)

    def UnLoad(self):
    	cmd = "ifconfig"
        lbl1.config(bg='gray')
        lbl1.config(height=2, font=10)
        lbl1.config(fg='black')
        lbl1["text"] = ""

    	if self.entryWidget.get().strip() !="":
    		self.show_msg(ssh(self.entryWidget.get().strip(),cmd))

    def show_msg(self,msg_info):
        lbl1.config(bg='gray')
        lbl1.config(height=2,font=10)
        lbl1.config(fg='black')
        lbl1["text"] = msg_info

        # tkMessageBox.showinfo("Time up!","Time up!")

    def GetSource():
        get_window = Tkinter.Toplevel(root)
        get_window.title('Source File?')
        Tkinter.Entry(get_window, width=30,
                      textvariable=source).pack()
        Tkinter.Button(get_window, text="Change",
                       command=lambda: update_specs()).pack()



root = Tk()
root.title("Tool")
root.geometry('500x300')
lbl1 = Label()
lbl1.pack(fill=BOTH, expand=1)
app = App(root)
root.mainloop()