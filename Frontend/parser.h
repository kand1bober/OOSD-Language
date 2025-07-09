#include <wchar.h>
#include <math.h>

#include "../NumberList/list.h"
#include "../Tree/tree.h"
#include "../Utilities/utilities.h"
#include "lexer.h"

#ifndef SYNTAX_HEADER
#define SYNTAX_HEADER

#define SYNTAX_ERROR    wprintf(RED L"Syntax error:"  \
                                "file: %s\n"        \
                                "func: %s\n"        \
                                "line: %d\n" DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                        exit(1); \

#define SYNTAX_ASSERT(expr)     if (TOKEN_VAL != expr) \
                                    SYNTAX_ERROR

typedef struct 
{
    NumList* cur_token;     // move in list of tokens
    NumList* old_token;       
    Tree* tree;
} Parser;

//-----------------------------------------------
void StartParser(Parser* parser, Lexer* tokenizer);

Node* GetTransUnit(Parser* src, Lexer* tokenizer);

Node* GetExtDecl(Parser* src);

Node* GetFuncDef(Parser* src);

Node* GetDeclList(Parser* src);

Node* GetDeclInit(Parser* src);

Node* GetStateList(Parser* src);

Node* GetCompoundState(Parser* src);

Node* GetState(Parser* src);

Node* GetSelectStateState(Parser* src);

Node* GetExpr(Parser* src);

Node* GetLogic_OR_Expr(Parser* src) ;

Node* GetLogic_AND_Expr(Parser* src) ;

Node* GetEqualityExpr(Parser* src) ;

Node* GetRelationalExpr(Parser* src);

Node* GetAdditiveExpr(Parser* src);

Node* GetMulExpr(Parser* src);

Node* GetPrimaryExpr(Parser* src);

Node* GetNumber(Parser* src);

Node* GetId(Parser* src);
//-----------------------------------------------

#endif
