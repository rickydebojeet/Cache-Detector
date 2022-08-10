#include <stdio.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

int main()
{
    // Initializing an integer array of size 20 MB
    static int arr[5 * MB];

    // Finding mod value since for powers of 2; a % b = a & (b - 1)
    unsigned int mod = 5 * MB - 1;

    // Variables for storing time related values
    clock_t start, end;
    double cpu_time;

    for (int strides = 1, powers = 0; strides <= 2048; strides *= 2, powers++)
    {
        cpu_time = 0;
        for (int i= 0; i < 10; i++)
        {
            start = clock();
            for (unsigned long int steps = 0; steps < 10 * MB; steps++)
            {
                arr[(steps * strides) & mod] = 1;
            }
            end = clock();
            cpu_time += (double)(end - start) / CLOCKS_PER_SEC;
        }
        // Average CPU time
        cpu_time /= 10;
        printf("%d %.20f\n", powers, cpu_time);
    }
    return 0;
}