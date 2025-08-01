#include "../Tree/tree.h"
#include "../StringList/list.h"

#ifndef SPU_CODE_GEN_HEADER
#define SPU_CODE_GEN_HEADER

void GenSpuCode(Tree* tree);

void GenFuncCode(Node* node, StrList* id_table, BufferInfo* func_code);

#endif
