#!/usr/bin/python
# -*- coding: UTF-8 -*-
import base64
from icon import img
import os
from io import BytesIO
from PIL import Image,ImageTk
byte_data = base64.b64decode(img)
image_data = BytesIO(byte_data)
imgage = Image.open(image_data)
imgage.show() 