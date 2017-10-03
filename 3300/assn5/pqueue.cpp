// CSCI 3300
// Assignment: 4a
// Author:     Josh Weeks
// File:       pqueue.cpp
// Tab stops:  none

#include <cstdio>
#include "pqueue.h"

using namespace std;

struct PQCell
{
  PQPriorityType priority;
  PQCell* next;
  PQItemType item;
  
  PQCell(PQItemType it, PQPriorityType prio, PQCell* nxt)
  {
    item = it;
    next = nxt;
    priority = prio;
  }
};

//==============================================================
//                      isEmpty
//==============================================================
// returns true if q is empty
//==============================================================
bool isEmpty(const PriorityQueue& q)
{
  if(q.ptr == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//==============================================================
//                      insertCell
//==============================================================
// inserts item x with priority p into the linked list pointed 
// to by p
//==============================================================

void insertCell(const PQItemType& x, PQPriorityType p, PQCell*& q)
{
  if(q == NULL || q -> priority > p)
  {
    q = new PQCell(x, p, q);
  }
  else
  {
    insertCell(x, p, q -> next);
  }
}

//==============================================================
//                      insert
//==============================================================
// Insert item x with priority p into q
//==============================================================

void insert(const PQItemType& x, PQPriorityType p, PriorityQueue& q)
{
  insertCell(x, p, q.ptr);
}

//==============================================================
//                      removeCell
//==============================================================
// Removes the item from q that has the smallest priority. 
// Stores the removed item into variable x and store its 
// priority into variable p.
//==============================================================

void removeCell(PQItemType& x, PQPriorityType& p, PQCell*& q)
{
  if(q != NULL)
  {
    x = q -> item;
    p = q -> priority;
    PQCell* r = q;
    q = r -> next;
    delete r;
  }
}

//==============================================================
//                      remove
//==============================================================
// Removes the item from q that has the smallest priority. 
// Stores the removed item into variable x and store its 
// priority into variable p.
//==============================================================

void remove(PQItemType& x, PQPriorityType& p, PriorityQueue& q)
{
  removeCell(x, p, q.ptr);
}

//==============================================================
//                      printPriorityQueueHelper
//==============================================================
// Prints the contents of q, in order from lowest priority to
// highest priority, to the standard output. Use pi(x) to show
// item x and pp(y) to show priority y. Write the priority 
// first, then a tab, then the item, then a newline character.
//==============================================================

void printPriorityQueueHelper(ItemPrinter pi, PriorityPrinter pp, PQCell*& cell)
{
  if(cell != NULL)
  {
    pp(cell -> priority);
    printf("\t");
    pi(cell -> item);
    printf("\n");
    printPriorityQueueHelper(pi, pp, cell -> next);
  }
}

//==============================================================
//                      printPriorityQueue
//==============================================================
// Prints what q holds.
//
// Example of format:
// 4.000000	test 3
// 5.000000	test 1
// 6.000000	test 2
//==============================================================

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
  PQCell* cell = q.ptr;
  printPriorityQueueHelper(pi, pp, cell);
}

