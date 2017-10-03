// CSCI 3300
// Assignment: 7
// Author:     Josh Weeks
// File:       graph.cpp
// Tab stops:  2

#include "graph.h"
#include "equiv.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

const int maxEdges = 100;
int trace = 0;

//==============================================================
//                   readGraph
//==============================================================
// readGraph(g) reads information about graph g and changes the
// graph to hold the information that it reads.
//
// input format:
//
// 5
// 1 2  9
// 1 3 12
// 2 4 18
// 2 3  6
// 2 5 20
// 3 5 15
// 0
//==============================================================

void readGraph(Graph &g)
{
    int vert1, vert2, amount, weight;
    int count = 0;
    bool flag = false;
    
    g.edgeArray = new Edge[maxEdges];
    
    scanf("%i", &amount);
    
    g.numVertices = amount;
    
    scanf("%i", &vert1);
    
    while(flag == false)
    {
        scanf("%i", &vert2);
        scanf("%i", &weight);
        
        g.edgeArray[count].vertex1 = vert1;
        g.edgeArray[count].vertex2 = vert2;
        g.edgeArray[count].weight = weight;
        
        count++;
        
        scanf("%i", &vert1);
        
        if(vert1 == 0)
        {
            flag = true;
        }
    }
    
    g.numEdges = count;
}

//==============================================================
//                   printGraph
//==============================================================
// printGraph(g) prints information about a graph.  It prints
// how many vertices and edges the graph has. Then, it prints
// the vertices and the weight that the edge between the
// vertices holds.
//==============================================================

void printGraph(Graph g)
{
    int numEdges = g.numEdges;
    
    printf("vertices weight\n");
    
    for(int i = 0; i < numEdges; i++)
    {
        printf("%i ", g.edgeArray[i].vertex1);
        printf("%i ", g.edgeArray[i].vertex2);
        printf("        %i \n", g.edgeArray[i].weight);
    }
}

//==============================================================
//                   createEdge
//==============================================================
// createEdge(g, weight, start, end) creates an edge that
// that contains information about a start vertex, end vertex,
// and the weight of the edge between the two.
//==============================================================

void createEdge(Graph& g, int weight, int start, int end)
{
    g.edgeArray[g.numEdges].weight = weight;
    g.edgeArray[g.numEdges].vertex1 = start;
    g.edgeArray[g.numEdges].vertex2 = end;
    g.numEdges++;
}

//==============================================================
//                   graphWeight
//==============================================================
// graphWeight(g) computes the total weight of the graph
// and returns the total weight as an integer value.
//==============================================================

int graphWeight(Graph &g)
{
    int sum = 0;
    int numEdges = g.numEdges;
    
    for(int i = 0; i < numEdges; i++)
    {
        sum = sum + g.edgeArray[i].weight;
    }
    
    return sum;
}

//==============================================================
//                   compareEdges
//==============================================================
// compareEdges(A, B) returns the weight of B subtracted from
// the weight of A.
//==============================================================

int compareEdges(const Edge* A, const Edge* B)
{
    return A->weight - B->weight;
}

//==============================================================
//                   setTrace
//==============================================================
// setTrace(argc, argv) check the command line for -te or -tm.
// If -tm, the trace is set to 2. If -te, the trace is set to
// 1. Argv is an array that holds the command line strings and
// argc is the amount of strings that occur on the command line.
//==============================================================

void setTrace(int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        const char* arg = argv[i];
        
        if(strcmp(arg, "-te") == 0)
        {
            trace = 1;
        }
        else if(strcmp(arg, "-tm") == 0)
        {
            trace = 2;
        }
    }
}

//==============================================================
//                   Kruskal
//==============================================================
// kruskal(g) takes g and return a graph that is the minimal
// spanning tree of of g.
//==============================================================

Graph kruskal(Graph &g)
{
    Graph g2;
    
    g2.edgeArray= new Edge[maxEdges];
    
    Equiv e(g.numVertices);
    
    
    
    if(trace > 1)
    {
        printf("\n\nKRUSKAL BEGINS:  g.numVertices: %i\n", g.numVertices);
        printf("\n\nBefore qsort:\n");
        printGraph(g);
    }
    
    qsort((void*) g.edgeArray, g.numEdges, sizeof(Edge), (QSORT_COMPARE_TYPE) compareEdges);
    
    if(trace > 1)
    {
        printf("\n\nAfter qsort:\n");
        printGraph(g);
    }
    
    for(int i = 0; i < g.numEdges; i++)
    {
        if(trace > 1)
        {
            printf("\n\nKRUSKAL CHECKED:\n");
            printf("%i  %i   weight: %i\n\n", g.edgeArray[i].vertex1, g.edgeArray[i].vertex2, g.edgeArray[i].weight);
        }
        
        if(!together(e, g.edgeArray[i].vertex1, g.edgeArray[i].vertex2))
        {
            if(trace > 1)
            {
                printf("\n\nKRUSKAL ADDED:\n");
                printf("%i  %i   weight: %i\n\n", g.edgeArray[i].vertex1, g.edgeArray[i].vertex2, g.edgeArray[i].weight);
            }
            
            createEdge(g2, g.edgeArray[i].weight, g.edgeArray[i].vertex1, g.edgeArray[i].vertex2);
            combine(e, g.edgeArray[i].vertex1, g.edgeArray[i].vertex2);
        }
    }
    return g2;
}

