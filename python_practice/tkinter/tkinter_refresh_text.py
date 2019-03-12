#!/usr/bin/python
# -*- coding: UTF-8 -*-

from Tkinter import *
import time

num = 0

tk = Tk()
# canvas = Canvas(tk, width=500, height=500)
canvas = Canvas(tk)
canvas.pack()
itext = canvas.create_text(30, 30, text='num: ' + str(num))
while num < 7:
    # num += 1
    num += 2

    canvas.itemconfig(itext, text='num: ' +str(num))
    canvas.insert(itext, 50, '')
    tk.update()
    print 'num: ',num
    tk.after(1000)