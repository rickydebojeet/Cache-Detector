#include <stdio.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

/**
 * This program is used to measure block size of cache.
 *
 * The program accesses the array at strides.
 * The strides are powers of 2 ranging from 1 to 2048.
 * The program generates the time taken for the different strides.
 * @return int
 */
int main()
{
    static int arr[5 * MB];
    unsigned int mod = 5 * MB - 1;

    clock_t start, end; ///< used to measure time taken for each stride
    double cpu_time;

    for (int strides = 1, powers = 0; strides <= 2048; strides *= 2, powers++)
    {
        cpu_time = 0; ///< reset the time taken for each stride
        for (int i = 0; i < 10; i++)
        {
            start = clock(); ///< start the timer
            for (unsigned long int steps = 0; steps < 10 * MB; steps++)
            {
                arr[(steps * strides) & mod] = 1; ///< since size is 2^n we can use bitwise and to get the remainder
            }
            end = clock();                                      ///< stop the timer
            cpu_time += (double)(end - start) / CLOCKS_PER_SEC; ///< add the time taken for each iteration
        }
        cpu_time /= 10; ///< get the average time taken for each stride
        printf("%d %.20f\n", powers, cpu_time);
    }
    return 0;
}