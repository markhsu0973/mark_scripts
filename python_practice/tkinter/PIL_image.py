#!/usr/bin/python
# -*- coding: UTF-8 -*
import Image
from Tkinter import* #導入Tkinter模組
from PIL import Image,ImageTk
# Read image 
img = Image.open('compal_logo.png') 
  
# Output Images 
img.show() 
  
# prints format of image 
print(img.format) 
  
# prints mode of image 
print(img.mode) 