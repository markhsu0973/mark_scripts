#########################################
#python csv-2-graph-line-chart.py folder_name#
#########################################
from csv import reader
from matplotlib import pyplot as plt
import sys, getopt
import glob, os
import os.path
import statistics

def draw(inputfiles):
    # To draw a double y-axis figure
    # change x label here
    x_label = 'Samples'

    # change y label here
    # y1_label = 'Acceleration (g)'
    # y1_limit = [-0.5, 1.5]
    
    y1_label = 'Distance (m)'
    # y1_limit = [0, 5]

    # read data from input file
    data = list()
    with open(inputfiles, 'r') as f:
        data = list(reader(f))
    # data_title = data[0][0]
    # print data_title
    # print 'data length: ',len(data)*0.020, 'seconds'

    # add data into figure
    x_data=[]
    y1_data=[]
    # y2_data=[]
    # y3_data=[]
    data_inf = 0
    for i in range(len(data)-2):
        # print data[i][3]
        
        if float(data[i][0]) == 0.0:
            # y1_data.append(0)
            data_inf += 1
        else:
            x_data.append(i)
            y1_data.append(float(data[i][0]))
        # print data[i][0]
        # y2_data.append(data[i+1][1])
        # y3_data.append(data[i+1][2])

    y1_limit = [statistics.mean(y1_data)-statistics.stdev(y1_data)*10, statistics.mean(y1_data)+statistics.stdev(y1_data)*10]
    # initial figure
    fig, ax1 = plt.subplots()
    # ax3 = ax2 = ax1

    
    # set color of lines
    ax1.plot(x_data, y1_data, 'r-', label=str(inputfiles).split("/")[-1])
    # ax2.plot(x_data, y2_data, 'b-', label=data[0][1])
    # ax3.plot(x_data, y3_data, 'g-', label=data[0][2])

    plt.legend()

    # set label font
    ax1.set_xlabel(x_label, fontsize=16)
    ax1.set_ylabel(y1_label, fontsize=16)

    # set axis range of y1 and y2
    ax1.set_ylim(y1_limit)

    # save figure 
    save_file = inputfiles + '.png'
    ax1.text(10, statistics.mean(y1_data)-statistics.stdev(y1_data)*8, 'average: '+str(format(statistics.mean(y1_data),'.3f')), fontsize=14)
    ax1.text(10, statistics.mean(y1_data)-statistics.stdev(y1_data)*7, 'stdev: '+str(statistics.stdev(y1_data)), fontsize=14)
    ax1.text(10, statistics.mean(y1_data)-statistics.stdev(y1_data)*6, '0 count: '+str(data_inf), fontsize=14)
    plt.savefig(save_file)
    plt.clf()
    f.close
    return 0

def find_file(argv):
    # load path from argument, need abslutely path now
    file_path = argv[0]
    print argv[0]
    # find all file start with corresponding string
    listOfFiles = list()
    for (dirpath, dirnames, filenames) in os.walk(file_path):
        for file in filenames:
            # if file.startswith("IMU_ang"):
            listOfFiles += [os.path.join(dirpath, file)]

    os.chdir(file_path)

    # draw figures 
    for i in range(len(listOfFiles)):
        print 'Nember ', i+1, '/', len(listOfFiles), ' file: ', listOfFiles[i]
        draw(listOfFiles[i])

    print 'File number: ', len(listOfFiles)

if __name__ == "__main__":
    find_file(sys.argv[1:])
