#!/bin/bash
echo Compiling the file!!
gcc block-size-finder.c && ./a.out | graph -T png -h .3 -w .6 > ../blockSize.png 
echo Done!!