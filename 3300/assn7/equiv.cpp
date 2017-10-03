// CSCI 3300
// Assignment: 7
// Author:     Josh Weeks
// File:       equiv.cpp
// Tab stops:  2

#include <cstdio>
#include "equiv.h"
#include "graph.h"

using namespace std;

extern int trace;

//==============================================================
//                   together
//==============================================================
// together(e, x, y) returns true if x and y are in the same
// set in e.
//==============================================================

bool together(Equiv& e, int x, int y)
{
    if(trace > 0)
    {
        printf("\n**PARAMETERS of together**\n");
        printf("\nBoss array:\n");
        for(int i = 0; i < e.arraySize; i++)
        {
            printf("%i\n", e.boss[i]);
        }
        printf("x = %i and y = %i\n", x, y);
    }
    
    bool same = false;
    
    for(int i = 0; i < e.arraySize; i++)
    {
        if(e.boss[i] == x && e.boss[i] == y)
        {
            return true;
        }
    }
    
    if(trace > 0)
    {
        printf("\nRESULT of together (1=true and 0=false):\n");
        printf("%d\n", same);
    }
    
    return same;
}

//==============================================================
//                   combine
//==============================================================
// combine(e, x, y) modifies e so that the sets that contain
// x and y are combined into a single set.
//==============================================================

void combine(Equiv& e, int x, int y)
{
    if(trace > 0)
    {
        printf("\n**PARAMETERS of combine**\n");
        printf("\nBoss array before combine:\n");
        
        for(int i = 0; i < e.arraySize; i++)
        {
            printf("%i\n", e.boss[i]);
        }
        
        printf("\nx = %i and y = %i\n\n", x, y);
    }
    
    e.boss[y] = leader(e,x);
    
    if(trace > 0)
    {
        printf("\nBoss array after combine:\n");
        
        for(int i = 0; i < e.arraySize; i++)
        {
            printf("%i\n", e.boss[i]);
        }
        
        printf("\n");
    }
}

//==============================================================
//                   leader
//==============================================================
// leader(e, x) returns the leader of the set that contains
// x in collection of sets e
//==============================================================

int leader(const Equiv& e, int x)
{
    while(e.boss[x] != 0)
    {
        x = e.boss[x];
    }
    return x;
}

