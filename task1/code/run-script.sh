#!/bin/bash
echo Compiling and Generating PNG!!
# Generating plot till 1 MB Arrays
gcc cache-code-task1.c && ./a.out 20 | graph -T png --bitmap-size "1400x1200" -g 3 -L "Time vs Size" -X "Size in Powers of 2" -Y "Execution Time(s)" > ../reports_and_plots/plot-task1-precise.png
# Generating plot till 16 MB Arrays
gcc cache-code-task1.c && ./a.out | graph -T png --bitmap-size "1400x1200" -g 3 -L "Time vs Size" -X "Size in Powers of 2" -Y "Execution Time(s)" > ../reports_and_plots/plot-task1.png
echo Done!!