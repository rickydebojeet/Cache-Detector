#!/bin/bash
echo Analysing and Generating PNG!!

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

touch results.txt
> results.txt

for i in ${SIZE}; do
    echo -n "${i} " >> results.txt
    cat ../output/${i}.txt | grep IPC | cut -d ' ' -f 9,10 | grep IPC | cut -d ' ' -f2 >> results.txt 
done

cat results.txt | graph -T png -h .3 -w .6 > ../reports_and_plots/plot-task2.png

echo Done!!

