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

    BufAppendStr(&asm_file.buffer_info, L"section .text\n"
                                         "    global main\n\n");

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
    int local_var_count = 0, passed_var_count = 0;
    StrList* passed_vars = StrListCtor();
    StrList* local_vars = StrListCtor();
    CountVariables(node->right, 
                   id_table, 
                   passed_vars, 
                   &passed_var_count, 
                   local_vars, 
                   &local_var_count);
    // StrListDot(var_table);
    // getchar();

    //form stack frame:
    BufAppendStr(&func_code, L"    push rbp\n"
                              "    mov rbp, rsp\n");
     
    wchar_t tmp_string[20] = {0};
    swprintf(tmp_string, 20, L"    sub rsp, %d\n", local_var_count * sizeof(int)); // int is the only data type so far
    BufAppendStr(&func_code, tmp_string); 
    
    BufAppendStr(&func_code, L"    and rsp, -32\n\n"); //allign by 8 bytes

    //function body:
    //TODO: Compare Parameters in node->left with parameters in call 
    GenDeclList(node->right, 
                id_table, 
                &func_code, 
                passed_vars, 
                &passed_var_count, 
                local_vars, 
                &local_var_count);
    
    // GenStateList(node->left, id_table, var_table, &func_code);
    
    //exit function
    BufAppendStr(&func_code, L"    mov rsp, rbp\n"
                              "    pop rbp\n"
                              "    ret\n\n");

    BufAppendBuf(asm_code, &func_code);
    free(func_code.buf);
    StrListDtor(passed_vars);
    StrListDtor(local_vars);
}


/*
*   recursive function; 
*   should be called to the left and right->left son's 
*   of prameter node of functon definition
*/
void CountVariables(Node* start_node, //parameter_node
                    StrList* id_table, 
                    StrList* passed_vars,
                    int* passed_var_count,
                    StrList* local_vars, 
                    int* local_var_count)
{
    #define COUNT_LOCAL_VAR(expr)   StrListAdd(local_vars, GET_NODE_DATA(StrListGetNode(id_table, (expr)->data.num + 1)), *local_var_count); \
                                    (*local_var_count)++; 

    #define COUNT_PASSED_VAR(expr)   StrListAdd(passed_vars, GET_NODE_DATA(StrListGetNode(id_table, (expr)->data.num + 1)), *passed_var_count); \
                                    (*passed_var_count)++;

    //passed variables
    Stack_t stack = {}; 
    StackCtor(&stack);

    int count_nodes = 0;
    Node* node = start_node->left;

    if (node)
    {
        while (node->left->type != kKeyWord || node->left->data.num != kNumber) //stops when kNumber is faced
        {
            StackPush(&stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }     

        COUNT_PASSED_VAR(node)

        while (count_nodes)
        {
            COUNT_PASSED_VAR((Node*)(StackPop(&stack).pointer_t))
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
            StackPush(&stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }

        COUNT_LOCAL_VAR(node)
        while (count_nodes)
        {
            COUNT_LOCAL_VAR((Node*)(StackPop(&stack).pointer_t));
            count_nodes--;
        }
    }

    StackDtor(&stack);    

    #undef COUNT_LOCAL_VAR
    #undef COUNT_PASSED_VAR
}


void GenDeclList(Node* start_node,
                 StrList* id_table, 
                 BufferInfo* func_code,
                 StrList* passed_vars,
                 int* passed_var_count,
                 StrList* local_vars, 
                 int* local_var_count)
{
    BufferInfo decl_list_code = {};
    
    Stack_t stack = {}; 
    StackCtor(&stack);
    
    //local variables
    int count_nodes = 0;
    Node* node = start_node->right->left;    
    if (node)
    {
        while (node->left->type != kKeyWord || node->left->data.num != kNumber)
        {
            StackPush(&stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }

        GenDeclInit(node, 
                    id_table, 
                    &decl_list_code, 
                    passed_vars, 
                    passed_var_count, 
                    local_vars, 
                    local_var_count);
        while (count_nodes)
        {
            GenDeclInit((Node*)(StackPop(&stack).pointer_t), 
                        id_table, 
                        &decl_list_code, 
                        passed_vars, 
                        passed_var_count, 
                        local_vars, 
                        local_var_count);
            count_nodes--;
        }
    }

    BufAppendBuf(func_code, &decl_list_code);
    free(decl_list_code.buf);
    StackDtor(&stack);    
}


void GenDeclInit(Node* node,
                 StrList* id_table, 
                 BufferInfo* decl_list_code,
                 StrList* passed_vars,
                 int* passed_var_count,
                 StrList* local_vars, 
                 int* local_var_count)
{
    wchar_t string[40] = {0};
    BufferInfo decl_code = {};
    decl_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));
    decl_code.size = 0;

    int var_shift = 0;

    if (node->right->data.num == kEqual)
    {
        GenRightValue(node->right->right, 
                      id_table, 
                      &decl_code, 
                      passed_vars, 
                      passed_var_count, 
                      local_vars, 
                      local_var_count);
        
        // calcuate shift in stack
        var_shift = StrListGetNodeNum(local_vars, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1))) + 1;  
        swprintf(string, 40, L"    mov dword [rbp - 4 * %d], eax\n\n", var_shift);
        BufAppendStr(&decl_code, string);
    }

    BufAppendBuf(decl_list_code, &decl_code);
    free(decl_code.buf);
}   
 

void GenRightValue(Node* node, // kEqual->right node
                   StrList* id_table, 
                   BufferInfo* decl_code,
                   StrList* passed_vars,
                   int* passed_var_count,
                   StrList* local_vars, 
                   int* local_var_count)
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
            r_val_shift = StrListGetNodeNum(local_vars, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1))) + 1;
            if (r_val_shift != 0) //not found in local_vars
            {
                swprintf(r_value_code, 40, L"    mov eax, dword [rbp - 4 * %d]\n", r_val_shift);
            }
            else
            {
                // wprintf(YELLOW L"Hello r_val_shift: %d\n" DELETE_COLOR, r_val_shift);
                r_val_shift = StrListGetNodeNum(passed_vars, GET_NODE_DATA(StrListGetNode(id_table, node->data.num + 1))) + 1;
                BACK_ASSERT(r_val_shift != -1)

                if (r_val_shift <= 6)
                {
                    swprintf(r_value_code, 40, L"    mov eax, %ls\n", passed_vars_table[r_val_shift]);                    
                } 
                else  
                {
                    r_val_shift = (16 + 4 * (r_val_shift - 7)); 
                    swprintf(r_value_code, 40, L"    mov eax, dword [rbp + %d]\n", r_val_shift);
                }
            }

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
