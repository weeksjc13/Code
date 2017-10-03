// CSCI 3300
// Assignment: 6b
// Author:     Josh Weeks
// File:       tree.h
// Tab stops:  2

#ifndef TREE_H
#define TREE_H

enum NodeKind {leaf, nonleaf};

struct Node
{
    NodeKind kind;
    char     ch;
    Node*    left;
    Node*    right;
    
    Node(char c)
    {
        kind = leaf;
        ch   = c;
    }
    Node(Node* L, Node* R)
    {
        kind  = nonleaf;
        left  = L;
        right = R;
    }      
};

#endif
