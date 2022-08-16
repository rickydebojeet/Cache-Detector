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

OUTPUT_PATH="/home/ricky/Desktop/22D0371/task2/output/"

# Create the output files for the different traces
for i in ${SIZE}; do
    ./run_champsim.sh bimodal-no-no-no-no-lru-1core 1 1 ${i}.champsimtrace.xz
done

cd results_1M/
rename.ul champsimtrace.xz-bimodal-no-no-no-no-lru-1core. "" *.txt

cp *.txt ${OUTPUT_PATH}