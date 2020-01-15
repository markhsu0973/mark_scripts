#!/usr/bin/python
# -*- coding: UTF-8 -*
from Tkinter import* #導入Tkinter模組
from PIL import Image,ImageTk

def Load ():
    print"load"

def UnLoad ():
    print"unload"


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
pil_image = Image.open("compal_logo.png")
w, h = pil_image.size
pil_image_resized = resize(w, h, w_box, h_box, pil_image) 
tk_image = ImageTk.PhotoImage(pil_image_resized)
imlabel = Label(win, image=tk_image, width=w_box, height=h_box, bg="white")
imlabel.pack()

wifi_ip = Label(text="Wifi IP ", fg="white", bg="gray")
wifi_ip.config(font=("ansifixed", 12))
wifi_ip.pack()
wifi_ip_entry = Entry(bd =2)
wifi_ip_entry.pack()

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

load_btn = Button(text="Load", font="12", command= Load)
load_btn.pack(side=LEFT)

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 5))
space_label.pack()

unload_btn = Button(text="UnLoad", font="12", command= UnLoad)
unload_btn.pack(side=LEFT)

space_label =  Label(text="", fg="white", bg="white")
space_label.config(font=("ansifixed", 8))
space_label.pack()

quit_btn = Button(text="QUIT", font="12", fg="red", command=win.quit)
quit_btn.pack()

#循環常駐主視窗
win.mainloop()