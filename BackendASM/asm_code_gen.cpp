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

    //arrange local variables for convenient access
    int var_count = 0;
    StrList* var_table = StrListCtor();
    CountVariables(node->right->right, id_table, var_table, &var_count);

    //form stack frame:
    BufAppendStr(&func_code, L"    push rbp\n"
                              "    mov rbp, rsp\n");
     
    wchar_t tmp_string[20] = {0};
    swprintf(tmp_string, 20, L"    sub rsp, %d\n", var_count * sizeof(int)); // int is the only data type so far
    BufAppendStr(&func_code, tmp_string); 
    
    BufAppendStr(&func_code, L"    and rsp, -32\n"); //allign by 8 bytes

    //function body:
    node = node->right; //parameters node

    //TODO: Compare Parameters in node->left with parameters in call  

//    GenDeclList(node->right->left, id_table, &func_code);

    //exit function
    BufAppendStr(&func_code, L"    mov rsp, rbp\n"
                              "    pop rbp\n"
                              "    ret\n");

    BufAppendBuf(asm_code, &func_code);
    free(func_code.buf);
}


//TODO: algorythm needs to be optimized 
// node -- funcdef node
void CountVariables(Node* node, 
                    StrList* id_table, 
                    StrList* var_table, 
                    int* var_count)
{
    if (node->left)
    {
        node = node->left;
        while (node->data.num == kStep)
        {
            StrListAdd(var_table, GET_NODE_DATA(StrListGetNode(id_table, node->right->data.num)), *var_count);
            (*var_count)++;
            node = node->left;
        }
        StrListAdd(var_table, GET_NODE_DATA(StrListGetNode(id_table, node->right->data.num)), *var_count);
        (*var_count)++;
    }
}


void GenDeclList(Node* node,
                 StrList* id_table, 
                 BufferInfo* func_code)
{
    BufferInfo decl_list = {};

    int var_count = 0;
    while (node->data.num == kStep)
    {
        GenDeclInit(node->right, id_table, &decl_list, &var_count);

        node = node->left;
    }

    GenDeclInit(node, id_table, &decl_list, &var_count);
}


void GenDeclInit(Node* node,
                 StrList* id_table, 
                 BufferInfo* decl_list_code, 
                 int* var_count)
{
    wchar_t decl[20] = {0};

    if (node->right->data.num == kEqual)
    {

    }

    (*var_count)++;
}   

//-----------------------------------------------

void GenId(Node* node,
           StrList* id_table, 
           BufferInfo* code)
{
    BACK_ASSERT(node->type == kIdentifier);

    StrList* id = StrListGetNode(id_table, node->data.num); 
    BufAppendStr(code, GET_NODE_DATA(id));
}


void GenNumber(Node* node,
               StrList* id_table, 
               BufferInfo* code)
{
    BACK_ASSERT(node->type == kConstant)

    wchar_t* num_code = (wchar_t*)calloc(15, sizeof(wchar_t));

    swprintf(num_code, 15, L"%ld", node->data.num);

    BufAppendStr(code, num_code);
    free(num_code);
}

#undef BACK_ASSERT
