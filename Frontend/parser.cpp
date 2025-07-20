#include "parser.h"
#include <cstdlib>

#define GO_TO_NEXT_TOKEN src->cur_token = src->cur_token->next;    
#define GO_TO_PREV_TOKEN src->cur_token = src->cur_token->prev;
#define TOKEN_VAL        src->cur_token->data.number
#define TOKEN_ID_VAL     GET_NODE_DATA(src->cur_token->data.ptr)

#define SET_OLD_TOKEN    src->old_token = src->cur_token;
#define OLD_TOKEN_VAL    src->old_token->data.number

#define SYNTAX_ERROR    wprintf(RED L"Syntax error:\n"  \
                                RED "file:" DELETE_COLOR " %s\n"        \
                                RED "func:" DELETE_COLOR " %s\n"        \
                                RED "line:" DELETE_COLOR " %d\n" DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                        exit(1); \

#define SYNTAX_ASSERT(expr)     if (TOKEN_VAL != expr) \
                                {                   \
                                    SYNTAX_ERROR    \
                                }                   

#define DEBUG_PRINT     wprintf(YELLOW L"in func" RED " \"%s\"" YELLOW ", curr token:\n" \
                                        "data_type: %ld\n" \
                                        ".num = %ld\n.ptr = %p\n\n" DELETE_COLOR, \
                                        __PRETTY_FUNCTION__,  src->cur_token->data_type, \
                                        src->cur_token->data.number, src->cur_token->data.ptr);

//------------RECURSIVE DESCENT------------------

void GetSyntaxTree(Parser* src, Lexer* tokenizer)
{   
    src->cur_token = tokenizer->num_list;

    SYNTAX_ASSERT(NUM_LIST_POISON)
    GO_TO_NEXT_TOKEN

    src->tree = TreeCtor();
    src->tree->root = GetTransUnit(src);

    SYNTAX_ASSERT(NUM_LIST_POISON)

}


Node* GetTransUnit(Parser* src)
{   
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetExtDecl(src);
    left_node = node;
    while (TOKEN_VAL != NUM_LIST_POISON)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = kStep});

        right_node = GetExtDecl(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetExtDecl(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    if (TOKEN_VAL == kNumber)
    {
        GO_TO_NEXT_TOKEN

        if (src->cur_token->data_type == kPtrData)
        {
            GO_TO_NEXT_TOKEN

            if (TOKEN_VAL == kLeftBracket)
            {
                GO_TO_PREV_TOKEN
                GO_TO_PREV_TOKEN
                node = GetFuncDef(src);
            }
            else  
            {
                GO_TO_PREV_TOKEN
                GO_TO_PREV_TOKEN
                node = GetDeclInit(src);  

                SYNTAX_ASSERT(kStep)
                GO_TO_NEXT_TOKEN
            }
        } 
        else  
        {
            wprintf(RED L"Missing identifier after data type\n" DELETE_COLOR);
            SYNTAX_ERROR 
        }
    }
    else  
    {
        node = NULL;
    }

    return node;
}


Node* GetFuncDef(Parser* src)
{
    Node* node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;
    Node* right_left_node = NULL;
    Node* right_right_node = NULL;

    left_node = CreateNode(NULL, NULL, node, kKeyWord, {.num = TOKEN_VAL});
    GO_TO_NEXT_TOKEN

    node = CreateNode(NULL, NULL, NULL, kFuncDef, {.str = TOKEN_ID_VAL});
    GO_TO_NEXT_TOKEN

    SYNTAX_ASSERT(kLeftBracket)
    GO_TO_NEXT_TOKEN

    InsertLeave(src->tree, node, kLeft, left_node);

    right_node = CreateNode(NULL, NULL, node, kParameters, {.num = TOKEN_VAL});
    InsertLeave(src->tree, node, kRight, right_node);

    if (TOKEN_VAL == kNumber)
    {
        right_left_node = GetDeclList(src);
        InsertLeave(src->tree, right_node, kLeft, right_left_node);
    }

    SYNTAX_ASSERT(kRightBracket)
    GO_TO_NEXT_TOKEN

    right_right_node = GetCompoundState(src);
    InsertLeave(src->tree, right_node, kRight, right_right_node);

    return node;
}


Node* GetDeclList(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetDeclInit(src);
    left_node = node;
    while (TOKEN_VAL == kEnum)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetDeclInit(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetDeclInit(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;
    Node* right_right_node = NULL;

    if (TOKEN_VAL == kNumber)
    {
        left_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        tmp_node = GetId(src);
    }
    else  
    {
        SYNTAX_ERROR
    }

    node = CreateNode(NULL, NULL, NULL, kVarDecl, {.str = tmp_node->data.str});
    InsertLeave(src->tree, node, kLeft, left_node);

    if (TOKEN_VAL == kEqual)
    {
        right_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_right_node = GetLogic_OR_Expr(src);

        InsertLeave(src->tree, node, kRight, right_node);
        InsertLeave(src->tree, right_node, kLeft, tmp_node);
        InsertLeave(src->tree, right_node, kRight, right_right_node);
    }
    else  
    {
        InsertLeave(src->tree, node, kRight, tmp_node);
    }

    return node;
}

//-----------------------------------------------

Node* GetStateList(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    if (IsStatement(src))
    {
        node = GetState(src);
        left_node = node;
        while (IsStatement(src))
        {
            tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = kStep});

            right_node = GetState(src);

            InsertLeave(src->tree, tmp_node, kLeft, left_node);
            InsertLeave(src->tree, tmp_node, kRight, right_node);

            left_node = tmp_node;
        }   
        node = left_node;
    }

    return node;
}


bool IsStatement(Parser* src)
{
    switch (src->cur_token->data_type)
    {
        case kPtrData:
        case kConstData:
        {
            wprintf(YELLOW L"Бесполезное выражение, т.к. не имеет возвращаемого значения.\n" DELETE_COLOR);
            exit(1); 
        }
        case kNumData:
        {
            switch (TOKEN_VAL)
            {
                case kWhile:
                case kIf:
                case kContinue:
                case kBreak:
                case kAbort:
                case kRet:
                case kLeftCurlyBracket:
                {
                    return true;
                } 
                default:
                {
                    return false;
                }
            }
        }
        default:
        {
            SYNTAX_ERROR
        }
    }
}


Node* GetCompoundState(Parser* src)
{
    SYNTAX_ASSERT(kLeftCurlyBracket)
    GO_TO_NEXT_TOKEN

    Node* decl_node = NULL;
    Node* state_node = NULL;
    Node* node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = kStep});

    if (TOKEN_VAL == kNumber)
    {
        Node* tmp_node = NULL;
        Node* left_node = NULL;
        Node* right_node = NULL;

        decl_node = GetDeclList(src);
        SYNTAX_ASSERT(kStep)
        GO_TO_NEXT_TOKEN

        left_node = decl_node;
        while (TOKEN_VAL == kNumber)
        {
            tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = kStep});

            right_node = GetDeclList(src);
            SYNTAX_ASSERT(kStep)
            GO_TO_NEXT_TOKEN

            InsertLeave(src->tree, tmp_node, kLeft, left_node);
            InsertLeave(src->tree, tmp_node, kRight, right_node);

            left_node = tmp_node;
        }   

        decl_node = left_node;
        InsertLeave(src->tree, node, kLeft, decl_node);
    }

    if (TOKEN_VAL != kRightCurlyBracket && TOKEN_VAL != kNumber)
    {
        state_node = GetStateList(src);
        InsertLeave(src->tree, node, kRight, state_node);
    }

    SYNTAX_ASSERT(kRightCurlyBracket)
    GO_TO_NEXT_TOKEN

    return node;
}


Node* GetState(Parser* src)
{
    Node* node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    switch (TOKEN_VAL)
    {
        case kIf:
        case kWhile:
        {
            node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
            GO_TO_NEXT_TOKEN
            SYNTAX_ASSERT(kLeftBracket)
            GO_TO_NEXT_TOKEN
            left_node = GetExpr(src);
            SYNTAX_ASSERT(kRightBracket)
            GO_TO_NEXT_TOKEN
            right_node = GetCompoundState(src); 

            InsertLeave(src->tree, node, kLeft, left_node);
            InsertLeave(src->tree, node, kRight, right_node);

            break;
        }
        case kContinue:
        case kBreak:
        case kAbort:
        {
            node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
            GO_TO_NEXT_TOKEN

            SYNTAX_ASSERT(kStep)
            GO_TO_NEXT_TOKEN

            break;
        }
        case kRet:
        {
            node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
            GO_TO_NEXT_TOKEN
            right_node = GetExpr(src);

            SYNTAX_ASSERT(kStep)
            GO_TO_NEXT_TOKEN

            InsertLeave(src->tree, node, kRight, right_node);

            break;
        }
        case kLeftCurlyBracket:
        {
            node = GetCompoundState(src);
        }
        default:
        {
            SYNTAX_ERROR
        }

    }

    return node; 
}

//-----------------------------------------------

Node* GetExpr(Parser* src)
{
    return GetLogic_OR_Expr(src);
}


Node* GetLogic_OR_Expr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetLogic_AND_Expr(src);
    left_node = node;
    while (TOKEN_VAL == kOR)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetLogic_AND_Expr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetLogic_AND_Expr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetEqualityExpr(src);
    left_node = node;
    while (TOKEN_VAL == kAND)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetEqualityExpr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetEqualityExpr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetRelationalExpr(src);
    left_node = node;
    while (TOKEN_VAL == kEcmp || TOKEN_VAL == kNEcmp)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetRelationalExpr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetRelationalExpr(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetAdditiveExpr(src);
    left_node = node;
    while (TOKEN_VAL == kAcmp || TOKEN_VAL == kAEcmp || 
            TOKEN_VAL == kBcmp || TOKEN_VAL == kBEcmp)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetAdditiveExpr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


/*
* Get Plus/Minus expression
*/
Node* GetAdditiveExpr(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetMulExpr(src);
    left_node = node;
    while (TOKEN_VAL == kAdd || TOKEN_VAL == kSub)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetMulExpr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


/*
*   Get Multiplicative expression
*/
Node* GetMulExpr(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetPrimaryExpr(src);
    left_node = node;
    while (TOKEN_VAL == kMul || TOKEN_VAL == kDiv)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetPrimaryExpr(src);

        InsertLeave(src->tree, tmp_node, kLeft, left_node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        left_node = tmp_node;
    }   

    node = left_node;

    return node;
}


Node* GetPrimaryExpr(Parser* src)
{
    Node* node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;
    Node* tmp_node = NULL;

    switch (src->cur_token->data_type)
    {
        case kPtrData:
        {
            node = GetId(src);

            if (TOKEN_VAL == kLeftBracket)
            {
                GO_TO_NEXT_TOKEN
                
                right_node = node;
                node = CreateNode(NULL, NULL, NULL, kCall, {.num = 0});

                InsertLeave(src->tree, node, kRight, right_node);

                left_node = GetCallParams(src); 
                if (left_node)
                    InsertLeave(src->tree, node, kLeft, left_node);

                SYNTAX_ASSERT(kRightBracket)
                GO_TO_NEXT_TOKEN
            }

            break;
        } 
        case kNumData:
        {
            switch (TOKEN_VAL)
            {
                case kLeftBracket:
                {
                    GO_TO_NEXT_TOKEN
                    node = GetExpr(src);

                    SYNTAX_ASSERT(kRightBracket)
                    
                    GO_TO_NEXT_TOKEN
                    break;
                }

                case kSin: 
                case kCos: 
                case kFloor: 
                {
                    node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
                    GO_TO_NEXT_TOKEN

                    SYNTAX_ASSERT(kLeftBracket)
                    GO_TO_NEXT_TOKEN

                    Node* right_node = GetExpr(src);
                    // Node* right_node = GetNumber(src);
                    
                    SYNTAX_ASSERT(kRightBracket)
                    GO_TO_NEXT_TOKEN

                    InsertLeave(src->tree, node, kRight, right_node);
                    break;
                }
                case kDiff:
                {
                    wprintf(YELLOW L"Дифференицирования нет, мне было лень его добавлять :)\n" DELETE_COLOR);
                    SYNTAX_ERROR
                }

                default:
                {
                    SYNTAX_ERROR
                }
            }

            break;
        }
        case kConstData:
        {
            node = GetNumber(src);
            break;
        }
        default:
        {
            SYNTAX_ERROR
        }
    }    

    return node;
}

//-----------------------------------------------

Node* GetCallParams(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    if (TOKEN_VAL != kRightBracket)
    {
        node = GetExpr(src);
        left_node = node;
        while (TOKEN_VAL == kEnum)
        {
            tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
            GO_TO_NEXT_TOKEN
            right_node = GetExpr(src);

            InsertLeave(src->tree, tmp_node, kLeft, left_node);
            InsertLeave(src->tree, tmp_node, kRight, right_node);

            left_node = tmp_node;
        }   

        node = left_node;
    }

    return node;
}


/*
* Get Number
*/
Node* GetNumber(Parser* src)
{    
    Node* new_node = CreateNode(NULL, NULL, NULL, kConstant, {.num = TOKEN_VAL});

    GO_TO_NEXT_TOKEN

    return new_node;
}


/*
* Get Identifier
*/
Node* GetId(Parser* src)
{
    Node* new_node = CreateNode(NULL, NULL, NULL, kIdentifier, {.str = TOKEN_ID_VAL});
 
    GO_TO_NEXT_TOKEN

    return new_node;
}


#undef GO_TO_NEXT_TOKEN
#undef GO_TO_PREV_TOKEN
#undef TOKEN_VAL
#undef TOKEN_ID_VAL 
#undef SET_OLD_TOKEN
#undef OLD_TOKEN_VAL
#undef SYNTAX_ERROR
#undef SYNTAX_ASSERT
#undef DEBUG_PRINT

