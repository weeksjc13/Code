// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       unhuffman.cpp
// Tab stops:  2

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include "binary.h"
#include "tree.h"
#include "trace.h"
#include "pqueue.h"

using namespace std;


//==============================================================
//                      unhuffman
//==============================================================
// Activate tracing by typing -t1 before your input/output files
//
// First file on command line will be an input file and the
// second will be an output file.
//
// Example: ./run 
//==============================================================


//==============================================================
//                      trace
//==============================================================

int trace = 0;

//==============================================================
//                      findFile
//==============================================================
// parameters: argv is the array of strings holding the command
// line input
//
// findInput asks if the second part of the command line
// contain character "-" if it does then it returns 2
// if it does not it returns 1
//
// Note: If character "-" is at argv[1] then it must be tracing
// and the next string must be the file to be read
//==============================================================

int findFile(char** argv)
{
    if(strpbrk(argv[1], "-"))
    {
        return 2;
    }
    
    return 1;
}

//==============================================================
//                      uncompress
//==============================================================
//
//==============================================================

void uncompress(BFILE* binaryFile, FILE* output, Node* tree)
{
    Node* original = tree;
    Node*& subtree = tree;
    
    int bit = readBit(binaryFile);
    
    while(bit != EOF)
    {
        if(bit == 0)
        {
            subtree = tree -> left;
            printf("\nHello, bit == 0\n");
            printTree(tree);
            printf("\n\n");
        }
        else if(bit == 1)
        {
            subtree = tree -> right;
            printf("\nHello, bit == 1\n");
            printTree(tree);
            printf("\n\n");
        }
        
        if(subtree -> kind == leaf)
        {
            char character = subtree -> ch;
            printf("\nSUBTREE -> KIND == leaf :D\n");
            fprintf(output, "%c", character);
            printf("\nAfter fprintf...\n");
            subtree = original;
            printTree(tree);
        }
        
        bit = readBit(binaryFile);
    }
}

//==============================================================
//                      readTree
//==============================================================

Node* readTree(BFILE* binaryFile, FILE* output, Node* t)
{
    int bit = readBit(binaryFile);
    
    if(bit == 1)
    {
        int byte = readByte(binaryFile);
        char character = (char)byte;
        
        Node* leaf = new Node(character);
        return leaf;
    }
    else if(bit == 0)
    {
        t = new Node(readTree(binaryFile, output, t),readTree(binaryFile, output, t));
        return t;
    }
    else
    {
        return t;
    }
}

//==============================================================
//                       main
//==============================================================

int main(int argc, char** argv)
{
    setTracing(argc, argv);
    
    int filePos = findFile(argv);
    
    FILE* output = fopen(argv[filePos + 1], "r");
    
    BFILE* binaryFile = openBinaryFileRead(argv[filePos]);
    
    Node* t = NULL;
    
    Node* tree = readTree(binaryFile, output, t);
    
    if(trace >= 2)
    {
        printf("\n\nThe tree created from the binary file is: \n");
        printTree(tree);
        printf("\n\n");
    }
    
    uncompress(binaryFile, output, tree);
    
    fclose(output);
    
    closeBinaryFileRead(binaryFile);
    
    return 0;
}


