#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "../Frontend/keywords.h"
#include "../Utilities/utilities.h"
#include "configuration.h"

#ifndef TREE_HEADER
#define TREE_HEADER

const uint64_t POISON = 0xBADBABA;

typedef uint64_t Data;

typedef enum 
{
    kGoodTree = 1,
    kBadTree,
} TreeInfo;

typedef enum 
{
    kLeft = 1,
    kRight = 2,
    kNoBranch = 3,
} Direction;

typedef enum
{
    kNoType = 0, // default/initial

    kConst = 1,
    kIdentifier = 2,
    kKeyWord = 3,
    kFuncDef = 4,
    kParam = 5,
    kVarDecl = 6,
    kCall = 7,
} NodeTypes;

typedef struct node_t 
{   
    Data data;
    NodeTypes type;
    node_t* left;
    node_t* right;
    node_t* parent;
} Node;

typedef struct
{
    Data data;           
    NodeTypes type;          

    TreeInfo info;
    Node* root;
} Tree;

//-----------------------------------------------
Tree* TreeCtor();
TreeInfo TreeDtor(Tree* tree);

Node* CreateNode(Tree* tree, Node* left, Node* right, Node* parent, Data data, NodeTypes type);
TreeInfo InsertLeave (Tree* tree, Node* parent, Direction branch, Node* to_connect);
TreeInfo InsertNode(Node* left, Node* right, Node* node);
void FreeTree (Tree* tree, Node* node);
TreeInfo BranchDelete (Tree* tree, Node* node, NodeTypes node_type);
TreeInfo FindNode(Node* node_search, Data to_find, Node** answer);
Node* CopyNode (Tree* tree, Node* node_to_copy);
Node* CopyBranch (Tree* tree, Node* to_copy, Node* parent);
//-----------------------------------------------

#endif
