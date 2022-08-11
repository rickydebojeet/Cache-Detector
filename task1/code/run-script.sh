#!/bin/bash
echo Compiling and Generating PNG!!
# Compile the code and generate the PNG
gcc cache-code-task1.c && ./a.out | graph -T png -h .3 -w .6 > ../reports_and_plots/plot-task1.png
echo Done!!