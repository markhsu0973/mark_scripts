#!/bin/bash

g++ $1.cpp -lpthread -o $1
#g++ $1.cpp -o $1

echo "<<===== start $1 cpp =====>>"
./$1

echo "<<===== stop $1 cpp ======>>"
