#!/usr/bin/python
# -*- coding: UTF-8 -*
import os
alive = os.system("ping -c 1 -W 2000 192.168.100.222 > /dev/null 2>&1") == 0
print alive