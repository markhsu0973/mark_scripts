#!/bin/bash

INPUT_FILE=`zenity --title  "輸入" --entry --text "請輸入密碼："`
echo $INPUT_FILE | sudo -S add-apt-repository ppa:mystic-mirage/pycharm

echo $INPUT_FILE | sudo -S apt update

echo $INPUT_FILE | sudo -S apt install pycharm-community
