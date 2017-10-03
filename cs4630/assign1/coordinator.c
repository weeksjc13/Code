// CSCI 4630
// Program:    1
// Class:      CSCI 4630
// Author:     Josh Weeks
// Date:       2/4/16
// File:       coordinator.c

//compiler information:
//gcc -o coordinator coordinator.c -lm
//NOTE: recieves two warning but still works

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
  int status, workerid, id;
  int i = 0;
  int size = argc;
  int loopcount = 0;
  
  //create array
  char* data[size];
  for(i = 1; i <= size; i++)
  {
    data[i] = argv[i];
  }
  
  int numberloops = ceil(log2(argc)); //number of times outer loop will run
  int index = 0;
  
  for(index = 0; numberloops > index; index++)
  {
    loopcount = 0;
    
    for(i = 1; i <= size; i = i + 2)
    {
      loopcount++;
      
      id = fork();
      if(id == 0)
      {
        printf("I am Child, PID: %d Parent PID: %d\n", getpid(), getppid());
        execlp("./worker", "worker", data[i], data[i+1], NULL);
      }
      else if(id > 0)
      {
        printf("I am Parent, PID: %d.\n", getppid());
        
        workerid = waitpid(-1, &status, 0); //wait for worker
        printf("Child finished. Process ID of worker: %d\n", workerid);
      
        status = WEXITSTATUS(status);
        
        //update data array
        char* statStr;
        statStr = (char*) malloc(16);
        snprintf(statStr, sizeof(statStr), "%d", status);
        data[loopcount] = statStr;
        
        printf("Result recieved by parent: %d\n\n", status);
      }
      else
      {
        printf("Error: Unable to fork.\n");
      }
    }
    
    //set array after size to zero
    while(loopcount < size)
    {
      loopcount++;
      data[loopcount] = 0;
    } 
    
    //change size (number of values in data array)
    if(size % 2 == 1)
    {
      size = (size+1)/2;
    }
    else
    {
      size = size/2;
    }
  }
  
  printf("\n\nThe final sum is %s.\n\n", data[1]);
}
