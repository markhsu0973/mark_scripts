#!/usr/bin/python

ifn = r"123.txt"
ofn = r"train_output.txt"

infile = open(ifn,'rb')
outfile = open(ofn,'wb')

for eachline in infile.readlines():
        lines = filter(lambda ch: ch not in ' ', eachline)

        outfile.write(lines)

infile.close
outfile.close
