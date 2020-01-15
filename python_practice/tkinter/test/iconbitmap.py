#!/usr/bin/python
# -*- coding: UTF-8 -*
from Tkinter import *
root = Tk()
root.minsize(100, 100)
root.title("My Window")
try:
    root.wm_iconbitmap('@compal_logo.xbm')
    root.mainloop()
except TclError:
    print 'No ico file found'