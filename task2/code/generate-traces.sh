#!/bin/bash
# Different Sizes of Cache
SIZE='
10
11
12
13
14
15
16
17
18
19
20
21
22
23
'

CHAMPSIM_PATH="/home/ricky/Desktop/ChampSim/"
EXECUTABLE_PATH="/home/ricky/Desktop/Cache-Detector/task2/code/a.out"
TRACES_PATH="/home/ricky/Desktop/Cache-Detector/task2/traces/"

# Create the traces for the different sizes of cache
for i in ${SIZE}; do
	./pin -t ${CHAMPSIM_PATH}tracer/obj-intel64/champsim_tracer.so -o ${i}.champsimtrace -t 1000000 -- ${EXECUTABLE_PATH} ${i}
    xz ${i}.champsimtrace
done

cp *.xz ${TRACES_PATH}