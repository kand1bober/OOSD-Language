#include "../Tree/tree.h"
#include "../StringList/list.h"
#include "../StringList/list.h"

#ifndef SPU_CODE_GEN_HEADER
#define SPU_CODE_GEN_HEADER

static const wchar_t* tabulation = L"    ";

void GenSpuCode(Tree* tree, StrList* id_table);

void GenExtDecl();

void GenFunc(Node* node, 
             StrList* id_table, 
             BufferInfo* asm_code);

void CountVariables(Node* node, 
                    StrList* id_table, 
                    StrList* var_table, 
                    int* var_count);

void GenDeclList(Node* node,
                 StrList* id_table, 
                 BufferInfo* func_code);

void GenDeclInit(Node* node,
                 StrList* id_table, 
                 BufferInfo* decl_list_code,
                 int* var_count);

void GenStateList();

bool IsStatement();

void GenCompoundState();

void GenState();

void GenExpr();

void GenLogic_OR_Expr() ;

void GenLogic_AND_Expr() ;

void GenEqualityExpr() ;

void GenRelationalExpr();

void GenAdditiveExpr();

void GenMulExpr();

void GenPrimaryExpr();

void GenCallParams();

void GenId(Node* node,
           StrList* id_table, 
           BufferInfo* code);

void GenNumber(Node* node,
               StrList* id_table, 
               BufferInfo* code);

#endif
