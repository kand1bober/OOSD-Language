#include <wchar.h>
#include <math.h>

#include "../../NumberList/list.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"
#include "../Tokenizer/tokenizer.h"

#ifndef SYNTAX_HEADER
#define SYNTAX_HEADER

#define SYNTAX_ERROR    wprintf(RED L"Syntax error:"  \
                                "file: %s\n"        \
                                "func: %s\n"        \
                                "line: %d\n" DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                        exit(1); \

typedef struct 
{
    NumList* cur_token;     // move in list of tokens
    NumList* old_token;       
    Tree* tree;
} Parser;

//-----------------------------------------------

// Node* GetE (Parser* src);
// Node* GetT (Parser* src);
// Node* GetP (Parser* src);
// Node* GetN (Parser* src);


Node* GetTransUnit(Parser* src);

Node* GetExtDecl(Parser* src);

Node* FuncDef(Parser* src);

Node* GetDecl(Parser* src);

Node* DeclList(Parser* src);

Node* InitDeclList(Parser* src);

Node* GetInitDecl(Parser* src);

Node* GetParamTypeList(Parser* src);

Node* GetParamList(Parser* src);

Node* GetParamDecl(Parser* src);

Node* GetInit(Parser* src);

Node* GetInitList(Parser* src);
// Get Statement
Node* GetState(Parser* src);

Node* GetLabeledState(Parser* src);

Node* GetExprState(Parser* src);

Node* GetCompoundState(Parser* src);

Node* GetStateList(Parser* src);

Node* GetSelectionState(Parser* src);

Node* IterState(Parser* src);

Node* JumpState(Parser* src);

Node* GetExpr(Parser* src);

Node* GetAssignExpr(Parser* src);

Node* GetCondExpr(Parser* src);

Node* GetConstExpr(Parser* src);

Node* GetLogical_OR_Expr(Parser* src);

Node* GetLogical_AND_Expr(Parser* src);

Node* GetLogical_Equal_Expr(Parser* src);

Node* GetRelationalExpr(Parser* src);

Node* GetLAddExpr(Parser* src);

Node* GetMulExpr(Parser* src);

//-----------------------------------------------
void SyntaxAnalysis(Parser* parser, Tokenizer* tokenizer);

void CloseParser(Parser* parser);

Node* GetTransUnit(Parser* src, Tokenizer* tokenizer);

Node* GetExtDecl(Parser* src);

Node* GetFuncDef(Parser* src);

Node* GetDecl(Parser* src);

Node* GetDeclList(Parser* src);

Node* GetDeclInitList(Parser* src);

Node* GetDeclInit(Parser* src);

Node* GetExpr(Parser* src);

Node* GetAssignExpr(Parser* src);

Node* GetLogic_OR_Expr(Parser* src);

Node* GetLogic_AND_Expr(Parser* src);

Node* GetEqualityExpr(Parser* src) ;

Node* GetAdditiveExpr(Parser* src);

Node* GetMulExpr(Parser* src);

Node* GetPrimaryExpr(Parser* src);

Node* GetNumber(Parser* src);

Node* GetId (Parser* src);
//-----------------------------------------------

#endif
