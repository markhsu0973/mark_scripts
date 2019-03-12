#!/bin/bash

cd mark/src
pwd
repo init -u http://192.168.100.50/CompalAGV3/agv3_manifest.git -m default.xml
repo sync
