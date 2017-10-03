// CSCI 3300
// Assignment: 7
// Author:     Josh Weeks
// File:       equiv.h
// Tab stops:  2

#include <cstdio>

using namespace std;

//==============================================================
//                   Structures
//==============================================================

struct Equiv
{
    int arraySize;
    int* boss;
    
    Equiv(int arrayS)
    {
        arraySize = arrayS + 1;
        boss = new int[arraySize];
        
        for(int i = 0; i < arraySize; i++)
        {
            boss[i] = 0;
        }
    }
};

//==============================================================
//                   Prototypes
//==============================================================

bool together(Equiv& e, int x, int y);
void combine(Equiv& e, int x, int y);
int leader(const Equiv& e, int x);



