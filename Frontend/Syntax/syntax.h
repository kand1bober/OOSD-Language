#include <wchar.h>
#include <math.h>

#include "../../NumberList/list.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"

#ifndef SYNTAX_HEADER
#define SYNTAX_HEADER

#define SYNTAX_ERROR    printf(RED "Syntax error:"  \
                                "file: %s\n"        \
                                "func: %s\n"        \
                                "line: %d\n" DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                        exit(1); \

typedef struct 
{
    NumList* cur_node;
    NumList* old_node;
    Tree* tree;
} RecursiveDescent;

//-----------------------------------------------
// void GetG (RecursiveDescent* src);
// Node* GetE (RecursiveDescent* src);
// Node* GetT (RecursiveDescent* src);
// Node* GetD (RecursiveDescent* src);
// Node* GetSL(RecursiveDescent* src);
Node* GetP (RecursiveDescent* src);
Node* GetN (RecursiveDescent* src);
Node* GetId (RecursiveDescent* src);
//-----------------------------------------------

#endif
