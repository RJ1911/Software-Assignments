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
    ./a           or     ./16_1.exe
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
    for (int i = 0; i < cacheSize; i++)
        arr_elems[i] = -1;

    hit = 0;
    for (int j = 0; j < referenceCount; j++)
    {
        int num = references[j];
        bool found = false;
        for (int i = 0; i < cacheSize; i++){
            if (arr_elems[i] == num){
                hit++;
                found = true;
                for (int k = i; k > 0; k--)
                    arr_elems[k] = arr_elems[k - 1];
                arr_elems[0] = num;
                break;
            }
        }
        if (!found)
        {
            for (int k = cacheSize - 1; k > 0; k--)
                arr_elems[k] = arr_elems[k - 1];
            arr_elems[0] = num;
        }
    }
    cacheHitRatio = (1.0 * hit) / referenceCount;
    printf("Hit Ratio of the program is = %.1lf\n",cacheHitRatio);
}

// variables for queue implementation of fifo   
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

    for (int i = 0; i < cacheSize; i++)
        q_elems[i] = -1;
    
    hit = 0;

    for (int j = 0; j < referenceCount; j++)
    {
        bool found = false;
        int num = references[j];
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
    cacheHitRatio = (1.0 * hit) / referenceCount;

    printf("Hit Ratio of the program is = %.1lf\n", cacheHitRatio);
}

int main(int argc,char *argv[])     // command line arguments
{
    referenceCount=argc-4;
    cacheSize = (int)*argv[1]-48;
    cacheAlgoType = (char)*argv[3];
    mainMemsize=(int)atoi(argv[2]);    // atoi is used to convert string to integer
    
    
    references = (int*)malloc((argc - 4)*sizeof(int));
    for (int i = 0; i < argc - 4; i++){
        references[i] = (int)*argv[i+4]-48;
    }
    //error case 
    if (mainMemsize != 32 && mainMemsize != 64 && mainMemsize != 128)
        printf("Error,Value of main memory size should be one of  32/64/128.\n");
    else
    {    // error case 
        if (cacheSize>mainMemsize/4)
            printf("Error, Value of cache size should not exceed 1/4 of main memory size.\n");
        else
        {   int referenceLength = argc-4;
            bool referenceBool = true; 
            for (int i = 0; i < referenceLength; i++){
                if (references[i]>= mainMemsize || references[i]< 0)
                {
                    referenceBool = false;
                    break;
                }
            }
            //error case
            if (!referenceBool)
                printf("Main memory block references should be non-negative and less than main memory size.\n");
            else
            {
                switch (cacheAlgoType)
                {
                    case 'F':
                        FIFO();
                        break;
                    case 'L':
                        LRU();
                        break;
                }
            }
        }
    }

    return 0;
}
/* 
SAMPLE CASES:

sample case 1 -
input 
 4 32 F 1 2 3 1 4 5 1 4 3 6

output 1 -
Hit Ratio of the program is = 0.3

sample  case 2 -
input 
4 32 L 1 2 3 1 4 5 1 4 3 6

output 2 -
Hit Ratio of the program is = 0.4
*/