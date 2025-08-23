#include "../Tree/tree.h"
#include "../StringList/list.h"
#include "../StringList/list_dump.h"

#ifndef SPU_CODE_GEN_HEADER
#define SPU_CODE_GEN_HEADER

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
                 StrList* var_table,
                 BufferInfo* func_code);

void GenDeclInit(Node* node,
                 StrList* id_table, 
                 StrList * var_table,
                 BufferInfo* dec_list_code);

void GenRightValue(Node* node, // kEqual node
                   StrList* id_table, 
                   StrList * var_table,
                   BufferInfo* decl_code);

void GenStateList(Node* node,
                 StrList* id_table, 
                 StrList* var_table,
                 BufferInfo* func_code);

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
