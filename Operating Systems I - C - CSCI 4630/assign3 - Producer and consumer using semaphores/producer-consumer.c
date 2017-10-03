// CSCI 4630
// Program:    3
// Class:      CSCI 4630
// Author:     Josh Weeks
// Date:       3/30/16
// File:       producer-consumer.c


//Compiling notes:
//gcc -o producer-consumer producer-consumer.c -lpthread -lm
//./producer-consumer x
//x being the number of items produced and consumed


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define size 10  //size of buffer

//semaphores
sem_t empty;
sem_t full;
sem_t mutex;

//functions
void *producer();
void *consumer();

//files
FILE *producerFile;
FILE *consumerFile;

int buffer[size];  //buffer array
int x;             //number of items to be consumed/produced
int in = 0;        //index for producer in buffer array
int out = 0;       //index for consumer in buffer array



int main(int argc, char *argv[])
{
  srand(time(NULL));
  
  //initialize array
  int i;
  for(i = 0; i < size; i++)
  {
    buffer[i] = -1;
  }
  
  //open file
  producerFile = fopen("production.txt", "w");
  consumerFile = fopen("consumption.txt", "w");
  
  x = atoi(argv[1]);
  
  //producer/consumer thread ID
  pthread_attr_t tattr;
  pthread_t producerID, consumerID;
  
  pthread_attr_init(&tattr);
  pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);
  
  //initialize semaphores empty, full, and mutex
  sem_init(&empty, 0, size);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);
  
  //create producer and consumer threads
  pthread_create(&producerID, &tattr, producer, NULL);
  pthread_create(&consumerID, &tattr, consumer, NULL);

  //wait
  pthread_join(producerID, NULL);
  pthread_join(consumerID, NULL);

  //close file
  fclose(consumerFile);
  fclose(producerFile);
}



void *producer()
{
  int item;
  int i;
  for(i = 0; i < x; i++)
  {
    sem_wait(&empty);  //wait for empty slot
    sem_wait(&mutex);
    
    item = rand() % 100;
    item++;
    
    if(in == size)
    {
      in = 0;
    }
    
    buffer[in] = item;
    
    fprintf(producerFile, "Producer: %d\n", buffer[in]);
    printf("Produced: buffer[%d]: %d\n", in, buffer[in]);
    
    in++;
    
    sem_post(&mutex);
    sem_post(&full);  //update full/item had been produced
  }
}



void *consumer()
{
  int item;
  int i;
  for(i = 0; i < x; i++)
  {
    sem_wait(&full);  //wait for an item
    sem_wait(&mutex);
    
    if(out == size)
    {
      out = 0;
    }
    
    item = buffer[out];
    fprintf(consumerFile, "Consumed: %d   Squared: %d\n", item, item * item);
    printf("Consumed: buffer[%d]: %d   Squared: %d\n", out, buffer[out], buffer[out] * buffer[out]);
    
    buffer[out] = -1;
    out++;
    
    sem_post(&mutex);  
    sem_post(&empty);  //update empty/item has been consumed
  }
}

