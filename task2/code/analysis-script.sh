#!/bin/bash
echo Analysing and Generating PNG!!

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

# Create and clear the file to store the results of the analysis
touch results.txt
> results.txt

# Run the analysis for different sizes of cache
for i in ${SIZE}; do
    echo -n "${i} " >> results.txt
    cat ../output/${i}.txt | grep IPC | cut -d ' ' -f 9,10 | grep IPC | cut -d ' ' -f2 >> results.txt 
done

# Plot the results
cat results.txt | graph -T png -h .3 -w .6 > ../reports_and_plots/plot-task2.png

echo Done!!

