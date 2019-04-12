#!/bin/bash

echo "Detect the USB Device"

function _key_input_func {
  # $1 is the default string
  # $2 is the input guidence
  default=$1
  read -p "$2: [ $default ]: " input
  input=${input:-$default}
  echo $input
}
lsusb > temp1.txt

USAGE=$(_key_input_func "Enter" "Please insert the USB device")
sleep 1
lsusb > temp2.txt

if [ "$(diff temp1.txt temp2.txt)" ]; then
  echo "--------------------------------------------------------------"
  echo "The USB device PID VID is: " 
  echo "  "$(diff temp1.txt temp2.txt)
  echo "--------------------------------------------------------------"
else
  echo "--------------------------------------------------------------"
  echo "Not detect the USB device"
  echo "--------------------------------------------------------------"
fi

rm -rf temp1.txt temp2.txt
