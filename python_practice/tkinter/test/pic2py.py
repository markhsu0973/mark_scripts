#!/usr/bin/python
# -*- coding: UTF-8 -*-
import base64
from base64img import base64_img
import os
from io import BytesIO
from PIL import Image,ImageTk
 
def pic2py(picture_names, py_name):
    """
    將圖像文件轉換爲py文件
    :param picture_name:
    :return:
    """
    write_data = []
    for picture_name in picture_names:
	    filename = picture_name.replace('.', '_')
	    open_pic = open("%s" % picture_name, 'rb')
	    b64str = base64.b64encode(open_pic.read())
	    open_pic.close()
	    # 注意這邊b64str一定要加上.decode()
	    write_data.append('%s = "%s"\n' % (filename, b64str.decode()))

    f = open('%s.py' % py_name, 'w+')
    for data in write_data:
    	f.write(data)
    f.close()
 
if __name__ == '__main__':
    pics = ["compal_logo.ico", "compal_logo.png"]
    pic2py(pics, 'base64_img')	 # 將pics裏面的圖片寫到 memory_pic.py 中
    print("ok")