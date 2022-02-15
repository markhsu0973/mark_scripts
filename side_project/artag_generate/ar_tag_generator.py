#!/usr/bin/python
# -*- coding: UTF-8 -*
import time
from Tkinter import* 
from PIL import Image,ImageTk
import base64
from base64_img import *
from artag_base64_img import *
from io import BytesIO
import platform

import cv2
import sys
import os



def generate ():
    os.system(clear_cmd)
    msg = int(str(qrcode_msg_entry.get().strip()))
    print"=== Start Generate AR Tag ==="
    if msg >= 0 and msg <= 99:
      artag_file = "ID_" + str(msg) +".png"
      artag_endcode_file = "ID_" + str(msg) +"_png"
      # print artag_base64_img
      artag_image_tmp = open(artag_file,"wb+")
      exec("artag_image_tmp.write(base64.b64decode(ID_{}_png))".format(str(msg)))
      artag_image_tmp.close()
      print "Success"
      detect_text.set("Success")
    else:
      print "Fail"
      detect_text.set("Fail")
    print"============================="


def resize(w, h, w_box, h_box, pil_image):  
  f1 = 1.0*w_box/w # 1.0 forces float division in Python2  
  f2 = 1.0*h_box/h  
  factor = min([f1, f2])  
  #print(f1, f2, factor) # test  
  # use best down-sizing filter  
  width = int(w*factor)  
  height = int(h*factor)  
  return pil_image.resize((width, height), Image.ANTIALIAS) 

win = Tk() 

global clear_cmd

win.title("AT Tag  Generator Tool")

sysstr = platform.system()
if(sysstr =="Windows"):
  print ("Call Windows tasks")
  clear_cmd = 'cls'
  icon_image_tmp = open("icon_image_tmp.ico","wb+")
  icon_image_tmp.write(base64.b64decode(wistron_logo_ico))
  icon_image_tmp.close()
  win.iconbitmap("icon_image_tmp.ico")
  os.remove("icon_image_tmp.ico")
elif(sysstr == "Linux"):
  print ("Call Linux tasks")
  clear_cmd = 'clear'
  icon_image_tmp = open("icon_image_tmp.xbm","wb+")
  icon_image_tmp.write(base64.b64decode(wistron_logo_xbm))
  icon_image_tmp.close()
  win.iconbitmap("@icon_image_tmp.xbm")
  os.remove("icon_image_tmp.xbm")
else:
  print ("Other System tasks")


win.geometry("400x00") 
win.geometry("400x400+400+400")
win.minsize(width=400, height=400) 
win.maxsize(width=1024, height=1024)
win.resizable(0, 1) # 1 = True, 0 = False

win.config(bg="white")

win.attributes("-alpha", 1)   #1~0,  1=100%  0=0%


win.attributes("-topmost", 1) # 1 = True, 0 = False  

title_text = Label(text="Charging Station AR Tag Generator", fg="black", bg="white")

title_text.config(font=("ansifixed", 15))
title_text.pack()

w_box = 200  
h_box = 100
#
image_tmp = open("image_tmp.png","wb+")
image_tmp.write(base64.b64decode(wistron_logo_png))
image_tmp.close()
pil_image = Image.open("image_tmp.png")

w, h = pil_image.size
pil_image_resized = resize(w, h, w_box, h_box, pil_image) 
tk_image = ImageTk.PhotoImage(pil_image_resized)
imlabel = Label(win, image=tk_image, width=w_box, height=h_box, bg="white")
imlabel.pack()
os.remove("image_tmp.png") 
# 
qrcode_msg = Label(text="AR Tag Number", fg="white", bg="gray")
qrcode_msg.config(font=("ansifixed", 12))
qrcode_msg.pack()
qrcode_msg_entry = Entry(bd =2)
qrcode_msg_entry.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()


space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 1))
space_label.pack()

load_btn = Button(text="Generate", font="12", command= generate)
load_btn.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 1))
space_label.pack()

detect_text = StringVar()
detect_text.set("UnKnown")
detect_label = Label(textvariable=detect_text)
detect_label.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

quit_btn = Button(text="QUIT", font="12", fg="red", command=win.quit)
quit_btn.pack()


win.mainloop()
