#!/usr/bin/python
# -*- coding: UTF-8 -*-
from tkinter import * 

class TrafficLight: 

    def __init__(self): 

     window = Tk() 
     window.title("Traffic Light") 

     self.canvas = Canvas(window, width = 80, height = 180, bg = "white") 
     self.canvas.pack() 

     frame = Frame(window) 
     frame.pack() 

     self.color = StringVar() 

     rbRed = Radiobutton(frame, text = "Red", variable = self.color, value = "R", command = self.colorChange) 
     rbRed.grid(row = 1, column = 1) 

     rbYellow = Radiobutton(frame, text = "Yellow", variable = self.color, value = "Y", command = self.colorChange) 
     rbYellow.grid(row = 1, column = 2) 

     rbGreen = Radiobutton(frame, text = "Green", variable = self.color, value = "G", command = self.colorChange) 
     rbGreen.grid(row = 1, column = 3) 


     self.red = self.canvas.create_oval(20,20,60,60, fill = "white") 
     self.yellow = self.canvas.create_oval(20,70,60,110, fill = "white") 
     self.green = self.canvas.create_oval(20,120,60,160, fill = "white") 

     window.mainloop() 

    def colorChange(self): 
     on = self.color.get() 

     if on == "R": 
      self.canvas.itemconfig(self.red, fill = "red") 
      self.canvas.itemconfig(self.yellow, fill = "white") 
      self.canvas.itemconfig(self.green, fill = "white") 
     elif on == "Y": 
      self.canvas.itemconfig(self.red, fill = "white") 
      self.canvas.itemconfig(self.yellow, fill = "yellow") 
      self.canvas.itemconfig(self.green, fill = "white") 
     elif on == "G": 
      self.canvas.itemconfig(self.red, fill = "white") 
      self.canvas.itemconfig(self.yellow, fill = "white") 
      self.canvas.itemconfig(self.green, fill = "green") 

TrafficLight()