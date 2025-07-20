#include <wchar.h>
#include <math.h>

#include "../NumberList/list.h"
#include "../Tree/tree.h"
#include "../Utilities/utilities.h"
#include "lexer.h"

#ifndef SYNTAX_HEADER
#define SYNTAX_HEADER

typedef struct 
{
    NumList* cur_token;     // move in list of tokens
    NumList* old_token;       
    Tree* tree;
} Parser;

//-----------------------------------------------
void GetSyntaxTree(Parser* src, Lexer* tokenizer);

Node* GetTransUnit(Parser* src);

Node* GetExtDecl(Parser* src);

Node* GetFuncDef(Parser* src);

Node* GetDeclList(Parser* src);

Node* GetDeclInit(Parser* src);

Node* GetStateList(Parser* src);

bool IsStatement(Parser* src);

Node* GetCompoundState(Parser* src);

Node* GetState(Parser* src);

Node* GetExpr(Parser* src);

Node* GetLogic_OR_Expr(Parser* src) ;

Node* GetLogic_AND_Expr(Parser* src) ;

Node* GetEqualityExpr(Parser* src) ;

Node* GetRelationalExpr(Parser* src);

Node* GetAdditiveExpr(Parser* src);

Node* GetMulExpr(Parser* src);

Node* GetPrimaryExpr(Parser* src);

Node* GetCallParams(Parser* src);

Node* GetNumber(Parser* src);

Node* GetId(Parser* src);
//-----------------------------------------------

#endif
