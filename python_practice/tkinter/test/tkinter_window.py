#!/usr/bin/python
# -*- coding: UTF-8 -*
import sys, os
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
from Tkinter import* #導入Tkinter模組
from PIL import Image,ImageTk
import base64
from base64_img import *
from io import BytesIO
import platform


def ssh(agv_ip,ssh_cmd):
    source_ros = 'source /opt/ros/kinetic/setup.bash && source /home/robot/catkin_ws/AGV3/setup.bash'    
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect(agv_ip, username="mark", password="1111")
    stdin, stdout, stderr = client.exec_command(ssh_cmd)
    for line in stdout:
        print line.strip('/n')
    client.close()

def ping_agv(IP):
    # tStart = time.time()
    toping = Popen(['ping', '-c', '2', '-w', '2', IP], stdout=PIPE)# The -c means that the ping will stop afer 5 package is replied and the -W 5 is the timelimit
    output = toping.communicate()[0]
    hostalive = toping.returncode
    return hostalive

def Load ():
    print"load"
    cmd = "pwd"
    ssh(wifi_ip_entry.get().strip(),cmd)
    

def UnLoad ():
    print"unload"
    cmd = "ls"
    ssh(wifi_ip_entry.get().strip(),cmd)

def resize(w, h, w_box, h_box, pil_image):  
  f1 = 1.0*w_box/w # 1.0 forces float division in Python2  
  f2 = 1.0*h_box/h  
  factor = min([f1, f2])  
  #print(f1, f2, factor) # test  
  # use best down-sizing filter  
  width = int(w*factor)  
  height = int(h*factor)  
  return pil_image.resize((width, height), Image.ANTIALIAS) 

win = Tk() #建立Tk視窗

#標題
win.title("Roller System Integration Test")

sysstr = platform.system()
if(sysstr =="Windows"):
  print ("Call Windows tasks")
  icon_image_tmp = open("icon_image_tmp.ico","wb+")
  icon_image_tmp.write(base64.b64decode(compal_logo_ico))
  icon_image_tmp.close()
  win.iconbitmap("icon_image_tmp.ico")
  os.remove("icon_image_tmp.ico")
elif(sysstr == "Linux"):
  print ("Call Linux tasks")
  icon_image_tmp = open("icon_image_tmp.xbm","wb+")
  icon_image_tmp.write(base64.b64decode(compal_logo_xbm))
  icon_image_tmp.close()
  win.iconbitmap("@icon_image_tmp.xbm")
  os.remove("icon_image_tmp.xbm")
else:
  print ("Other System tasks")

#大小
win.geometry("400x400") #寬x高
win.geometry("400x400+400+400")
win.minsize(width=400, height=400) #最小範圍
win.maxsize(width=1024, height=1024) #最大範圍
win.resizable(0, 0) # 1 = True, 0 = False

win.config(bg="white")
#透明度
win.attributes("-alpha", 1)   #1~0,  1=100%  0=0%

#置頂
win.attributes("-topmost", 1) # 1 = True, 0 = False  

title_text = Label(text="Roller System Integration Test", fg="black", bg="white")
# obj.config(font="字型 大小")
title_text.config(font=("ansifixed", 15))
title_text.pack()

w_box = 200  
h_box = 100
#
image_tmp = open("image_tmp.png","wb+")
image_tmp.write(base64.b64decode(compal_logo_png))
image_tmp.close()
pil_image = Image.open("image_tmp.png")

w, h = pil_image.size
pil_image_resized = resize(w, h, w_box, h_box, pil_image) 
tk_image = ImageTk.PhotoImage(pil_image_resized)
imlabel = Label(win, image=tk_image, width=w_box, height=h_box, bg="white")
imlabel.pack()
os.remove("image_tmp.png") 
# 
wifi_ip = Label(text="Wifi IP ", fg="white", bg="gray")
wifi_ip.config(font=("ansifixed", 12))
wifi_ip.pack()
wifi_ip_entry = Entry(bd =2)
wifi_ip_entry.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

load_btn = Button(text="Load", font="12", command= Load)
load_btn.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

unload_btn = Button(text="UnLoad", font="12", command= UnLoad)
unload_btn.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 8))
space_label.pack()

quit_btn = Button(text="QUIT", font="12", fg="red", command=win.quit)
quit_btn.pack()

#循環常駐主視窗
win.mainloop()
