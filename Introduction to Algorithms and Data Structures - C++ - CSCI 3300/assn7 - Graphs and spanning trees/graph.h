// CSCI 3300
// Assignment: 7
// Author:     Josh Weeks
// File:       graph.h
// Tab stops:  2

#include <cstdio>

using namespace std;

//==============================================================
//                   Structures
//==============================================================

struct Edge
{
    int vertex1;
    int vertex2;
    int weight;
    
    Edge(int vert1, int vert2, int w)
    {
        vertex1 = vert1;
        vertex2 = vert2;
        weight = w;
    }
    
    Edge()
    {
        vertex1 = 0;
        vertex2 = 0;
        weight = 0;
    }
};

struct Graph
{
    int numVertices;
    int numEdges;
    Edge* edgeArray;
    
    Graph(int numV, int numE)
    {
        numVertices = numV;
        numEdges = numE;
        edgeArray = new Edge[numE + 1];
    }
    
    Graph()
    {
        numVertices = 0;
        numEdges = 0;
        edgeArray = NULL;
    }
};

//==============================================================
//                   Prototypes
//==============================================================

typedef int (*QSORT_COMPARE_TYPE)(const void*, const void*);
void setTrace (int argc, char** argv);
int compareEdges(const Edge* A, const Edge* B);
int graphWeight(Graph &g);
void createEdge(Graph& g, int weight, int start, int end);
void printGraph(Graph g);
void readGraph(Graph &g);
Graph kruskal(Graph &g);



