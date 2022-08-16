#include <stdio.h> 
#include <stdlib.h>
#include <time.h>


#define total 256* 1024 

int main() {
    unsigned int access_times;
    int arr[4* 1024]; 
    int i,j;
    int array_size;
    double time_taken;
    clock_t start;
    int temp;
     int stride[] = { 
        1,2,4,8,16,32,64,128,256};
    array_size = sizeof(arr)/sizeof(int);
    for (i = 0; i < sizeof(stride)/sizeof(int); i++) {
    start = clock();
    for (access_times = 0; access_times< total; access_times++) {
    for (j = 0; j < array_size; j=j+stride[i]) {
	        temp = arr[j];
	       
	    }
    } 

	    time_taken = (double)(clock() - start)/CLOCKS_PER_SEC;
        
        printf("%d,%.8f \n", stride[i], time_taken);
    }
    

    return 0;
}