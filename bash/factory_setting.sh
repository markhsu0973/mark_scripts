#!/bin/bash

sudo route add default gw 192.168.100.1
sudo route add -net 10.0.0.0 netmask 255.0.0.0 gw 10.110.217.254
