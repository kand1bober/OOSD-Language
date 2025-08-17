#include "../Tree/tree.h"
#include "../StringList/list.h"

#ifndef SPU_CODE_GEN_HEADER
#define SPU_CODE_GEN_HEADER

void GenSpuCode(Tree* tree, StrList* id_table);

void GenExtDecl();

void GenFunc(Node* node, 
             StrList* id_table, 
             BufferInfo* asm_code);

void GenDeclList();

void GenDeclInit();

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

void GenNumber();

void GenId();

#endif
