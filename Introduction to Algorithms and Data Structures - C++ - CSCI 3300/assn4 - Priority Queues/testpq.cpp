// CSCI 3300
// Assignment: 4a
// Author:     Josh Weeks
// File:       testpq.cpp
// Tab stops:  none

#include <cstdio>
#include "pqueue.h"

using namespace std;

void printPriority(PQPriorityType x)
{
  printf("%lf", x);
}

void printItem(const PQItemType& p)
{
  printf(p);
}

//==============================================================
//                   main
//==============================================================

int main(int argc, char** argv)
{
  
  PriorityQueue q;
  //list is now NULL
  
  PQItemType x;
  PQPriorityType p;
  
  if(isEmpty(q))
  {
    printf("\n\ntest before insert: list is empty\n\n");
  }
  
  printf("\n\ntest: original inserts in q\n\n");
  
  insert("test 1", 5.0, q);
  insert("test 2", 6.0, q);
  insert("test 3", 4.0, q);

  printPriorityQueue(q, printItem, printPriority);
  
  //after one remove
  printf("\n\nremove first cell from q\n\n");
  remove(x, p, q);
  printPriorityQueue(q, printItem, printPriority);
  
  //after two removes
  printf("\n\nremove second cell from q\n\n");
  remove(x, p, q);
  printPriorityQueue(q, printItem, printPriority);
  
  //after three removes
  printf("\n\nremove third cell from q, leaving it empty\n\n");
  remove(x, p, q);
  printPriorityQueue(q, printItem, printPriority);
  
  return 0;
}

