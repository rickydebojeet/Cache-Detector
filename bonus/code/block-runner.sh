#!/bin/bash
echo Compiling and Generating PNG!!
gcc block-size-finder.c && ./a.out | graph -T png -h .3 -w .6 > ../blockSize.png 
echo Done!!