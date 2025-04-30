#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "../Frontend/Lexis/lexis.h"

#ifndef TREE__HEADER
#define TREE__HEADER

const uint64_t POISON = 0xBADBABA;

// Node types = key word types

typedef union
{
    double num;
    char* str;
    
} Data_t;

typedef struct node_t 
{   
    Data_t data;
    KeyWords_t node_type;

    node_t* left;
    node_t* right;
    node_t* parent;
} Node_t;

typedef enum 
{
    kGoodTree = 1,
    kBadTree,
} TreeInfo;

enum Direction
{
    kLeft = 1,
    kRight = 2,
    kNoBranch = 3,
};

typedef struct
{
    KeyWords_t type;
    TreeInfo info;
    Node_t* root;
    Data_t data;
} Tree_t;


//-------------------------------OPERATIONS WITH TREE------------------------------------
TreeInfo TreeCtor (Tree_t* tree);
TreeInfo TreeDtor (Tree_t* tree);
void FreeTree (Tree_t* tree, Node_t* node); //-------- recursive

//--------------------------------OPERATIONS WITH NODES----------------------------------
Node_t* CreateNode (Tree_t* tree, Node_t* left, Node_t* right, Node_t* parent, Data_t data, KeyWords_t type);
Node_t* CopyNode (Tree_t* tree, Node_t* node_to_copy);

TreeInfo BranchDelete (Tree_t* tree, Node_t* node, KeyWords_t node_type);
TreeInfo InsertNode( Node_t* left, Node_t* right, Node_t* node);
TreeInfo InsertLeave (Tree_t* tree, Node_t* parent, Direction branch, Node_t* to_connect);
Node_t* CopyBranch( Tree_t* tree, Node_t* to_copy, Node_t* parent);

#endif


