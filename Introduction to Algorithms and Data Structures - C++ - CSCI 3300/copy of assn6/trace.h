// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       trace.h
// Tab stops:  none

#include <cstdio>
#include <cstring>
#include <string>
#include "tree.h"

using namespace std;

void setTracing(int argc, char** argv);

void printBinary(string* huffmanCodes);

void printArray(int* array);

void printTree(Node* t);

void printCharacter(char ch);
