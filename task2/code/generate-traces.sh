#!/bin/bash
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


for i in ${SIZE}; do
	./pin -t /home/ricky/Desktop/ChampSim/tracer/obj-intel64/champsim_tracer.so -o ${i}.champsimtrace -t 1000000 -- /home/ricky/Desktop/Cache-Detector/task2/code/a.out ${i}
    xz ${i}.champsimtrace
done