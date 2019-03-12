#!/usr/bin/python

import commands
import os
# mac addresss
mac = commands.getoutput("ifconfig -a | grep HWaddr | awk '{print $5}'")
ethernet_mac_address = mac[:17]
wlan_mac_address = mac[-17:]
linefeed = mac.find('\n')
# print mac
# print len(mac)

# IP address
ip = commands.getoutput("ifconfig | awk -F'[ :]+' '/Bcast/{print $4}'")
linefeed = ip.find('\n')
ethernet_ip = ip[:linefeed]
len_ip = len(ip)
wlan_ip_start = len_ip - linefeed-1
wlan_ip = ip[-wlan_ip_start:]
# print ip
user = "robot"
password = "robot"

#add 10-network.rules
os.mknod("/home/"+user+"/10-network.rules")
# 10-network.rules.move("/home/mark","/home/mark/mark")
rule = open("/home/"+user+"/10-network.rules", "w")
# SUBSYSTEM=="net", ACTION=="add",ATTR{address}==ethernet_mac_address, NAME="eth1"
rule.write('SUBSYSTEM=="net", ACTION=="add",ATTR{address}=='+'"'+ethernet_mac_address+'", NAME="enp2s0"')
# rule.write('\nSUBSYSTEM=="net", ACTION=="add",ATTR{address}=='+'"'+wlan_mac_address+'", NAME="wlp3s0"')
rule.close()
os.system("echo '"+password+"' | sudo -S mv /home/"+user+"/10-network.rules /etc/udev/rules.d")
os.system("cd /etc/udev/rules.d && echo '"+password+"' | sudo -S chmod 644 10-network.rules")

#amend network interface
# os.system("cd /etc/network && echo '"+password+"' | sudo -S chmod 777 interfaces")
# interface = open("/etc/network/interfaces", "a")
# interface.write('\nauto enp2s0\niface enp2s0 inet static\n    address '+ethernet_ip+'\n    netmask 255.255.255.0')
# # interface.write('\nauto wlp3s0\niface wlp3s0 inet static\n    address '+wlan_ip+'\n    netmask 255.255.255.0')
# os.system("cd /etc/network && echo '"+password+"' | sudo -S chmod 644 interfaces")
# interface.close()