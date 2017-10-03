// CSCI 4630
// Program:    1
// Class:      CSCI 4630
// Author:     Josh Weeks
// Date:       2/4/16
// File:       worker.c

//compiler information:
//gcc -o worker worker.c

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
  int num1 = atoi(argv[1]);
  int num2;
  
  if(argc == 3)
  {
    num2 = atoi(argv[2]);
  }
  else
  {
    num2 = 0;
  }
  
  int sum = num1 + num2;
  
  printf("%d + %d = %d Worker process PID: %d\n", num1, num2, sum, getpid());
  
  exit(sum);
}
