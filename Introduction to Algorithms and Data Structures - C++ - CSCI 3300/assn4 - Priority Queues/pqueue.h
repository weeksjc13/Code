// CSCI 3300
// Assignment: 4a
// Author:     Josh Weeks
// File:       pqueue.h
// Tab stops:  none
 
struct PriorityQueue;
struct PQCell;

typedef const char* PQItemType;
typedef double      PQPriorityType;
typedef void (ItemPrinter)(const PQItemType&);
typedef void (PriorityPrinter)(PQPriorityType);

struct PriorityQueue
{
  PQCell* ptr;
  
  PriorityQueue()
  {
    ptr = NULL;
  }
};

//==============================================================
//                      isEmpty
//==============================================================
// returns true if q is empty
//==============================================================

bool isEmpty(const PriorityQueue& q);

//==============================================================
//                      insert
//==============================================================
// Insert item x with priority p into q
//==============================================================

void insert(const PQItemType& x, PQPriorityType p, PriorityQueue& q);

//==============================================================
//                      remove
//==============================================================
// Removes the item from q that has the smallest priority. 
// Stores the removed /item into variable x and store its 
// priority into variable p.
//==============================================================

void remove(PQItemType& x, PQPriorityType& p, PriorityQueue& q);

//==============================================================
//                      printPriorityQueue
//==============================================================
// Prints the contents of q, in order from lowest priority to
// highest priority, to the standard output. Use pi(x) to show
// item x and pp(y) to show priority y. Write the priority 
// first, then a tab, then the item, then a newline character. 
//==============================================================

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp);


