// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       trace.cpp
// Tab stops:  none

#include <cstdio>
#include <cstring>
#include <string>
#include "trace.h"

extern int trace;

//==============================================================
//                      setTracing
//==============================================================
// parameters: argc is the amount of strings on the command line
// and argv is an array that holds the strings of the command
// line
//
// if -t1 is found is the command line it sets a variable trace
// to 1
// if -t2 is found is the command line it sets a variable trace
// to 2
//
// Note: trace is an external variable
//==============================================================

void setTracing(int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        const char* arg = argv[i];
        
        if(strcmp(arg, "-t1") == 0)
        {
            trace = 1;
        }
        else if(strcmp(arg, "-t2") == 0)
        {
            trace = 2;
        }
        else if(strcmp(arg, "-t3") == 0)
        {
            trace = 3;
        }
    }
}

//==============================================================
//                      printArray
//==============================================================
// parameters: array holds integers that represent frequencies
// at each characters location in the array
//
// printArray prints the character and frequency at each index
// of array if the frequency is greater than 0
//==============================================================

void printArray(int* array)
{
    printf("\nThe character frequencies are: \n\n");
    
    unsigned char character;
    
    for(int x = 0; x < 256; x++)
    {
        if(array[x] > 0)
        {
            character = x;
            printCharacter(character);
            printf(" %i\n", array[x]);
        }
    }
}

//==============================================================
//                      printTree
//==============================================================
// parameters: t is a tree with character leaves
//
// printTree prints the characters that are in the tree in the
// order they occur in the tree
//
// example: ((c,(b,d)),(a,e))
//==============================================================

void printTree(Node* t)
{
    if(t -> kind != nonleaf)
    {
        printCharacter(t -> ch);
    }
    else
    {
        printf("(");
        printTree(t -> left);
        printf(",");
        printTree(t -> right);
        printf(")");
    }
}

//==============================================================
//                      printCharacter
//==============================================================
// parameters: ch is a character
//
// printCharacter prints (space) if ch is a space, (newline) if
// ch is a newline, (tab) if ch is a tab, and otherwise prints
// the character as it is
//==============================================================

void printCharacter(char ch)
{
    if(ch == ' ')
    {
        printf("(space)");
    }
    else if(ch == '\n')
    {
        printf("(newline)");
    }
    else if(ch == '\t')
    {
        printf("(tab)");
    }
    else
    {
        printf("%c", ch);
    }
}

//==============================================================
//                      printBinary
//==============================================================
// parameters: huffmanCodes is an array of strings that hold
// binary that has been encoded for a character
//
// printBinary prints characters and their newly encoded binary
//==============================================================

void printBinary(string* huffmanCodes)
{
    printf("A huffman code is as follows.\n\n");
    
    unsigned char character;
    
    for(int x = 0; x < 256; x++)
    {
        if(huffmanCodes[x].length() > 0)
        {
            character = x;
            printCharacter(character);
            printf(" %s\n", huffmanCodes[x].c_str());
        }
    }
}

