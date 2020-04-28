#!/usr/bin/python
# -*- coding: UTF-8 -*-
import base64
from base64_img import *
import os
from io import BytesIO
from PIL import Image,ImageTk

def get_pic(pic_name):
	byte_data = base64.b64decode(pic_name)
	image_data = BytesIO(byte_data)
	return image_data

compal_logo_ico_imgage = Image.open(get_pic(compal_logo_ico))
compal_logo_ico_imgage.show() 