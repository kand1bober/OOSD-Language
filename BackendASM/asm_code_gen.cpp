#include "asm_code_gen.h"

#define BACK_ASSERT(expr) if (!(expr)) \
                          { \
                               wprintf(RED L"Backend: badly formed tree\n" DELETE_COLOR); \
                               exit(1); \
                          } 
                          
#define BACK_ERROR    wprintf(RED L"Syntax error:\n"  \
                              RED "file:" DELETE_COLOR " %s\n"        \
                              RED "func:" DELETE_COLOR " %s\n"        \
                              RED "line:" DELETE_COLOR " %d\n" DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                      exit(1); 

void GenSpuCode(Tree* tree, StrList* id_table)
{ 
    //-------------------------------------------
    FileInfo asm_file = {};
    // OpenFile(&asm_file, "SPU/PROGRAMM_ASM.txt", "w");
    OpenFile(&asm_file, "BackendASM/code.txt", "w");
    //-------------------------------------------

    Node* node = tree->root;

    BufAppendStr(&asm_file.buffer_info, L"\nsection .text\n"
                                         "    global main\n");

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
    BufAppendStr(&func_code, L"\n");
    BufAppendStr(&func_code, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1)));
    BufAppendStr(&func_code, L":\n");


    //arrange local variables for convenient access
    int var_count = 0;
    StrList* var_table = StrListCtor();
    Stack_t stack = {}; 
    StackCtor(&stack);
    CountVariables(node->right, id_table, var_table, &var_count, &stack);
    // StrListDot(var_table);
    // getchar();

    //form stack frame:
    BufAppendStr(&func_code, L"    push rbp\n"
                              "    mov rbp, rsp\n");
     
    wchar_t tmp_string[20] = {0};
    swprintf(tmp_string, 20, L"    sub rsp, %d\n", var_count * sizeof(int)); // int is the only data type so far
    BufAppendStr(&func_code, tmp_string); 
    
    BufAppendStr(&func_code, L"    and rsp, -32\n\n"); //allign by 8 bytes

    //function body:
    //TODO: Compare Parameters in node->left with parameters in call 
    GenDeclList(node->right, id_table, var_table, &func_code, &stack);
    
    // GenStateList(node->left, id_table, var_table, &func_code);
    
    //exit function
    BufAppendStr(&func_code, L"\n    mov rsp, rbp\n"
                              "    pop rbp\n"
                              "    ret\n");

    BufAppendBuf(asm_code, &func_code);
    free(func_code.buf);
    StrListDtor(var_table);
    StackDtor(&stack);
}


/*
*   recursive function; 
*   should be called to the left and right->left son's 
*   of prameter node of functon definition
*/
void CountVariables(Node* start_node, //parameter_node
                    StrList* id_table, 
                    StrList* var_table, 
                    int* var_count,
                    Stack_t* stack)
{
    #define COUNT_LOCAL_VAR(expr)   StrListAdd(var_table, GET_NODE_DATA(StrListGetNode(id_table, (expr)->data.num + 1)), *var_count); \
                                    (*var_count)++; 

    #define COUNT_PASSED_VAR(expr)   StrListAdd(var_table, GET_NODE_DATA(StrListGetNode(id_table, (expr)->data.num + 1)), *var_count);

    //passed variables
    int count_nodes = 0;
    Node* node = start_node->left;

    if (node)
    {
        while (node->left->type != kKeyWord || node->left->data.num != kNumber) //stops when kNumber is faced
        {
            StackPush(stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }     

        COUNT_PASSED_VAR(node)

        while (count_nodes)
        {
            COUNT_PASSED_VAR((Node*)(StackPop(stack).pointer_t))
            count_nodes--;
        }
    }

    //local variables
    count_nodes = 0;
    node = start_node->right->left;    
    if (node)
    {
        while (node->left->type != kKeyWord || node->left->data.num != kNumber)
        {
            StackPush(stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }

        COUNT_LOCAL_VAR(node)
        while (count_nodes)
        {
            COUNT_LOCAL_VAR((Node*)(StackPop(stack).pointer_t));
            count_nodes--;
        }
    }

    #undef COUNT_VAR
}


void GenDeclList(Node* start_node,
                 StrList* id_table, 
                 StrList* var_table,
                 BufferInfo* func_code,
                 Stack_t* stack)
{
    BufferInfo decl_list_code = {};
    
    //local variables
    int count_nodes = 0;
    Node* node = start_node->right->left;    
    if (node)
    {
        while (node->left->type != kKeyWord || node->left->data.num != kNumber)
        {
            StackPush(stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }

        GenDeclInit(node, id_table, var_table, &decl_list_code);
        while (count_nodes)
        {
            GenDeclInit((Node*)(StackPop(stack).pointer_t), id_table, var_table, &decl_list_code);
            count_nodes--;
        }
    }

    BufAppendBuf(func_code, &decl_list_code);
    free(decl_list_code.buf);
}


void GenDeclInit(Node* node,
                 StrList* id_table, 
                 StrList * var_table,
                 BufferInfo* decl_list_code)
{
    wchar_t string[40] = {0};
    BufferInfo decl_code = {};
    decl_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));
    decl_code.size = 0;

    int var_shift = 0;

    if (node->right->data.num == kEqual)
    {
        GenRightValue(node->right->right, id_table, var_table, &decl_code);
        
        // calcuate shift in stack
        var_shift = StrListGetNodeNum(var_table, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1))) + 1;  
        // wprintf(YELLOW L"var_shift: %d\n" DELETE_COLOR, var_shift);
        swprintf(string, 40, L"    mov dword [rbp - 4 * %d], eax\n", var_shift);
        BufAppendStr(&decl_code, string);
    }

    BufAppendBuf(decl_list_code, &decl_code);
    free(decl_code.buf);
}   
 

void GenRightValue(Node* node, // kEqual->right node
                   StrList* id_table, 
                   StrList* var_table,
                   BufferInfo* decl_code)
{
    wchar_t r_value_code[40] = {0};

    switch (node->type)
    {
        case kCall:
            break;
        case kConstant:
        {
            swprintf(r_value_code, 40, L"    mov eax, %d\n", node->data.num);
            break;
        }
        case kIdentifier:
        {
            int r_val_shift = 0;
            r_val_shift = StrListGetNodeNum(var_table, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1))) + 1;
            swprintf(r_value_code, 40, L"    mov eax, dword [rbp - 4 * %d]\n", r_val_shift);
            break;
        }
        default:
        {
            BACK_ERROR 
        }
    }

    BufAppendStr(decl_code, r_value_code);
}


void GetStateList(Node* node,
                 StrList* id_table, 
                 StrList * var_table,
                 BufferInfo* func_code)
{

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
#undef BACK_ASSERT 
