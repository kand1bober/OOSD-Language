#include "asm_code_gen.h"

#define BACK_ASSERT(expr) if (!(expr)) \
                          { \
                               wprintf(RED L"Backend: badly formed tree\n" DELETE_COLOR); \
                               exit(1); \
                          } 

void GenSpuCode(Tree* tree, StrList* id_table)
{ 
    //-------------------------------------------
    FileInfo asm_file = {};
    // OpenFile(&asm_file, "SPU/PROGRAMM_ASM.txt", "w");
    OpenFile(&asm_file, "BackendASM/code.txt", "w");
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
    BACK_ASSERT(node->type == kFuncDef)

    BufferInfo func_code = {};
    func_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));

    //label:
    BufAppendStr(&func_code, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1)));
    BufAppendStr(&func_code, L":\n");

    //form stack frame:
    int var_count = 0;
    CountVariables(node, &var_count);

    BufAppendStr(&func_code, L"    push rbp\n"
                              "    mov rbp, rsp\n");
    
    wchar_t tmp_string[20] = {0};
    swprintf(tmp_string, 20, L"    sub rsp, %d\n", var_count);
    BufAppendStr(&func_code, tmp_string); 

    BufAppendStr(&func_code, L"    and rsp, -32\n"); //allign by 8 bytes

    /// вызов тела функции 

    //exit function
    BufAppendStr(&func_code, L"    mov rsp, rbp\n"
                              "    pop rbp\n"
                              "    ret\n");

    BufAppendBuf(asm_code, &func_code);
    free(func_code.buf);
}


//TODO: algorythm needs to be optimized 
// node -- funcdef node
void CountVariables(Node* node, int* count)
{
    if (node->type == kVarDecl)
        (*count)++;
    
    if (node->left)
        CountVariables(node->left, count);
    if (node->right)
        CountVariables(node->right, count);
}


void GenDeclInit(Node* node,
                 StrList* id_table, 
                 BufferInfo* asm_code)
{
    

    if (node->right->type == kKeyWord && node->right->data.num == kEqual)
    {

    }

}

//-----------------------------------------------

void GenId(Node* node,
           StrList* id_table, 
           BufferInfo* asm_code)
{
    BACK_ASSERT(node->type == kIdentifier);

    StrList* id = StrListGetNode(id_table, node->data.num); 
    BufAppendStr(asm_code, GET_NODE_DATA(id));
}


void GenNumber(Node* node,
               StrList* id_table, 
               BufferInfo* asm_code)
{
    BACK_ASSERT(node->type == kConstant)

    wchar_t* num_code = (wchar_t*)calloc(15, sizeof(wchar_t));

    swprintf(num_code, 15, L"%ld", node->data.num);

    BufAppendStr(asm_code, num_code);
    free(num_code);
}

#undef BACK_ASSERT
