import sys
import tf
import rospy
import geometry_msgs.msg
from rosbag import Bag

import os

import copy

tran_frame_id_src = 'base_link'
tran_frame_id_target = 'map'
tran_frame_id_append = '_bag'

tran_tpoic_robot_pos = '/robot_pose'
tran_tf_filter_list = ['/motor/odom_L','/motor/odom_R','/imu_data','/back_scan_original' ,'/front_scan_original','/scan_original_AMCL_']

def processBag(file_src,file_dst):
    print file_src , " ----> " , file_dst
    count_robot = 0
    count_odom_L = 0
    count_odom_R = 0
    count_scan = 0
    count_imu = 0
    
    count_tf = [0] * len(tran_tf_filter_list)
    
    time_start = 0
    time_end = 0



    tran_robot = tf.Transformer(False)

    with Bag(file_dst, 'w') as Y:
        for topic, msg, t in Bag(file_src):
            if time_start == 0.0:
                time_start = t
            time_end = t

            if topic == '/tf':
                msg_clone = copy.deepcopy(msg)
                # print
                for trans in msg_clone.transforms:
                    if trans.header.frame_id != tran_frame_id_target :
                        trans.header.frame_id += tran_frame_id_append
                    trans.child_frame_id += tran_frame_id_append
                Y.write(topic, msg_clone, t)


                tran_robot.setTransform(msg.transforms[0])
                if msg.transforms[0].header.frame_id == tran_frame_id_src and tran_robot.canTransform(tran_frame_id_target,tran_frame_id_src,rospy.Time(0)): 
                    robot_pos, robot_quat = tran_robot.lookupTransform(tran_frame_id_target,tran_frame_id_src,rospy.Time(0))
                    pose = geometry_msgs.msg.PoseStamped()
                    pose.header = msg.transforms[0].header
                    pose.header.frame_id = tran_frame_id_target

                    pose.pose.position.x = robot_pos[0]
                    pose.pose.position.y = robot_pos[1]
                    pose.pose.position.z = robot_pos[2]
                    
                    pose.pose.orientation.x = robot_quat[0]
                    pose.pose.orientation.y = robot_quat[1]
                    pose.pose.orientation.z = robot_quat[2]
                    pose.pose.orientation.w = robot_quat[3]

                    Y.write(tran_tpoic_robot_pos, pose, t)
                    count_robot += 1
                # if len(tran_frame_id_append) > 0 :
                #     if msg.transforms[0].header.frame_id != tran_frame_id_target :
                #         msg.transforms[0].header.frame_id += tran_frame_id_append
                #     msg.transforms[0].child_frame_id += tran_frame_id_append
                #     Y.write(topic, msg, t)
                    
            else:
                for i in range(len(tran_tf_filter_list)):
                    if topic == tran_tf_filter_list[i]:
                        Y.write(topic, msg, t)
                        count_tf[i] += 1
                        break
                # idx_tf = tran_tf_filter_list.find(topic)
                # if idx_tf >= 0:
                #     Y.write(topic, msg, t)
                #     count_tf[idx_tf] += 1
            # elif topic == '/motor/odom_L' or topic == '/motor/odom_R' or topic == '/scan' or topic == '/imu_data':
            #     Y.write(topic, msg, t)
            #     if topic == '/motor/odom_L':
            #         count_odom_L+=1
            #     if topic == '/motor/odom_R':
            #         count_odom_R+=1
            #     if topic == '/scan':
            #         count_scan+=1
            #     if topic == '/imu_data':
            #         count_imu+=1
    print
    print "Result:"
    print "--------------------------------"
    for i in range(len(tran_tf_filter_list)):
        print "%16s" % tran_tf_filter_list[i] ,": ",count_tf[i], "frames"
    print "%16s" % tran_tpoic_robot_pos ,": ",count_robot, "frames"
    #print "{}\t\t\t: {} frames".format(tran_tf_filter_list[i],count_tf[i])
    #print "/robot_pose     : " , count_robot , " frames"
    # print "/motor/odom_L   : " , count_odom_L , " frames"
    # print "/motor/odom_R   : " , count_odom_R , " frames"
    # print "/scan           : " , count_scan , " frames"
    # print "/robot_pose     : " , count_robot , " frames"
    # print "/imu_data       : " , count_imu , " frames"
    print "--------------------------------"
    time_len = (time_end - time_start)/1000000000.0
    print "Time length      : " , time_len , " sec"
    print "Output bag file  : ",bag_dst
    print

def appendFilename(filename,strAppend):
    file_ext_pos = filename.find(".")
    if file_ext_pos == -1:
        return filename+strAppend
    else:
        return filename[0:file_ext_pos] + strAppend + ".bag"


if len(sys.argv) == 2:
    if sys.argv[1].lower().endswith('.bag') : #file mode
        print "File mode"
        bag_dst = appendFilename(sys.argv[1],"_odom")
        processBag(sys.argv[1],bag_dst)
    else: #folder mode
        print "Folder mode"
        if sys.argv[1].endswith("/") :
            folder_name = sys.argv[1]
        else:
            folder_name = sys.argv[1] +"/"
        for file in os.listdir(sys.argv[1]):
            if file.lower().endswith("_odom.bag"):
                print "Skip",file
            elif file.lower().endswith(".bag"):
                bag_dst = appendFilename(file,"_odom")
                processBag(folder_name+file,folder_name+bag_dst)      
elif len(sys.argv) == 3:
    bag_dst = sys.argv[2]
    processBag(sys.argv[1],bag_dst)    
else:
    print "python bag_filter_odom_scan_tf.py from.bag to.bag"


