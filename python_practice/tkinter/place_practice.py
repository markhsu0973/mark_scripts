#!/usr/bin/python
# -*- coding: UTF-8 -*-
from tkinter import *
 
root = Tk()
root.geometry('800x600')
lb = Label(root, text='hello Place')
# lb.place(relx = 1,rely = 0.5,anchor = CENTER)
# 使用相对坐标(0.5,0.5)将Label放置到(0.5*sx,0.5.sy)位置上
v = IntVar()
for i in range(5):
    Radiobutton(
        root,
        text='Radio' + str(i),
        variable=v,
        value=i
    ).place(x=80 * i, anchor=NW)
root.mainloop()
# 使用place来指定各个Radiobutton的位置