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
//                      Unhuffman
//==============================================================
// Unhuffman decodes a binary file that conains a tree and the
// characters that were in the original file. The original file
// will be written to a new file.
//
// Activate tracing by typing -t1 before your input/output files
//
// First file on command line will be an input file and the
// second will be an output file.
//
// Example: ./run input.cmp output.txt
//==============================================================


//==============================================================
//                      trace
//==============================================================

int trace = 0;

//==============================================================
//                      findFile
//==============================================================
// findFile(argv) returns an integer. It returns 2 if the 
// command line contains a "-" and 1 otherwise.
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
// uncompress(binaryFile, output, tree) uses tree to decode
// binaryFile. The decoded file is written into output.
//==============================================================

void uncompress(BFILE* binaryFile, FILE* output, Node* tree)
{
    Node* original = tree;
    Node*& subtree = tree;
    
    int bit = readBit(binaryFile);
    
    char character;
    
    while(bit != EOF)
    {
        if(bit == 0)
        {
            subtree = tree -> left;
        }
        else if(bit == 1)
        {
            subtree = tree -> right;
        }
        
        if(subtree -> kind == leaf)
        {
            character = subtree -> ch;
            fputc(character, output);
            subtree = original;
        }
        
        bit = readBit(binaryFile);
    }
}

//==============================================================
//                      readTree
//==============================================================
// readTree(binaryFile, t) returns a decoded tree that was
// encoded in binaryFile. t is a tree that is initialized as
// NULL that will hold the decoded tree that is returned.
//==============================================================

Node* readTree(BFILE* binaryFile, Node* t)
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
        t = new Node(readTree(binaryFile, t),readTree(binaryFile, t));
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
    
    FILE* output = fopen(argv[filePos + 1], "w");
    
    BFILE* binaryFile = openBinaryFileRead(argv[filePos]);
    
    Node* t = NULL;
    
    Node* tree = readTree(binaryFile, t);
    
    if(trace >= 2)
    {
        printf("\n\nThe tree created from the binary file is: \n");
        printTree(tree);
        printf("\n\n");
    }
    
    uncompress(binaryFile, output, tree);
    
    printf("\n\n");
    
    fclose(output);
    
    closeBinaryFileRead(binaryFile);
    
    return 0;
}


