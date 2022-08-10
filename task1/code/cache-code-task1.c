// Generate cache sizes of my computer
#include <stdio.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

int main()
{
    static int arr[64 * MB];
    unsigned long int sizes[] = {1 * KB, 2 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 
    128 * KB, 256 * KB, 512 * KB, 1 * MB, 2 * MB, 4 * MB, 8 * MB, 16 * MB, 32 * MB, 64 * MB
    };
    
    int sizeOfSizes = sizeof(sizes)/sizeof(unsigned long int);

    clock_t start, end;
    double cpu_time;

    for (int looper = 0, power = 10; looper < sizeOfSizes; looper++, power++)
    {
        cpu_time = 0;
        for(int i = 0; i < 10; i++)
        {
            start = clock();
            for (unsigned long int steps = 0; steps < 10 * MB; steps++)
            {
                arr[(steps * 16) & (sizes[looper] - 1)]++;
            }
            end = clock();
            cpu_time += (double)(end - start) / CLOCKS_PER_SEC;
        
        }
        cpu_time /= 10;
        printf("%d %.30f\n", power, cpu_time);
    }
    return 0;
}