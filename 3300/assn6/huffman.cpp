// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       huffman.cpp
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
//                      Huffman
//==============================================================
// Huffman reads a input file and creates a tree based on the 
// frequency of the characters that occur in the input file.
// Huffman writes this tree in huffman codes to a output file 
// then writes the input file in huffman codes to the output 
// file.
//
// Huffman reads an input file from the command line and write 
// to another file on the command line.
//
// Ex: ./run -t3 data.txt data.cmp
//==============================================================


//==============================================================
//                      trace
//==============================================================

int trace = 0;

//==============================================================
//                      countFile
//==============================================================
// countFile(array, input) makes an array and reads input.  The
// array will hold the number of times each character occurs in
// input at the characters position in the array.
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
// createArray(array) fills each index of array of size 255 with
// 0's
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
// leafMaker(array, q) finds each position of the array that
// does not hold 0 and creates a leaf for that character and
// stores each individual leaf into q.
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
// treeMaker(q) creates a tree from leaves that are currently
// in q and inserts the tree into q.
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
// makeBinaryHelper(huffmanCodes, binary, tree) writes binary 
// code for a character in tree and puts it in the string 
// binary. Each character's code will be stored at it's
// own index.
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
// makeBinary(q, huffmanCodes) creates a binary for each of the
// characters that exist in the tree that exists in q.
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
// findInput(argv) returns an integer. It returns 2 if the 
// command line contains a "-" and 1 otherwise.
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
// writeBinaryTree(t, output) write the binary version of t
// into output.
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
// writeCharacterCode(input2, output, huffmanCodes, character)
// writes the huffman code of each character in input2 into
// output. The huffman codes are retrieved from huffmanCodes.
// Character is an integer that is equal to 0 when it is passed. 
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
// writeFile(huffmanCodes, t, fileLoc, argv) opens input2 and
// output. t is the tree that will be written in binary into
// output. After the tree is written, input2 will be written
// in huffman codes that obtained from huffmanCodes into output.
// argv is the array holding command line arguments and fileLoc
// is the index of the input file on the command line.
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
    
    closeBinaryFileWrite(output);
    
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


