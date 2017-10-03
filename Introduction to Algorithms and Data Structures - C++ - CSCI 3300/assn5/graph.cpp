// CSCI 3300
// Assignment: 5i
// Author:     Josh Weeks
// File:       graph.cpp
// Tab stops:  none

#include <cstdio>
#include <string.h>
#include "pqueue.h"
#include "event.h"

using namespace std;

int trace = 0;

//==============================================================
//                   Structures
//==============================================================

struct AdjList
{
  double weight;
  int vertex;
  AdjList* nextAdj;
  
  AdjList(int w, int vert, AdjList* nextA)
  {
    weight = w;
    vertex = vert;
    nextAdj = nextA;
  }
};

struct Vertex
{
  double distance;
  int signal;
  AdjList* adjPointer;

  Vertex(double d, int s, AdjList* adjP)
  {
    distance = d;
    signal = s;
    adjPointer = adjP;
  }
  
  Vertex()
  {
    adjPointer = NULL;
    distance = 0.0;
    signal = -1;
  }
};

struct Graph
{
  int numVertices;
  int startVertex;
  int endVertex;
  Vertex* vertArray;
  
  Graph(int numV)
  {
    numVertices = numV;
    startVertex = 0;
    endVertex = 0;
    vertArray = new Vertex[numV + 1];
  }
};

//==============================================================
//                   Prototypes
//==============================================================

void printGraphHelp(int index, AdjList* adjPointer);
void signalerHelp(PriorityQueue& p, Graph& g);
void makeEvents(PriorityQueue& p, AdjList* list, double priority, int start);

//==============================================================
//                   readGraph
//==============================================================
// *parameters*
//
// g is a graph that will be filled by some input
//
//
// readGraph stores some input into g. This input includes a
// start vertex, end vertex, and the weight of the edge.
//==============================================================

void readGraph(Graph &g)
{
  int vert1, vert2, amount;
  double weight;
  bool flag = false;
  
  scanf("%i", &amount);
  g = Graph(amount);
  
  scanf("%i", &vert1);
  
  while(flag == false)
  {
    scanf("%i", &vert2);
    scanf("%lf", &weight);
    
    g.vertArray[vert1].adjPointer = new AdjList(weight, vert2, g.vertArray[vert1].adjPointer);
    
    g.vertArray[vert2].adjPointer = new AdjList(weight, vert1, g.vertArray[vert2].adjPointer);
    
    scanf("%i", &vert1);
    
    if(vert1 == 0)
    {
      scanf("%i", &g.startVertex);
      scanf("%i", &g.endVertex);
      
      flag = true;
    }
  }
}

//==============================================================
//                   printGraph
//==============================================================
// *parameters*
//
// g holds information about a graph: vertices and weights
//
//
// printGraph shows the path and weight of each edge that occurs
// in g.
//==============================================================

void printGraph(Graph &g)
{
  printf("There are %i vertices in the graph\n", g.numVertices);
  printf("The edges are as follows: \n\n");
  
  for(int i = 0; g.numVertices > i; i++)
  {
    printGraphHelp(i, g.vertArray[i].adjPointer);
  }
}

//==============================================================
//                   printGraphHelp
//==============================================================
// *parameters*
//
// adjPointer contains all the nodes that are adjacent to
// a specific node
//
// index is the location of the node
//
// printGraphHelp the path from a single node to all adjacent nodes.
//==============================================================

void printGraphHelp(int index, AdjList* adjPointer)
{
  for(AdjList* x = adjPointer; x != NULL; x = x -> nextAdj)
  {
    if(index < adjPointer -> vertex)
    {
      printf("(%i,%i) weight %lf \n", index, x -> vertex, x -> weight);
    }
  }
}

//==============================================================
//                   signaler
//==============================================================
// *parameters* 
//
// p is an empty priority queue
//
// g is a graph with edges that have different priorities
//
//
// signaler sends signals through the tree and finds the 
// shortest path.
//==============================================================

void signaler(PriorityQueue& p, Graph& g)
{
  int s = g.startVertex;
  
  Event* e = new Event(0, s, 0.0);
  insert(e, e -> time, p);
  
  while(!isEmpty(p))
  {
    signalerHelp(p, g);
  }
} 

//==============================================================
//                   signalerHelp
//==============================================================
// *parameters*
//
// p is an empty priority queue that will be filled with events
//
// g is a graph that is filled with nodes and edges that have
// priorities
//
//
// An event contains the start node and end node along with the
// the edges priority.
//==============================================================

void signalerHelp(PriorityQueue& p, Graph& g)
{
  Event* e;
  double priority;
  
  remove(e, priority, p);
  
  if(g.vertArray[e -> end].signal == -1)
  {
    g.vertArray[e -> end].distance = priority;
    g.vertArray[e -> end].signal = e -> start;
    
    if(trace > 0)
    {
      printf("\nSignal sent from %i to %i with a new weight of %lf.\n\n", e -> start, e -> end, priority);
    }
    
    makeEvents(p, g.vertArray[e -> end].adjPointer, priority, e -> end);
  }
}

//==============================================================
//                   makeEvents
//==============================================================
// *parameters*
//
// p is where the events will be inserted into
//
// list holds vertexs and their priorities
//
// priority is the priority that the current node holds
//
// start is the node that has sent the signals
//
// 
// makeEvents creates events that start at parameter start and 
// stores them into p. The priority that the node currently holds
// and will be added to the weight of the edge that has been
// signalled.
//==============================================================

void makeEvents(PriorityQueue& p, AdjList* list, double priority, int start)
{
  if(list != NULL)
  {
    Event* e = new Event(start, list -> vertex, list -> weight + priority);
    insert(e, e -> time, p);
    makeEvents(p, list -> nextAdj, priority, start);
  }
}

//==============================================================
//                   printEvents
//==============================================================
// *parameters*
//
// g is a graph that hold the previous nodes in the path that
// signalled to the end node in graph
//
// vertex holds the end vertex stored in graph
// 
// Prints the all nodes in the shortest path in g from the starting vertex to
// the ending vertex.
//==============================================================

void printPath(Graph g, int vertex)
{
  if(vertex == g.endVertex)
  {
    printPath(g, g.vertArray[vertex].signal);
    printf("%i", g.endVertex);
  }
  else if(vertex != 0)
  {
    printPath(g, g.vertArray[vertex].signal);
    printf("%i -> ", vertex);
  }
}

//==============================================================
//                      setTracing
//==============================================================
// parameters: argc is the amount of strings on the command line
// and argv is an array that holds the strings of the command
// line
//
// if -t is found is the command line it sets a variable trace
// to 1
//==============================================================

void setTracing(int argc, char** argv)
{
  for(int i = 0; i < argc; i++)
  {
    const char* arg = argv[i];
    
    if(strcmp(arg, "-t") == 0)
    {
      trace = 1;
    }
  }
}

//==============================================================
//                   main
//==============================================================

int main(int argc, char** argv)
{
  setTracing(argc, argv);
  
  Graph g = Graph(1);
  
  PriorityQueue p;
  
  readGraph(g);
  
  printf("\n");
  printGraph(g);
  printf("\n");
  
  signaler(p, g);
  
  printf("\nThe shortest path from %i to %i has length %lf and is\n", g.startVertex, g.endVertex, g.vertArray[g.endVertex].distance);
  
  printPath(g, g.endVertex);
  
  printf("\n\n");
  
  return 0;
}
