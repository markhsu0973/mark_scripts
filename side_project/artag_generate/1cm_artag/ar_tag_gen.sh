#!/bin/bash

for i in {0..97};
do
#    echo $i;
	rosrun ar_track_alvar createMarker -s 1 $i
done
