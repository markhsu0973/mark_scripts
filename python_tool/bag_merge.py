#!/usr/bin/python

import rosbag
import argparse
from operator import itemgetter

class bag_merge:
    def __init__(self, out_name, sorted_bags):
        self.first_time_ = None
        self.start_sec_ = 0
        self.stop_elapsed_ = 999999999999999
        self.out_file_name_ = out_name
        self.sorted_bags_ = sorted_bags
    def bag_rewriter(self, input_name, output_bag):
        print "processing {}".format(input_name)
        for topic, msg, t in rosbag.Bag(input_name).read_messages():
            if self.first_time_ is None:
                self.first_time_ = t
            duration = ( t - self.first_time_ )
            if duration.to_sec() <= self.start_sec_:
                continue
            elif duration.to_sec() > (self.start_sec_ + self.stop_elapsed_):
                return True
            else:
                output_bag.write(topic, msg, msg.header.stamp if msg._has_header else t)
    def merge(self):
        with rosbag.Bag(self.out_file_name_, 'w') as outbag:
            for bag in self.sorted_bags_:
                self.bag_rewriter(bag, outbag)
            outbag.close()
 
def bag_sort(bag_names):
    augment_list = []
    for name in bag_names:
        entity = []
        number = name.split('_')[1].strip('.bag')
        entity.append(name)
        entity.append(number)
        augment_list.append(entity)
    augment_list = sorted(augment_list, key=itemgetter(1))
    return [row[0] for row in augment_list]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Input "package" and "installed destnation".')
    parser.add_argument('--bags', '-b',  metavar='BAGS', type=str, nargs='*',
                       help='bags merged')
    parser.add_argument('--output', '-o',  metavar='OUT', type=str,
                       help='out put name')

    args = parser.parse_args()
    sorted_bags = bag_sort(args.bags)
    out_file_name = ''
    if args.output is None:
        out_file_name = "merged.bag"
    else:
        out_file_name = args.output
    print sorted_bags

    bgmer = bag_merge(out_file_name, sorted_bags)
    bgmer.merge()
