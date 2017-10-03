// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       huffman.cpp
// Tab stops:  none

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
//                      trace
//==============================================================

int trace = 0;

//==============================================================
//                      countFile
//==============================================================
// parameters: integer array of size 255, char array argv that
// represents the strings of the command line, and an integer
// that is the location of a file in the command line
//
// countFile reads a file character by character and increments
// array at each characters place in the array
//==============================================================

void countFile(int* array, FILE* input)
{
    int charNum = 0;
    
    while(charNum != EOF)
    {
        charNum = getc(input);
        
        array[charNum]++;
    }
    
    
    if(trace >= 1)
    {
        printArray(array);
    }
}

//==============================================================
//                      createArray
//==============================================================
// parameters: integer array of size 255
//
// sets each index of the array to 0
//==============================================================

void createArray(int* array)
{
    for(int x = 0; x < 256; x++)
    {
        array[x] = 0;
    }
}

//==============================================================
//                      leafMaker
//==============================================================
// parameter: an integer array of size 255 that holds character
// frequencies
//
// leafMaker finds all character that have frequencies. Each of
// the characters will be made into a Node that holds a single
// character.
//==============================================================

void leafMaker(int* array, PriorityQueue& q)
{
    unsigned char character =0;
    
    for(int x = 0; x < 256; x++)
    {
        if(array[x] > 0)
        {
            character = x;
            Node* t = new Node(character);
            insert(t, array[x], q);
        }
    }
}

//==============================================================
//                      treeMaker
//==============================================================
// parameter: q holds node(s) with a character and a frequency
//
// treeMaker removes the two lowest priority leaves in the q
// and their frequencies and combines them into a single node.
// Both characters become a child of a parent node and are
// inserted back into the q. The new node holds the sum of the
// frequencies of the teo removed leaves.
//==============================================================

void treeMaker(PriorityQueue& q)
{
    int prio1, prio2;
    
    Node* Node1;
    Node* Node2;
    
    remove(Node1, prio1, q);
    
    if(!isEmpty(q))
    {
        remove(Node2, prio2, q);
        
        Node* t = new Node(Node1, Node2);
        
        insert(t, prio1 + prio2, q);
        
        treeMaker(q);
    }
    else
    {
        insert(Node1, prio1, q);
        printTree(Node1);
    }
}

//==============================================================
//                      makeBinaryHelper
//==============================================================
// parameters: huffmanCodes is a array of strings of size 255
// that are not yet defined, binary is a string not defined,
// tree is a tree that holds characters and their frequencies
//
// makeBinaryHelper makes a binary code for each characte in tree
// based on its postion in the tree
//==============================================================

void makeBinaryHelper(string* huffmanCodes, string binary, Node* tree)
{
    int charInt;
    
    if(tree -> kind == leaf)
    {
        charInt = tree -> ch;
        huffmanCodes[charInt] = binary;
    }
    else
    {
        makeBinaryHelper(huffmanCodes, binary + "0", tree -> left);
        makeBinaryHelper(huffmanCodes, binary + "1", tree -> right);
    }
    
}

//==============================================================
//                      makeBinary
//==============================================================
// parameters: q holds a tree, huffman codes is a string array
// of size 255 that does not hold any information yet
//
// makeBinary gets a tree from q and changes the characters
// encodes each into its own binary which is stored into
// huffmanCodes
//==============================================================

void makeBinary(PriorityQueue q, string* huffmanCodes)
{
    string binary;
    int x;
    Node* t;
    
    remove(t, x, q);
    
    makeBinaryHelper(huffmanCodes, binary, t);
    
    if(trace >= 1)
    {
        printBinary(huffmanCodes);
        printf("\n\n\n");
    }
}

//==============================================================
//                      findInput
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

int findInput(char** argv)
{
    if(strpbrk(argv[1], "-"))
    {
        return 2;
    }
    
    return 1;
}

//==============================================================
//                       writeTreeBinary
//==============================================================

void writeTreeBinary(Node* t, BFILE* output)
{
    if(t -> kind == leaf)
    {
        writeBit(output, 1);
        writeByte(output, t -> ch);
    }
    else
    {
        writeBit(output, 0);
        writeTreeBinary(t -> left, output);
        writeTreeBinary(t -> right, output);
    }
}

//==============================================================
//                       writeCharacterCode
//==============================================================

void writeCharacterCode(FILE* input2, BFILE* output, string* huffmanCodes, int character)
{
    int bit;
    
    while(character != EOF)
    {
        character = getc(input2);
        
        if(character == EOF)
        {
            break;
        }
        
        string code = huffmanCodes[character];
        
        int stringSize = code.length();
        char charArray[10];
        
        for(int i = 0; i < stringSize; i++)
        {
            charArray[i] = code[i];
            
            bit = charArray[i];
            
            if(bit == 48)
            {
                writeBit(output, 0);
            }
            else
            {
                writeBit(output, 1);
            }
        }
    }
}

//==============================================================
//                       writeFile
//==============================================================

void writeFile(string* huffmanCodes, Node* t, int fileLoc, char** argv)
{
    FILE* input2 = fopen(argv[fileLoc], "r");
    
    BFILE* output = openBinaryFileWrite(argv[fileLoc + 1]);
    
    
    if(output != NULL)
    {
        writeTreeBinary(t, output);
        
        int character = 0;
        
        writeCharacterCode(input2, output, huffmanCodes, character);
    }
    
    
    fclose(input2);
    
    closeBinaryFileRead(output);
    
}


//==============================================================
//                       main
//==============================================================

int main(int argc, char** argv)
{
    PriorityQueue q;
    
    setTracing(argc, argv);
    
    
    int* array = new int [256];
    
    createArray(array);
    
    
    int fileLoc = findInput(argv);
    
    FILE* input = fopen(argv[fileLoc], "r");
    
    countFile(array, input);
    
    fclose(input);
    
    
    leafMaker(array, q);
    
    
    if(trace >= 1)
    {
        printf("\n\nThe Huffman tree is as follows: ");
        treeMaker(q);
        printf("\n\n\n");
    }
    
    
    string* huffmanCodes = new string [256];
    
    makeBinary(q, huffmanCodes);
    
    Node* t = new Node('a');
    
    int prio;
    
    remove(t, prio, q);
    
    
    writeFile(huffmanCodes, t, fileLoc, argv);
    
    
    return 0;
}

