#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

int main() {
    unsigned int steps = 512 * 1024 * 1024;
    static int arr[20* 1024 * 1024];
    int lengthMod;
    unsigned int i,j;
    double time_taken;
    clock_t start;
    int temp;
    int sizes[] = { 
        1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB,
        512 * KB, 1 * MB, 2 * MB, 4 * MB, 8 * MB, 16 * MB, 18 * MB, 20 * MB
    };
   int array_element = sizeof(sizes)/sizeof(int);
    // for each size to test for ... 
    for (i = 0; i < array_element; i++) {
	    lengthMod = sizes[i] - 1;
	    start = clock();
	    for (j = 0; j < steps; j++) {
	        temp = arr[(j* 16) & lengthMod];
	       
	    }

	    time_taken = (double)(clock() - start)/CLOCKS_PER_SEC;
        printf("%d, %.8f \n", sizes[i] / 1024, time_taken);
    }

    return 0;
}