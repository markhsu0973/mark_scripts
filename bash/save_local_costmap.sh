source ~/wisbot/install/setup.bash
mainName=localcostmap
today=`date +%Y_%m_%d`
fileName=$mainName$today
rosrun map_server map_saver --occ 90 --free 10 -f $fileName map:=/move_base/local_costmap/costmap
rm -rf $fileName.yaml
