// CSCI 3300
// Assignment: 7
// Author:     Josh Weeks
// File:       main.cpp
// Tab stops:  2

#include "graph.h"
#include <cstdio>
#include <iostream>

using namespace std;

extern int trace;

//==============================================================
//                   main
//==============================================================

int main(int argc, char** argv)
{
    setTrace(argc, argv);
    
    Graph g;
    
    readGraph(g);
    
    printf("\n\nThe input graph has 5 vertices, and its edges are as follows.\n\n");
    printGraph(g);
    
    Graph k = kruskal(g);
    printf("\n\nA minimal spanning tree uses the following edges.\n\n");
    printGraph(k);
    
    int totalWeight = graphWeight(k);
    printf("\n\nThe weight of the spanning tree is %i.\n\n", totalWeight);
    
    return 0;
}