#include "../Tree/tree.h"
#include "../StringList/list.h"
#include "../StringList/list_dump.h"
#include "../Stack/stack.h"
#include "../Common/keywords.h"

#ifndef SPU_CODE_GEN_HEADER
#define SPU_CODE_GEN_HEADER

static const wchar_t* passed_vars_table[] = 
{
    L"trash :)",
    L"edi",
    L"esi", 
    L"edx",
    L"ecx",
    L"r8d",
    L"r9d",
};

typedef struct 
{
    int if_count;
    int while_count;
}LabelCounter;


void GenSpuCode(Tree* tree, StrList* id_table);

void GenExtDecl();

void GenFunc(Node* node, 
             StrList* id_table, 
             BufferInfo* asm_code,
             LabelCounter* label_counter);

void CountVariables(Node* start_node, //parameter_node
                    StrList* id_table, 
                    StrList* passed_vars,
                    int* passed_var_count,
                    StrList* local_vars, 
                    int* local_var_count);

void GenDeclList(Node* start_node,
                 StrList* id_table, 
                 BufferInfo* func_code,
                 StrList* passed_vars,
                 int* passed_var_count,
                 StrList* local_vars, 
                 int* local_var_count);

void GenDeclInit(Node* node,
                 StrList* id_table, 
                 BufferInfo* decl_list_code,
                 StrList* passed_vars,
                 int* passed_var_count,
                 StrList* local_vars, 
                 int* local_var_count);

void GenRightValue(Node* node, // kEqual->right node
                   StrList* id_table, 
                   BufferInfo* decl_code,
                   StrList* passed_vars,
                   int* passed_var_count,
                   StrList* local_vars, 
                   int* local_var_count);

void GenStateList(Node* start_node,
                  StrList* id_table, 
                  BufferInfo* func_code,
                  StrList* passed_vars,
                  int* passed_var_count,
                  StrList* local_vars, 
                  int* local_var_count, 
                  LabelCounter* label_counter);

void GenState(Node* node,
              StrList* id_table, 
              BufferInfo* state_list_code,
              StrList* passed_vars,
              int* passed_var_count,
              StrList* local_vars, 
              int* local_var_count, 
              LabelCounter* label_counter);

void ChooseJump(Node* node, wchar_t* string);

void GenCompoundState();

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
