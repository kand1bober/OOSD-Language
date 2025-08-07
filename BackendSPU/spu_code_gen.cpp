#include "spu_code_gen.h"

#define NODE_VAL node->data.num

void GenSpuCode(Tree* tree, StrList* id_table)
{ 
    // //-------------------------------------------
    // FileInfo asm_file = {};
    // // OpenFile(&asm_file, "SPU/PROGRAMM_ASM.txt", "w");
    // //-------------------------------------------

    // Node* node = tree->root;
    // BufferInfo func_code = {};
    // func_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));

    // while (node->data.num == kStep)
    // {
    //     GenFunc(node, id_table, &func_code);
    //     BufAppendBuf(&asm_file.buffer_info, &func_code);

    //     node = node->left;
    // }
    // if (node->data.num == kFuncDef)
    // {
    //     GenFunc(node, id_table, &func_code);
    //     BufAppendBuf(&asm_file.buffer_info, &func_code);
    // }

    // CloseFile(&asm_file);
    // free(func_code.buf);
}


void GenFunc(Node* node, StrList* id_table, BufferInfo* func_code)
{
    BufAppendStr(func_code, GET_NODE_DATA(StrListGetNode(id_table, node->data.num)));

    BufAppendStr(func_code, L"\n");
}

#undef NODE_VAL

