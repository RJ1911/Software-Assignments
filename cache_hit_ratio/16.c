 /*
 Team No. 16
 1. Sumanta Kumar Paul    roll 063
 2. Shivam Das            roll 059
 3. Rafson Jani           roll 008
 4.Shivam Patel           roll 072
 */

/*
 Assignment details
 INPUT -
the program will accept variable number of arguments;
the first one is the size of the Cache (in multiple of cache block),
the second one is the size of the main memory (in multiple of cache block) and
the third one is the type of Cache Replacement Algorithm (FIFO or LRU).
After the third argument, there will be sequence of memory block references.
The value of the first argument should be not more than one-fourth of the main memory size
The value of the 2nd argument should be one of 32/64/128.
The value of the third argument should be either F (for FIFO) or L (for LRU).
And the values of the fourth argument onwards are the sequence of main memory block references (in numbers upto 31/63/127).
All these arguments should be taken from command line (using argc/argv etc.).
OUTPUT -
the  program should run the relevant algorithm and ultimately compute and 
display the Cache Hit Ratio. Refer to the course material regarding computing the Cache Hit Ratio.
*/
/*
 * compilation command.
    gcc 16_1.c       or   gcc 16_1.c -o 16_1
 * Put the execution sequence.
    ./a  input          or     ./16_1.exe input 

 */
// SAMPLE CASES AT THE END

// Cache handling
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// variables
char cacheAlgoType;
int cacheSize, mainMemsize,hit,referenceCount;
int *references;
double cacheHitRatio;

// variables for array implementation of lru
int length;
int *arr_elems;

// LRU  algorithm
void LRU() 
{
    length = cacheSize;
    arr_elems = (int *)malloc(cacheSize * sizeof(int));

    //initialising arr_elems array with -1

    for (int i = 0; i < cacheSize; i++)
        arr_elems[i] = -1;

    hit = 0;
    for (int j = 0; j < referenceCount; j++)
    {
        int num = references[j];
        bool found = false;
        // finding the no. in cache
        for (int i = 0; i < cacheSize; i++){
            if (arr_elems[i] == num){
                hit++;
                found = true;
                // if no. is found make it most recently used no. 
                for (int k = i; k > 0; k--)
                    arr_elems[k] = arr_elems[k - 1];
                arr_elems[0] = num;
                break;
            }
        }
        if (!found) // then replace lru no. with the given no. in the cache  
        {
            for (int k = cacheSize - 1; k > 0; k--)
                arr_elems[k] = arr_elems[k - 1];
            arr_elems[0] = num;
        }
    }
    cacheHitRatio = (double) hit / referenceCount;
    printf("Hit Ratio of the program is = %.2lf\n",cacheHitRatio);
}

// variables for circular queue implementation of fifo   
int front, rear, size;
int *q_elems;

void dequeue(){

    if (front == rear){
        front = -1;
        rear = -1;
    }
    else
    front=(front+1)%size;
}

void enqueue(int input){
   // first we dequeue for following condition
    if ((front == 0 && rear == size - 1) || (front == rear + 1))
        dequeue();

    if (front == -1)
        front = 0;
        
    rear = (rear + 1) % size;
    q_elems[rear] = input;
}
// FIFO algorithm
void FIFO() 
{
    front = -1;
    rear = -1;

    size = cacheSize;
    q_elems = (int *)malloc(cacheSize * sizeof(int));

//initialising q_elems array with -1

    for (int i = 0; i < cacheSize; i++)
        q_elems[i] = -1;
    
    hit = 0;

    for (int j = 0; j < referenceCount; j++)
    {
        bool found = false;
        int num = references[j];
        // for finding the number in cache, if found we increase hit 
        for (int i = 0; i < cacheSize; i++){

            if (q_elems[i] == num){
                found = true;
                hit++;
                break;
            }
           }
        if (!found)
            enqueue(num);
    }
    cacheHitRatio = (double)hit / referenceCount;

    printf("Hit Ratio of the program is = %.2lf\n", cacheHitRatio);
}

int main(int argc,char *argv[])     // command line arguments
{  
    int totalreference=argc;
   if (argc<=4 )  // no input
    {
        printf("Error : *No input given*\nPlease enter valid no. of arguments");
        return 0;
    }

    referenceCount=argc-4;
    // to convert string to integer
    cacheSize = (int)atoi(argv[1]);
    mainMemsize=(int)atoi(argv[2]);

    cacheAlgoType = (char)*argv[3];
   
    references = (int*)malloc((argc - 4)*sizeof(int));

    for (int i = 0; i < argc - 4; i++){
        references[i] = (int)atoi(argv[i+4]);
    }


  //1    
   if (mainMemsize != 32 && mainMemsize != 64 && mainMemsize != 128)  // cross-checking the correctness of the size of the main memory 
    {
        printf("Error : Size of main memory should be should be either 32 or 64 or 128!");
        return 0;
    }
//2
    if (cacheSize > mainMemsize / 4 || cacheSize < 1)        // cross-checking the correctness of the size of the cache memory 
    {
        printf("Error : Size of cache should not be more than 1/4th of the size of main memory!");
        return 0;
    }

//3    
    for (int i = 0; i < referenceCount; i++)   
    {
        if (references[i] >= mainMemsize || references[i] < 0)   // cross-checking the correctness of the references 
        {
            printf("Error : The memory block reference %d is not valid!\nIt must be smaller than main memory size(%d).\n" , references[i] , mainMemsize);
            return 0;
        }
    }


    if(cacheAlgoType=='F')
         FIFO();
     else if(cacheAlgoType=='L')
         LRU();
     else 
        printf("Error : The type of cache replacement algorithm should be either F or L");
         
    return 0;
}
/* 
SAMPLE CASES:

sample case 1 -
input 
 4 32 F 1 3 2 1 4 6 1 4 1 6

output 1 -
Hit Ratio of the program is = 0.40

sample  case 2 -
input 
4 32 L 1 3 2 1 4 6 1 4 1 6

output 2 -
Hit Ratio of the program is = 0.50
*/