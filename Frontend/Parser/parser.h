#include <wchar.h>
#include <math.h>

#include "../../NumberList/list.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"
#include "../Tokenizer/tokenizer.h"

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
} Parser;

//-----------------------------------------------
// void GetG (Parser* src);
// Node* GetE (Parser* src);
// Node* GetT (Parser* src);
// Node* GetD (Parser* src);
// Node* GetSL(Parser* src);
Node* GetP (Parser* src);
Node* GetN (Parser* src);
Node* GetId (Parser* src);

void SyntaxAnalysis(Parser* parser, Tokenizer* tokenizer);
void CloseParser(Parser* parser);
//-----------------------------------------------

#endif
