#!/bin/bash
_logdate=$(date +"%m%d%y")
diskName='/dev/sda1'
capacityLimit=90
bagfolder='/home/robot/.ros'
logfolder='/home/robot/.ros/log'
fileName='*.bag*'
disk_clean_log_dir=".disk_clean_log_dir"
logfile="$HOME"/"$disk_clean_log_dir"/"check_disk_$_logdate.txt"

if [ ! -d "$HOME"/"$disk_clean_log_dir" ]
then
  mkdir "$HOME"/"$disk_clean_log_dir"
fi

if [ ! -f $logfile ]
then
  touch $logfile
  echo 0 > $logfile
fi 

currentTime=$(date +"%y%m%d %H:%M:%S")
currentCapacity=$(df -h | grep ${diskName} | awk '{print $5}' | cut -d '%' -f 1)

bagDeleteDay=7
logDeleteDay=30
echo -e "\n======================${currentTime}======================" >> ${logfile}
while [ "${currentCapacity}" -ge "${capacityLimit}" ] && [ "${bagDeleteDay}" -ge "0" ] && [ "${logDeleteDay}" -ge "0" ]
do
    # Delete old log data
    deleteBag=$(find ${bagfolder} -maxdepth 1 -type f -name ${fileName} -mtime +${bagDeleteDay})
    rm -f ${deleteBag}

	deleteLog=$(find ${logfolder} -type d -mtime +${logDeleteDay})
	rm -rf ${deleteLog}
	deleteLog=$(find ${logfolder} -maxdepth 1 -type f -mtime +${logDeleteDay})
	rm -f ${deleteLog}

	echo -e "\n* Delete old log data (${bagDeleteDay} day ago)" >> ${logfile}
    echo -e "${deleteBag}" >> ${logfile}

	currentCapacity=$(df -h | grep ${diskName} | awk '{print $5}' | cut -d '%' -f 1)
	bagDeleteDay=$((${bagDeleteDay}-1))
	logDeleteDay=$((${logDeleteDay}-1))
done

exit 0
