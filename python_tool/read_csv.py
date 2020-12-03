#! /usr/bin/env python
import csv
import numpy as np

with open('output.csv', 'w') as csvfile:

  writer = csv.writer(csvfile)


  writer.writerow(['name',1])

  writer.writerow(['Tom',2])
  writer.writerow(['John',3])
with open("output.csv","r") as csvfile:
	reader = csv.reader(csvfile)
	for line in reader:
		print line[0], ", ", line[1]
