#!/bin/bash

zenity --info --text="歡迎使用 7z!
請先輸入您要壓縮的檔案，再選擇輸出的檔案路徑與命名。" --title="show usage"


INPUT_FILE=`zenity --file-selection --multiple --separator=' ' --title="選擇要壓縮的檔案"`
case $? in
  0)
    echo "\"$INPUT_FILE\" is selected."
    ;;
  1)
    echo "User quitting."
    exit
    ;;
  -1)
    zenity --error --text="Error in reading file."
    exit
    ;;
esac

OUTPUT_FILE=`zenity --file-selection --save --title="要輸出到哪裡？"`
case $? in
  0)
    echo "Output directory at \"$OUTPUT_FILE\""
    ;;
  1)
    echo "User quitting."
    exit
    ;;
  -1)
    zenity --error --text="Error in outputting file."
    exit
    ;;
esac

size=`zenity --title  "輸入壓縮倍率" --entry --text "0, 1, 3, 5, 7, 9 六種選擇，數字越大，壓縮率越高："`

7z a -mx=$size -mmt  $OUTPUT_FILE.7z $INPUT_FILE

