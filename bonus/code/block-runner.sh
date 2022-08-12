#!/bin/bash
echo Compiling and Generating PNG!!
gcc block-size-finder.c && ./a.out | graph -T png --bitmap-size "1400x1200" -g 3 -L "Time vs Stride" -X "Strides in Power of 2" -Y "Execution Time(s)" > ../blockSize.png 
echo Done!!