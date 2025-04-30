#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "../Frontend/Lexer/lexer.h"

#ifndef TREE_HEADER
#define TREE_HEADER

const uint64_t POISON = 0xBADBABA;

typedef union
{
    double num;
    char* str;
    
} Data_t;

typedef enum
{
    kConstant = 1,
    kIdentifier,
    kKeyword,
    kFunctionDefinition,
    kParameters,
    kVarDeclaration,
    kCall,
} NodeTypes;

typedef struct node_t 
{   
    Data_t data;
    NodeTypes type;
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
    Data_t data;
    KeyWords type;
    TreeInfo info;
    Node_t* root;
} Tree_t;


#endif
