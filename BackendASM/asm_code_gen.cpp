#include "asm_code_gen.h"

#define NODE_VAL node->data.num

void GenSpuCode(Tree* tree, StrList* id_table)
{ 
    //-------------------------------------------
    FileInfo asm_file = {};
    OpenFile(&asm_file, "SPU/PROGRAMM_ASM.txt", "w");
    //-------------------------------------------

    Node* node = tree->root;

    while (node->type == kKeyWord && node->data.num == kStep)
    {
        GenFunc(node->right, id_table, &asm_file.buffer_info);

        node = node->left;
    }
    GenFunc(node, id_table, &asm_file.buffer_info);

    fwrite(asm_file.buffer_info.buf, sizeof(wchar_t), asm_file.buffer_info.size, asm_file.file);

    CloseFile(&asm_file);
}


void GenFunc(Node* node, 
             StrList* id_table, 
             BufferInfo* asm_code)
{
    BufferInfo func_code = {};
    func_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));

    if (node->type == kFuncDef)
    {
        BufAppendStr(&func_code, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1)));
        BufAppendStr(&func_code, L"\n");
    }

    

    BufAppendBuf(asm_code, &func_code);
    free(func_code.buf);
}

#undef NODE_VAL

