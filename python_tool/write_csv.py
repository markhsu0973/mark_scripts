#! /usr/bin/env python
import csv


with open('output.csv', 'w') as csvfile:

  writer = csv.writer(csvfile)


  writer.writerow(['name'])

  writer.writerow(['Tom'])
  writer.writerow(['John'])