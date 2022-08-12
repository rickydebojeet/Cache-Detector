#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 1024
#define M 1024 * 1024

/**
 * This program is used to measure different caches of the CPU.
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @return int
 * 
 * The program allocates arrays of different sizes and accesses them for equivalent time
 * Checks the time taken for each array size and prints the results
 * By default it allocates upto 16 MB but can be changed using Command Line Arguments
 */
int main(int argc, char *argv[])
{
    int limit;
    if (argc > 1)   
        limit = atoi(argv[1]); ///< setting manual limit
    else
        limit = 24; ///< default limit
    
    clock_t start, end; ///< used to measure time taken for each array size
    double cpu_time;

    /**
     * Allocate arrays of different sizes
     *
     * size: size of the array in bytes.
     * power: power of 2 to be used to calculate the size of the array.
     *
     * The loop allocates arrays of size 2^power bytes 
     * By default the power ranges from 10 to 24 that is the array size ranges form 1KB to 16MB.
     * But it can be changed by giving command line argument
     */
    for (int size = 1024 / sizeof(int), power = 10; power <= limit; size *= 2, power++)
    {
        int *arr = (int *)malloc(sizeof(int) * size);
        cpu_time = 0; ///< reset the time taken for each array size

        for (int i = 0; i < 10; i++)
        {
            start = clock(); ///< start the timer
            /**
             * Access the array for equivalent number of times
             *
             * steps: number of acceses to the array
             *
             * The loop accesses the array at an interval of 64 bytes
             * so that if there is cache miss every time it is trying to access the array
             */
            for (unsigned long int steps = 0; steps < 20 * M; steps++)
            {
                arr[(steps * 16) & (size - 1)]++; ///< since size is 2^n we can use bitwise and to get the remainder
            }
            end = clock();                                      ///< stop the timer
            cpu_time += (double)(end - start) / CLOCKS_PER_SEC; ///< add the time taken for each iteration
        }
        cpu_time /= 10; ///< get the average time taken for each array size
        printf("%d %.30f\n", power, cpu_time);
        free(arr);
    }
    return 0;
}