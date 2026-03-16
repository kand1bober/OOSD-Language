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

    LabelCounter label_counter = {};

    Node* node = tree->root;

    BufAppendStr(&asm_file.buffer_info, L"section .text\n"
                                         "    global main\n\n");

    while (node->type == kKeyWord && node->data.num == kStep)
    {
        GenFunc(node->right, 
                id_table, 
                &asm_file.buffer_info, 
                &label_counter);

        node = node->left;
    }
    GenFunc(node, 
            id_table, 
            &asm_file.buffer_info, 
            &label_counter);

    fwrite(asm_file.buffer_info.buf, sizeof(wchar_t), asm_file.buffer_info.size, asm_file.file);

    CloseFile(&asm_file);
}


void GenFunc(Node* node, 
             StrList* id_table, 
             BufferInfo* asm_code, 
             LabelCounter* label_counter)
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
    GenDeclList(node->right, //parameter node
                id_table, 
                &func_code, 
                passed_vars, 
                &passed_var_count, 
                local_vars, 
                &local_var_count);
    
    // GenStateList(node->right, //parameter node
    //              id_table, 
    //              &func_code, 
    //              passed_vars, 
    //              &passed_var_count, 
    //              local_vars, 
    //              &local_var_count, 
    //              label_counter);
    
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


/*
* 
*
* if identifier, place it in eax 
*/
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

//-----------------------------------------------

void GenStateList(Node* start_node,
                  StrList* id_table, 
                  BufferInfo* func_code,
                  StrList* passed_vars,
                  int* passed_var_count,
                  StrList* local_vars, 
                  int* local_var_count, 
                  LabelCounter* label_counter)
{
    BufferInfo state_list_code = {};

    Stack_t stack = {}; 
    StackCtor(&stack);
    
    //local variables
    int count_nodes = 0;
    Node* node = start_node->right->right;    
    if (node->type == kKeyWord && node->data.num == kStep )
    {
        while (!(node->left->type == kKeyWord && node->left->data.num == kEqual && 
                 node->left->data.num == kEcmp && node->left->data.num == kBcmp && 
                 node->left->data.num == kAcmp && node->left->data.num == kBEcmp && 
                 node->left->data.num == kAEcmp && node->left->data.num == kNEcmp && 
                 node->left->data.num == kAND && node->left->data.num == kOR &&
                 node->left->data.num == kNOT))
        {
            StackPush(&stack, {.pointer_t = node->right});
            node = node->left;
            count_nodes++;
        }

        GenState(node, 
                 id_table, 
                 &state_list_code, 
                 passed_vars, 
                 passed_var_count, 
                 local_vars, 
                 local_var_count, 
                 label_counter);
        while (count_nodes)
        {
            GenState((Node*)(StackPop(&stack).pointer_t), 
                     id_table, 
                     &state_list_code, 
                     passed_vars, 
                     passed_var_count, 
                     local_vars, 
                     local_var_count, 
                     label_counter);
            count_nodes--;
        }
    }
    else  

    BufAppendBuf(func_code, &state_list_code);
    free(state_list_code.buf);
    StackDtor(&stack);    
}


void GenState(Node* node,
              StrList* id_table, 
              BufferInfo* state_list_code,
              StrList* passed_vars,
              int* passed_var_count,
              StrList* local_vars, 
              int* local_var_count,
              LabelCounter* label_counter)
{
    BufferInfo state_code = {};
    state_code.buf = (wchar_t*)calloc(10, sizeof(wchar_t));
    state_code.size = 0;

    wchar_t string[100] = {0};

    switch (node->data.num)
    {
        case kIf:
        case kWhile: 
        {
            GenExpr(node->left);

            if (node->data.num == kIf)
            {
                ChooseJump(node->left, string);
                swprintf(string + wcslen(string), 100 - wcslen(string), L"if_%d_body\n"
                                                                    "    jmp if_%d_end\n"
                                                                    "    if_%d_body:\n", 
                                                                    label_counter->if_count, 
                                                                    label_counter->if_count, 
                                                                    label_counter->if_count);
                label_counter->if_count++;
            }
            else if (node->data.num == kWhile)
            {
                ChooseJump(node->left, string);
                swprintf(string + wcslen(string), 100 - wcslen(string), L"while_%d_body\n"
                                                                    "    jmp while_%d_end\n"
                                                                    "    while_%d_body:\n", 
                                                                    label_counter->while_count, 
                                                                    label_counter->while_count, 
                                                                    label_counter->while_count);
                label_counter->while_count++;
            }
            BufAppendStr(&state_code, string);

            GenCompoundState(node->right);

            if (node->data.num == kIf) 
            {
                swprintf(string, 100, L"    if_%d_end:\n\n");
            }
            else if (node->data.num == kWhile)
            {
                swprintf(string, 100, L"    while_%d_end:\n\n");
            }
            else  
            {
                BACK_ERROR
            }

            BufAppendStr(&state_code, string);
            break;
        }
        case kContinue:
        {

            break;
        }
        case kBreak:
        {

            break;
        }
        case kAbort:
        {

            break;
        }
        case kRet:
        {

            break;
        }
        default:
        {
            BACK_ERROR            
        }
    }

    BufAppendBuf(state_list_code, &state_code);
    free(state_code.buf);
}

void ChooseJump(Node* node, wchar_t* string)
{
    typedef struct
    {
        KeyCode key_code;
        const wchar_t* jump_str;
    } Jumps;

    Jumps jump_list[] = 
    {
        #define DEF_JUMP(key_code, jump_str) {key_code, jump_str}

        DEF_JUMP(kEcmp,  L"je"),
        DEF_JUMP(kAcmp,  L"jg"),
        DEF_JUMP(kBcmp,  L"jl"),
        DEF_JUMP(kAEcmp, L"jge"),
        DEF_JUMP(kBEcmp, L"jle"),
        DEF_JUMP(kNEcmp, L"jne"),
        DEF_JUMP(kAND,   L""),
        DEF_JUMP(kOR,    L""),
        DEF_JUMP(kNOT,   L""),

        #undef DEF_JUMP
    };

    int index = 0;
    while (jump_list[index].key_code != node->data.num)
        index++;
    
    swprintf(string, 10, L"    %ls ", jump_list[index].jump_str);
}

void GenCompoundState(Node* node,
                      StrList* id_table, 
                      BufferInfo* state_list_code,
                      StrList* passed_vars,
                      int* passed_var_count,
                      StrList* local_vars, 
                      int* local_var_count)
{

}

void GenExpr(Node* node,
             StrList* id_table, 
             BufferInfo* state_list_code,
             StrList* passed_vars,
             int* passed_var_count,
             StrList* local_vars, 
             int* local_var_count)
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
