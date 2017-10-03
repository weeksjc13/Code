// CSCI 4630
// Program:    2
// Class:      CSCI 4630
// Author:     Josh Weeks
// Date:       2/23/16
// File:       prefix.c

//  Assume: no (zero 0) in the input file

//  Compiling:
//  gcc -lpthread -o prefix prefix.c -lm
//  Throws warnings but still runs fine...
//  ./prefix data.txt


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int A[50];			//original array
int sum[50];			//gets sums from array A
int distance = 1;		//distance of the two indices being added
int total = 0;			//total items in array

pthread_attr_t tattr;		//thread attributes
pthread_t tid;			//thread identifier
pthread_barrier_t barrier;      //barrier that stops threads



void *add(void *threadIds)
{
  int thread_id = *(int*)threadIds;  //current threads ID
  
  sum[thread_id] = A[thread_id] + A[thread_id - distance];
  
  //DEBUGGING
  //printf("add: thread_id: %d     %d + %d     sum[%d] = %d \n", thread_id, A[thread_id], A[thread_id - distance], thread_id, sum[thread_id]);
  
  pthread_barrier_wait(&barrier);
  
  //DEBUGGING
  //printf("thread_id: %d   PAST BARRIER... \n", thread_id);
  
  pthread_exit(NULL);

  return;
}



int main(int argc, char *argv[])
{
  FILE* input = fopen("data.txt", "r");		//input file
  int i;					//counting index
  int count = 0;				//counting index
  
  
  if(input == NULL)
  {
    printf("Error, could not open file.");
  }
  
  //read from file, store into A
  fscanf(input, "%d", &A[count]);
  while(A[count] != 0)
  {
    count++;
    fscanf(input, "%d", &A[count]);
  }
  
  A[count] = -1;				//acts as end of array
  total = count;				//number of items in array
  
  //copy A into sum
  printf("Initial sum array ==> ");
  count = 0;
  while(A[count] != -1)
  {
    sum[count] = A[count];
    printf("%d ", sum[count]);
    count++;
  }
  printf("\n");
  
  int value;					//for error checking
  int threadIds[total - 1];			//id of each thread
  int numberofloops = ceil(log2(total));	//number of runs the distance and barrier updates
  int x = 1;					//number of runs the loop has completed
  int barriernum = total - 1;			//threads to wait for
  
  //initialize attributes
  pthread_attr_init(&tattr);
  pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);
  
  while(x <= numberofloops)
  {
    pthread_barrier_init(&barrier, NULL, barriernum);
    
    barriernum = barriernum - distance;
    
    //create threads
    for(i = total - distance; i > 0; i--)
    {
      threadIds[i] = i;
      value = pthread_create(&tid, &tattr, add, (void*)&threadIds[i + (distance - 1)]);
    
      //error checking
      if(value)
      {
        printf("ERROR: pthread_create returned %d \n", value);
      }
    }
    
    pthread_join(tid, NULL);  //pauses until the barrier is full
    
    //printing the sum array
    printf("Array after distance: %d ==> ", distance);
    int a;
    for(a = 0; a < total; a++)
    {
      printf("%d ", sum[a]);
    }
    printf("\n");
    //done printing sum array
    
    distance = distance * 2;
    
    //copy sum into A
    count = 0;
    while(A[count] != -1)
    {
      A[count] = sum[count];
      count++;
    }
    
    x++;
  }
}
