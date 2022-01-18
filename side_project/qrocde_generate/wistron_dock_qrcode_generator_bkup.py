#!/usr/bin/python
# -*- coding: UTF-8 -*
import time
from Tkinter import* #導入Tkinter模組
from PIL import Image,ImageTk
import base64
from base64_img import *
from io import BytesIO
import platform

import cv2
import sys
import os

import qrcode
from PIL import Image
from pyzbar.pyzbar import decode

def generate ():
    os.system(clear_cmd)
    print"=== Start Generate QRcode ==="
    write_msg = str(qrcode_msg_entry.get().strip())
    im1 = qrcode.make(write_msg)
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_H,
        box_size=10,
        border=4,
    )

    im1 = im1.resize((189, 189))
    # 
    image_tmp = open("image_tmp.png","wb+")
    image_tmp.write(base64.b64decode(artag_for_qrcode_png))
    image_tmp.close()
    # pil_image = Image.open("image_tmp.png")

    # w, h = pil_image.size
    # pil_image_resized = resize(w, h, w_box, h_box, pil_image) 
    # tk_image = ImageTk.PhotoImage(pil_image_resized)
    # imlabel = Label(win, image=tk_image, width=w_box, height=h_box, bg="white")
    # imlabel.pack()
    # os.remove("image_tmp.png") 
    # 
    # im2 = Image.open('artag_for_qrcode.png')
    im2 = Image.open('image_tmp.png')
    logo_pos = ((im1.size[0] - im2.size[0]) // 2, (im1.size[1] - im2.size[1]) // 2)
    Image.Image.paste(im1, im2,logo_pos) 
    im1.save('Dock_SN.png')
    os.remove("image_tmp.png") 
    print "Generate the qrcode which message is " + write_msg
    print"=== Finish Generate QRcode ==="

def check():
  print"=== Start Check QRcode ==="
  img = cv2.imread('Dock_SN.png')

  # print len(decode(img))
  for barcode in decode(img):
    myData = barcode.data.decode('utf-8')
    print(myData)
    text.delete(1.0, 'end')
    text.insert('end', myData)
    print"=== Finish Check QRcode ==="

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

global clear_cmd
#標題
win.title("QRcode  Generator Tool")

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

#大小
win.geometry("400x00") #寬x高
win.geometry("400x400+400+400")
win.minsize(width=400, height=400) #最小範圍
win.maxsize(width=1024, height=1024) #最大範圍
win.resizable(0, 1) # 1 = True, 0 = False

win.config(bg="white")
#透明度
win.attributes("-alpha", 1)   #1~0,  1=100%  0=0%

#置頂
win.attributes("-topmost", 1) # 1 = True, 0 = False  

title_text = Label(text="Wistron Docking QRcode Generator", fg="black", bg="white")
# obj.config(font="字型 大小")
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
qrcode_msg = Label(text="QRcode Message ", fg="white", bg="gray")
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

load_btn = Button(text="Detect the generated qrcode", font="12", command= check)
load_btn.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 1))
space_label.pack()

text = Text(win, width=20, height=1)
text.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

quit_btn = Button(text="QUIT", font="12", fg="red", command=win.quit)
quit_btn.pack()

#循環常駐主視窗
win.mainloop()
