#!/usr/bin/python
# -*- coding: UTF-8 -*-

import Tkinter
import random


def random_number(a, b):
    t.delete(1.0, 'end')
    t.insert('end', random.randint(a, b))
    t.after(10, random_number, a, b)


top = Tkinter.Tk()

t = Tkinter.Text(top)
t.pack(expand=1, fill='both')
random_number(10, 15)

top.mainloop()
