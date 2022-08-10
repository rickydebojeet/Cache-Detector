
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define KB 1024
#define MB KB*KB
#define MAX_DATA_SIZE 64 * MB
#define NO_OF_SIZES 30

double sizeFactor[2] = {3.0/4, 2.0/3};
char dataArr[64 * MB];
static int cache[5];
double blockSize;

/* finds the percentage drop in time from time_one to time_two */
double getPercentageDiff(double time_one, double time_two){
   return((time_one - time_two)/time_one * 100);
}

/* ufinds the time difference in seconds between two time clock_t */
double getTimeDiff(clock_t start, clock_t end){
   return (double)(end - start)/CLOCKS_PER_SEC;
}

/**
* It allocates a memory of "jumpUptoInBytes" bytes size and iterates 
* through the memory with jump step of "jumpStepInBytes" bytes. In order to 
* make same amount of access to the memory for each memory size, the memory 
* access is repeated "noOfIteration" times. For example, for each of 64MB, 
* 48MB, 32MB, 24MB, 16MB ...etc., number of accesses are same.
*
* @param noOfIteration 
*              parameter to adjust same amount of access for each size of memory
* @param jumpStepInBytes 
*              jump step in bytes, e.g., if jump step is 64 bytes 
*              then this loop will try to access every next 64th bytes.
* @param jumpUptoInBytes
*              size of memory block to be accessed/allocated
* @return 
*        total time to access "jumpUptoInBytes" bytes memory block with jump step of "jumpStepInBytes" bytes 
*        for "noOfIteration" times
*/
double loop(int noOfIteration, int jumpStepInBytes, int jumpUptoInBytes){
   double timeForLoop;
   int repeat, i;
   clock_t startTime, endTime;
   
   startTime = clock();
   for (repeat = 0; repeat < noOfIteration; repeat++){
	  for(i = 0; i < jumpUptoInBytes; i += jumpStepInBytes){
		 dataArr[i]++;
	  }
   }
   endTime = clock();
   return getTimeDiff(startTime, endTime);
}

/* this method computes number of cache level and their sizes */
void computeCacheSize(){
   int noOfIteration = 1024;
   int jumpStep = 128;
   int jumpUptoInBytes;
   
   /* parameter used to adjust the time of execution of this function */
   int loopFactor;
   double timeForNLoops;
   
   int N = 50;
   
   /* data structure to store percentage diff and drop going from 64MB to 4KB */
   double perDiff[NO_OF_SIZES];
   int sizes[NO_OF_SIZES];
   
   double currentTimeTaken = 0, previousTimeTaken = 0;
   
   // parameters in loop to adjust the total number of iteration
   int innerLoop = 0;
   int newInnerLoop = 0;
   
   // no of memory sizes for which time has been computed so far.
   int sizeCount = 0;
   int s, k = 0,i = 0;
   
   double prevPerDrop = 0;
   double threshold;
   int isNextLikely;
  
   /* adjust no of iteration of loop so that the time for (MAX_DATA_SIZE - 1) is 45 sec*/
   timeForNLoops = loop(N, jumpStep, MAX_DATA_SIZE);
   loopFactor = (int)N/timeForNLoops * 60;
   
   noOfIteration = loopFactor; //iteration for first memory size i.e. 64MB
   jumpUptoInBytes = MAX_DATA_SIZE;
   
   perDiff[0] = 0;
   
   /* 
   * find the time for the loop for each memory sizes from 64MB down to 4KB, 
   * assuming that the cache size is always > 4KB 
   */
   for(s = 0; jumpUptoInBytes >= 4 * KB ; s++){
	   
      previousTimeTaken = currentTimeTaken;
      currentTimeTaken = loop(noOfIteration, jumpStep, jumpUptoInBytes);
      
      /* 
      * for first memory block there is no previousTimeTaken so ignoring that and storing 
      * percentage drop in time for the loop
      */
      if(previousTimeTaken != 0){
        perDiff[s] = getPercentageDiff(previousTimeTaken, currentTimeTaken);
      } 
      /* storing sizes that were checked */
      sizes[s] = jumpUptoInBytes;
      //printf("Size ==> %d,\t time==> %.8f, \t per Diff: %.8f\n", jumpUptoInBytes,currentTimeTaken, perDiff[s]);
      
      /* finding count of inner loop in current double loop to adjust noOfIteration in next round */
      innerLoop = (jumpUptoInBytes/jumpStep);
      //printf("jumpUptoInBytes: %d,\tnoOfIteration: %d, \t inner loop size: %d\n",jumpUptoInBytes,noOfIteration, innerLoop);
      
      /* 
      * selecting next size of memory to access from size factor alternatively i.e. {3/4 or 2/3} 
      * choosen memory sizes -> 
      * { 64MB, 48MB, 32MB, 24MB, 16MB, 12MB, 8MB, 6MB, 5MB, 4MB, 3MB, 
      * 2MB, 1MB, 512KB, 256KB, 128KB, 64KB, 32KB, 16KB, 8KB, 4KB }
      */


      if(jumpUptoInBytes >2 * MB){
         if(jumpUptoInBytes == 6 * MB){ //following step doesn't include 5MB so adding 5MB manually
            jumpUptoInBytes = 5 * MB; 
         }else{
            if(jumpUptoInBytes == 5 * MB){
               jumpUptoInBytes = 6*MB;
            }
            jumpUptoInBytes = jumpUptoInBytes * sizeFactor[k];
            k = (k + 1)%2;
         } 
      }else{
         jumpUptoInBytes /= 2;
      }
      //computing noOfIteration required in next loop
      newInnerLoop = jumpUptoInBytes/jumpStep;
      noOfIteration = (int) (noOfIteration * ((float)innerLoop/newInnerLoop));
   }

   /* with the time information obtained from above loops, finding the no. of cache and their sizes*/
   sizeCount = s;
   threshold = 20.0;
   isNextLikely = 1;
   i = 0;
   cache[0] = cache[1] = cache[2] = cache[3] = cache[4] = 0;
   
   /* 
   * going from 64MB to 4KB, if percentage drop is > 20 then that's our one of the cache level.
   * If current memory is cache, consecutive next memory is unlikely that the next memory to be next cache level.
   * After first cache level finding, next memory will not be our next cache until percentage drop 
   * from cache level to current memory is greater than 10
   */
   for(s = 1; s < sizeCount; s++){
       
       /* if cache size is less than 32*KB,  with data gained from several runs, 3.6 seems to be a reasonable threshold*/
       if(sizes[s] < (32 * KB)){
		      threshold = 3.6;
	     }
  	  if(isNextLikely){
          if(perDiff[s] > threshold){
    				cache[i] = sizes[s];
    				i++;
    				prevPerDrop = perDiff[s];
    				isNextLikely = 0;
  		    }
      }else{
         if(prevPerDrop - perDiff[s] > 10){
            isNextLikely = 1;
			      threshold = 15.0;
         }
      }
  }
}

/* 
* This function computes block size of cache. 
* It goes through memory of size MAX_DATA_SIZE from 0 to max size with differnt jump step bytes from
* 256B, 128B, 64B, 32B, 16B, 8B, and 4B
* Assumption: Blocksize is not less 4B (4 bytes)
*/
int computeBlockSize(){
   int noOfIteration = 4500; // no of iteration for approx 1 minutes in romulan2
   int jumpStep = 256;
   double prevTimeTaken = 0, currentTimeTaken = 0;
   double ratio, threshHoldRatio = 1.90;
   int prevBlockSize = jumpStep;
   
   /* jumpstep goes from 256B down to 4B */
   do{
     prevTimeTaken = currentTimeTaken;
     currentTimeTaken = loop(noOfIteration, jumpStep, MAX_DATA_SIZE);
     
     if(prevTimeTaken != 0){
        ratio = prevTimeTaken/currentTimeTaken;
        //printf("Jump Step: %d bytes\t Time taken by CPU: %.8f\t ratio: %.8f\n ", jumpStep,currentTimeTaken, ratio);
     	if(ratio>threshHoldRatio){
           return prevBlockSize;
        }
     }
     prevBlockSize = jumpStep;
     jumpStep = jumpStep / 2;
     noOfIteration /= 2;
   }while(jumpStep >= 4);
   
   return prevBlockSize;
}
/*
* loop to to access certain memory repeatedly to find the associativity of given cache
* @param outerLoop: 
*			just a constant outer loop
* @param innerLoop: 
*			a loop to maintain a same access amount the memory for varying innerMostLoop
* @param innerMostLoop: 
*			inner most loop can be 1, 2, 4, 8, 16, .... depends on 
*			how many cache size memory from next level you want to access.
*/
double loopForAssociativity(int outerLoop, int innerLoop, int innerMostLoop, int cacheSize){
    double timeTaken = 0;
    clock_t startTime, endTime;

    int i,j,k,m; 
    //printf("outer loop: %d, \t inner loop: %d\t innermost loop: %d\t", outerLoop, innerLoop, innerMostLoop);
    startTime = clock();
    for(i = 0;i<outerLoop;i++){
      for(j = 0; j < innerLoop; j++){
        k = 0;
        for(m = 0; m < innerMostLoop; m++){
          dataArr[k]++;
          k = k + cacheSize;
        }
      }
    }
    endTime = clock();
    
    return getTimeDiff(startTime, endTime);
}
/* 
* function to compute the associativity of cache
* This function seems to work only for level-1 cache
* One assumption made here is that the max associativity is half the no. of blocks in the given cache.
*/
int computeAssociativity(int cacheSize){

   int l, assoc;
   int numOfBlocks = cacheSize/blockSize;
   int maxAssoc = numOfBlocks/2;
   double previousTimeTaken = 0, currentTimeTaken = 0, timeTakenFor10Loops = 0;
   double ratio = 0;
   int outerLoop = 50, innerLoop=64 * MB;
   double ratioThreshold = 3.0;

   /* if level one cache size is < 32 * KB, it seems ratioThreshold seems to be < 3 and > 1.5 */
   if(cacheSize < 32 * KB){  ratioThreshold = 1.5; }
   
   currentTimeTaken = 0;
   //printf("\nCache Size : %d,\t max Assoc : %d\n", cacheSize, maxAssoc);
   for(l = 1 ; l <= maxAssoc;  l *= 2){
      previousTimeTaken = currentTimeTaken;
      currentTimeTaken = loopForAssociativity(outerLoop, innerLoop, l, cacheSize);
      if(previousTimeTaken != 0){
          ratio = currentTimeTaken/previousTimeTaken;
		    
          if(ratio > ratioThreshold){
        			assoc = l/2;
        			if(cacheSize < 32 * KB){
        				assoc = l;
        			}
        			//return assoc;
		      }  
      }
      innerLoop /= 2;
      //printf("Time taken : %.8f, \t Ratio: %.8f\n", currentTimeTaken, ratio);   

   }
   return assoc;
}

/* your main program*/
int main(){
   int s, i;
   /** 
   * Cache information of available machine in UAB moat 
   * vulcan 0  ==> Associativity = 8, CPU MHz: 3200.194, L1 : 16 * KB, L2 : 2048 * KB 	doesn't work 16KB level-1
   * vulcan 3  ==> Associativity = 8, CPU MHz: 3200.194, L1 : 16 * KB, L2 : 2048 * KB  
   * romulan 0 ==> Associativity = 8, CPU MHz: 1200.000, L1 : 32 * KB, L2 : 256 * KB,  L3: 12288 * KB ==> pass 875secs
   * romulan 2 ==> Associativity = 2, CPU MHz: 0800.000, L1 : 64 * KB, L2 : 512 * KB,  L3: 5118 * KB  ==> pass 552secs
   * romulan 3 ==> Associativity = 2, CPU MHz:           L1 : 32 * KB, L2 : 64 * KB,   L3: 
   * my mac    ==> Associativity = 8, CPU MHz: 2500.000, L1 : 32 * KB, L2 : 256 * KB 
   */
    blockSize = computeBlockSize();
    printf("\nBlock Size: %.2f\n",blockSize);
  
   computeCacheSize();
   
   s = 0;
   while(cache[s]!=0){
	   s++;
   }
   
   for(i = s; i>0; i--){
	    printf("Cache %d: %d \n", (s - i + 1), cache[i - 1]);
   }
   printf("\nNumber of cache levels: %d\n", s);

   printf("\nWays of Associativity of level-1 cache : %d\n", computeAssociativity(cache[s-1]));
   
   return (0);
}
