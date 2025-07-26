#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "../Common/keywords.h"
#include "../Utilities/utilities.h"
#include "configuration.h"

#ifndef TREE_HEADER
#define TREE_HEADER

const uint64_t POISON = 0xBADBABA;

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

    kConstant = 1,
    kIdentifier = 2,
    kKeyWord = 3,
    kFuncDef = 4,
    kParameters = 5,
    kVarDecl = 6,
    kCall = 7,
} NodeTypes;

typedef union 
{
    wchar_t* str;
    int64_t num;
} TreeData;

typedef struct node_t 
{   
    NodeTypes type;
    TreeData data;   

    node_t* left;
    node_t* right;
    node_t* parent;
} Node;

typedef struct
{
    int64_t data;   
    NodeTypes type;          

    TreeInfo info;
    Node* root;
} Tree;

//-----------------------------------------------
Tree* TreeCtor();

TreeInfo TreeDtor(Tree* tree);

Node* CreateNode(Node* left, Node* right, Node* parent, NodeTypes type, TreeData data);

TreeInfo InsertLeave (Tree* tree, Node* parent, Direction branch, Node* to_connect);

TreeInfo InsertNode(Node* left, Node* right, Node* node);

void FreeTree (Tree* tree, Node* node);

TreeInfo BranchDelete (Tree* tree, Node* node, NodeTypes node_type);

Node* FindNode(Node* node_search, NodeTypes type, TreeData to_find);

Node* CopyNode (Tree* tree, Node* node_to_copy);

Node* CopyBranch (Tree* tree, Node* to_copy, Node* parent);
//-----------------------------------------------

#endif
