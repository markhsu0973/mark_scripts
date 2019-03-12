#!/bin/bash

zenity --info --text="歡迎使用 rosbag_repair!
請先輸入您要修復的 rosbag，再選擇輸出的檔案路徑與命名。" --title="show usage"

INPUT_FILE=`zenity --file-selection --title="選擇要修復的檔案"`
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


echo "Reindexing rosbag..."
rosbag reindex $INPUT_FILE
echo "Fixing bag..."
rosbag fix $INPUT_FILE $OUTPUT_FILE
echo "The output bag file is saved at \"$OUTPUT_FILE\"."
