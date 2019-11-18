#!/usr/bin/python
# -*- coding: UTF-8 -*-

from tkinter import *
root = Tk()
Button(root,text='A').pack(side=LEFT,expand=YES,fill=Y)
Button(root,text='B').pack(side=TOP,expand=YES,fill=BOTH)
Button(root,text='C').pack(side=RIGHT,expand=YES,fill=NONE)
Button(root,text='D').pack(side=LEFT,expand=NO,fill=Y)
Button(root,text='E').pack(side=TOP,expand=YES,fill=BOTH)
Button(root,text='F').pack(side=BOTTOM,expand=YES)
Button(root,text='G').pack(anchor=SE)
root.mainloop()