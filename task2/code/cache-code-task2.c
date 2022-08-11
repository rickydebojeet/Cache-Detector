#include <stdio.h>
#include <stdlib.h>

#define K 1024
#define M 1024 * 1024

int power(int);

/**
 * This program is used to measure different caches of the CPU.
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @return int
 *
 * The program takes the size of the array as a command line argument.
 * It allocates an array of the given size and accesses it for equivalent time
 */
int main(int argc, char *argv[])
{
    int input = atoi(argv[1]); ///< size of the array in log2(bytes)
    int size = power(input) / sizeof(int);

    int *arr = (int *)malloc(sizeof(int) * size);
    for (unsigned long int steps = 0; steps < 10 * M; steps++)
    {
        arr[(steps * 16) & (size - 1)]++; ///< since size is 2^n we can use bitwise and to get the remainder
    }
    free(arr);
    return 0;
}

/**
 * This function calculates the power of 2
 * @param n: the power to be calculated
 * @return int: the power of 2
 */
int power(int n)
{
    int result = 1;
    for (int i = 1; i <= n; result *= 2, i++)
        ;
    return result;
}