// Generate cache sizes of my computer
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 1024
#define M 1024 * 1024

int main()
{
    clock_t start, end;
    double cpu_time;
    int size;

    for (int size = 1024/sizeof(int), power = 10; power <= 26; size *=2, power++)
    {
        int* arr = (int *)malloc(sizeof(int) * size);
        cpu_time = 0;
        for(int i = 0; i < 10; i++)
        {
            start = clock();
            for (unsigned long int steps = 0; steps < 10 * M; steps++)
            {
                arr[(steps * 16) & (size - 1)]++;
            }
            end = clock();
            cpu_time += (double)(end - start) / CLOCKS_PER_SEC;
        
        }
        cpu_time /= 10;
        printf("%d %.30f\n", power, cpu_time);
        free(arr);
    }
    return 0;
}