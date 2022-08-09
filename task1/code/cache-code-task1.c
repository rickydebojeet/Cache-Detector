// Generate cache sizes of my computer
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *ip = argv[1];
    long int size = strtol(ip, NULL, 10);
    double arr[size];
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (long int i = 0; i < size; i++)
    {
        arr[i] = 1;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for 1D array: %f\n", cpu_time_used);
    return 0;
}