#!/bin/bash

zenity --info --text="歡迎使用 mp4 轉 gif!
請先輸入您要轉檔的mp4，再選擇輸出的檔案路徑與命名。" --title="show usage"

INPUT_FILE=`zenity --file-selection --title="選擇要轉檔的mp4"`
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

rate=`zenity --title  "輸入fps" --entry --text "數字越大，越順暢但容量越大："`

ffmpeg -i $INPUT_FILE -r $rate $OUTPUT_FILE.gif
echo $rate
du -h $OUTPUT_FILE.gif

zenity --question --text= "要不要刪除" --ok-label="沒問題啦" --cancel-label="刪除"
ANS=$?
if [ "$ANS" -eq 0 ]; then
  echo "OK"
else
  rm -rf $OUTPUT_FILE.gif
  echo "CANCEL"
fi


