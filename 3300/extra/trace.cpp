// CSCI 3300
// Assignment: 6a
// Author:     Ibook Eyoita
// File:       trace.cpp
// Tab stops:  Every 4 characters

#include "trace.h"
#include "tree.h"
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;
int traceLevel=0;
//========================================================
//                    tracing
//========================================================
// tracing(v,opt) sets the trace value v from opt.
//========================================================

void tracing(int& v,const char* opt)
{
	if(strcmp(opt, "-t1") == 0)
	{
		v=1;
	}
	if(strcmp(opt, "-t2") == 0)
	{
		v=2;
	}
}

//========================================================
//                    showCharacter
//========================================================
// showCharacter(c) shows the name of c.
//========================================================

void showCharacter(char c)
{
	if(c == '\n')
	{
		printf("newline");
	}
	else if(c == ' ')
	{
		printf("space");
	}
	else if(c=='\t')
	{
		printf("tab");
	}
	else
	{
		printf("%c",c);
	}
}

//========================================================
//                    showFrequencies
//========================================================
// printFrequencies(arr[]) prints the occurences of each
// char in arr[]
//========================================================

void showFrequencies(int arr[])
{
	for(int i=0; i<256; i++)  // Print the results
	{
		if(arr[i]>0)
		{
			showCharacter(i);
			printf(" occurs %i times\n",arr[i]);
		}
	}
}

//========================================================
//                    showCode
//========================================================
// showCode(arr[]) shows the code in the arrary,arr[].
//========================================================

void showCode(string arr[])
{
	for(int i=0; i<256; i++)
	{
		if(arr[i]!= "")
		{
			showCharacter(i);
			printf("'s code is %s\n",arr[i].c_str());
		}
	}
}

//========================================================
//                    printTree
//========================================================
// printTree(theTree) prints theTree
//========================================================

void printTree(Node* theTree)
{
	
	if(theTree -> kind==nonleaf)
	{
		printf("(");
		printTree(theTree->left);
		printf(",");
		printTree(theTree->right);
		printf(")");
	}
	else
	{
		showCharacter(theTree->ch);
	}
}

//========================================================
//                    displayInfo
//========================================================
// displays the frequency array,freq, the tree and the code
// array, code[]
//========================================================

void displayInfo(int freq[],Node* tree, string code[])
{
	printf("The Character Frequencies are:\n");
	showFrequencies(freq);
	printf("\nThe Huffman tree is as follows:\n");
	printTree(tree);
	printf("\n");
	printf("\nThe Huffman code is as follows:\n");
	showCode(code);
}
