#!/bin/bash

#Need to install package sshpass
#sudo apt-get install sshpass

zenity --question --text="ssh到哪裡" --ok-label="AGV" --cancel-label="TMS"
ANS=$?
if [ "$ANS" -eq 0 ]; then
#  echo "AGV"
  SELECTION=`zenity --list --text="請選擇AGV" --column="AGV-list" "agv05" "agv07" "agv08" "agv09" "agv10" "agv11" "agv12" "agv13" "agv14" "agv17" "agv18"`
else
#  echo "TMS"
  SELECTION=`zenity --list --text="請選擇TMS" --column="TMS-list" "PCP-TMS" "KSP2-TMS" "KSP3-TMS" "KSP4-TMS" "CD-TMS"`
fi

case "$SELECTION" in
  PCP-TMS)
    user_ip=robot@10.111.128.20
    password=robot
    ;;
  KSP2-TMS)
    user_ip=robot@10.128.153.30
    password=robot
    ;;
  KSP3-TMS)
    user_ip=agv@10.129.64.5
    password=robotrobot
    ;;
  KSP4-TMS)
    user_ip=robot@10.129.158.11
    password=robot
    ;;
  CD-TMS)
    user_ip=ubuntu@10.134.28.72
    password=compal123!
    ;;
  agv05)
    user_ip=robot@10.129.203.243
    password=robot
    ;;
  agv07)
    user_ip=robot@10.128.28.77
    password=robot
    ;;
  agv08)
    user_ip=robot@10.129.13.10
    password=robot
    ;;
  agv09)
    user_ip=robot@10.129.13.11
    password=robot
    ;;
  agv10)
    user_ip=robot@10.128.28.80
    password=robot
    ;;
  agv11)
    user_ip=robot@10.128.28.78
    password=robot
    ;;
  agv12)
    user_ip=robot@10.129.203.244
    password=robot
    ;;
  agv13)
    user_ip=robot@10.129.203.246
    password=robot
    ;;
  agv14)
    user_ip=robot@10.129.203.245
    password=robot
    ;;
  agv17)
    user_ip=robot@10.134.13.234
#    user_ip=robot@10.134.12.38
    password=robot
    ;;
  agv18)
    user_ip=robot@10.134.12.41
    password=robot
    ;;
esac
echo ssh to $SELECTION
sshpass -p $password ssh $user_ip


