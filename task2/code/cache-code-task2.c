#include <stdio.h>
#include <stdlib.h>

#define K 1024
#define M 1024 * 1024

int power(int);

int main(int argc, char* argv[])
{
    int input = atoi(argv[1]);
    int size = power(input);

    int* arr = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < 10; i++)
    {
        for(unsigned long int steps = 0; steps < 10 * M; steps++)
        {
            arr[(steps * 16) & (size - 1)]++;
        }
    }
    free(arr);
    return 0;
}

int power(int n)
{
    int result = 1;
    for(int i = 1; i <= n; result *= 2, i++ );
    return result;
}