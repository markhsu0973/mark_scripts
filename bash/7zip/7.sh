#!/bin/bash

INPUT_FILE=`zenity --file-selection --directory --title="選擇要壓縮的檔案"`
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

# Check if the user updated something in INPUT_FILE
if [[ -z "$INPUT_FILE" ]];
  then
    zenity --error --text="No input file detected. Shutting down."
    exit
fi

# Choose compress rate
def_rate=9
RATE=$(zenity --entry \
          --title="設定壓縮率" \
          --text="輸入壓縮率，預設為 9倍。" \
          --entry-text "9")
RATE=${RATE:=$def_rate}
case $? in
  0)
    echo "你指定的播放度：$RATE"
    ;;
  1)
    echo "User quitting"
    exit
    ;;
  2)
    zenity --error --text="Error in setting rosbag play rate."
    exit
    ;;
esac

# Choose where to save the output file
## Extract the file name
DEF_OUTPUT_FILE=$INPUT_FILE.7z

zenity --info --text="預設儲存路徑為 $DEF_OUTPUT_FILE，若想儲存制預設路徑，
直接按下取消鍵即可。"

OUTPUT_FILE=`zenity --file-selection --save --title="要儲存到哪裡？"`
OUTPUT_FILE=${OUTPUT_FILE:=$DEF_OUTPUT_FILE}
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

zenity --info --text="要壓縮的rosbag: $INPUT_FILE
壓縮率：$RATE 倍
將儲存至：$OUTPUT_FILE"


# Compress the file
7z a -mx=$RATE -mmt $OUTPUT_FILE $INPUT_FILE

# Prone user to check the saved file
parent_dir=${OUTPUT_FILE%/*}
zenity --question --text="想要檢視已儲存的檔案嗎？" --ok-label="打開儲存路徑" --cancel-label="取消"
ANS=$?
if [ "$ANS" -eq 0 ]; then
  nautilus $parent_dir
else
  echo "OK! Bye!"
fi

