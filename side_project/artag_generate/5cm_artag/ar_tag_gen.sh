#!/bin/bash

for i in {98..99};
do
#    echo $i;
	rosrun ar_track_alvar createMarker -s 5 $i
done
