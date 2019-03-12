#!/bin/bash

INPUT_FILE=`zenity --title  "輸入" --entry --text "請輸入 ftp 網址："`

OUTPUT_FILE=`zenity --file-selection --directory --title="要輸出到哪裡？"`

cd $OUTPUT_FILE

pwd

wget --password=robot $INPUT_FILE
