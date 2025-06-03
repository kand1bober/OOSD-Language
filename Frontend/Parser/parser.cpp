#include "parser.h"

// //------------RECURSIVE DESCENT------------------
void SyntaxAnalysis(Parser* parser, Tokenizer* tokenizer)
{
    parser->cur_token = tokenizer->num_list;
}

#define GO_TO_NEXT_TOKEN src->cur_token = src->cur_token->next;    
#define GO_TO_PREV_TOKEN src->cur_token = src->cur_token->prev;
#define TOKEN_VAL        src->cur_token->data.number
#define SET_OLD_TOKEN    src->old_token = src->cur_token;
#define OLD_TOKEN_VAL    src->old_token->data.number

#define GO_TO_NEXT_ID    src->cur_id = src->cur_id->next;
#define ID_VAL           GET_NODE_DATA(src->cur_id);

//-----------------------------------------------
Node* GetTransUnit(Parser* src, Tokenizer* tokenizer)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    GO_TO_NEXT_TOKEN
    node = GetExtDecl(src);
    while (TOKEN_VAL == kStep)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetExtDecl(src);
        
        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

    return node;
}


Node* GetExtDecl(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    node = GetFuncDef(src);
    switch ((int)TOKEN_VAL)
    {
        case k
    }

    return node;
}


Node* GetFuncDef(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    if (TOKEN_VAL == kNumber)
    {
        node = GetId(src);
        node->left = GetDecl(src);
        node->right = GetCompoundState(src);
    }
    else 
        SYNTAX_ERROR

    return node;
}


Node* GetDecl(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    if (TOKEN_VAL == kNumber)
    {
        node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        node->right = node = GetDeclInit(src);

    }
    else  
        SYNTAX_ERROR 

    return node;
}


// Node* GetDeclList(Parser* src)
// {
//     Node* node = NULL;
//     Node* tmp_node = NULL;
//     Node* right_node = NULL;

//     node = GetDecl(src);
//     while (TOKEN_VAL == kStep)
//     {
//         tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
//         GO_TO_NEXT_TOKEN

//         right_node = GetDecl(src);
        
//         InsertLeave(src->tree, tmp_node, kLeft, node);
//         InsertLeave(src->tree, tmp_node, kRight, right_node);

//         node = tmp_node;
//     }   

//     return node;
// }


// Node* GetDeclInitList(Parser* src)
// {
//     Node* node = NULL;
//     Node* tmp_node = NULL;
//     Node* right_node = NULL;

//     node = GetDeclInit(src);
//     while (TOKEN_VAL == kStep)
//     {
//         tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
//         GO_TO_NEXT_TOKEN

//         right_node = GetDeclInit(src);
        
//         InsertLeave(src->tree, tmp_node, kLeft, node);
//         InsertLeave(src->tree, tmp_node, kRight, right_node);

//         node = tmp_node;
//     }   

//     return node;
// }


Node* GetDeclInit(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* right_node = NULL;

    node = GetId(src);
    
    if (TOKEN_VAL == kEqual)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kVarDecl, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetNumber(src);

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }

    return node;
}

// Node* GetLabeledState(Parser* src)
// {

// }


// Node* GetExprState(Parser* src)
// {

// }


// Node* GetCompoundState(Parser* src)
// {

// }


// Node* GetSelectState(Parser* src)
// {

// }

// Node* GetIterState(Parser* src)
// {

// }

// Node* GetJumpState(Parser* src)
// {

// }

Node* GetExpr(Parser* src)
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetAssignExpr(src);
    while (TOKEN_VAL == kEnum)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetAssignExpr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

    return node;
}


Node* GetAssignExpr(Parser* src)
{   
    Node* root = NULL;
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;

    SET_OLD_TOKEN
    GO_TO_NEXT_TOKEN

    if (TOKEN_VAL == kEqual) 
    {   
        root = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        tmp_node = root;    
        left_node = GetPrimaryExpr(src);
        InsertLeave(src->tree, tmp_node, kLeft, left_node);

        SET_OLD_TOKEN
        GO_TO_NEXT_TOKEN
        tmp_node = tmp_node->right;

        while (TOKEN_VAL == kEqual)
        {
            tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
            left_node = GetPrimaryExpr(src);
            InsertLeave(src->tree, tmp_node, kLeft, left_node);

            SET_OLD_TOKEN
            GO_TO_NEXT_TOKEN
            tmp_node = tmp_node->right;
        }   

        node = GetLogic_OR_Expr(src);
        InsertLeave(src->tree, tmp_node, kRight, node);
        node = root;
    }

    GO_TO_PREV_TOKEN
    node = GetLogic_OR_Expr(src);

    return node;
}


Node* GetLogic_OR_Expr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetLogic_AND_Expr(src);
    while (TOKEN_VAL == kOR)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetLogic_AND_Expr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

    return node;
}


Node* GetLogic_AND_Expr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetEqualityExpr(src);
    while (TOKEN_VAL == kAND)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetEqualityExpr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

    return node;
}


Node* GetEqualityExpr(Parser* src) 
{
    Node* node = NULL;
    Node* tmp_node = NULL;
    Node* left_node = NULL;
    Node* right_node = NULL;

    node = GetAdditiveExpr(src);
    while (TOKEN_VAL == kEcmp || TOKEN_VAL == kNEcmp)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetAdditiveExpr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

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
    while (TOKEN_VAL == kAdd || TOKEN_VAL == kSub)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetMulExpr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

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
    while (TOKEN_VAL == kMul || TOKEN_VAL == kDiv)
    {
        tmp_node = CreateNode(NULL, NULL, NULL, kKeyWord, {.num = TOKEN_VAL});
        GO_TO_NEXT_TOKEN

        right_node = GetPrimaryExpr(src);
        GO_TO_NEXT_TOKEN

        InsertLeave(src->tree, tmp_node, kLeft, node);
        InsertLeave(src->tree, tmp_node, kRight, right_node);

        node = tmp_node;
    }   

    return node;
}


Node* GetPrimaryExpr(Parser* src)
{
    GO_TO_NEXT_TOKEN

    Node* node = NULL;
    switch (int(TOKEN_VAL))
    {
        case kId:
        {
            node = GetId(src);
            GO_TO_NEXT_TOKEN
            
            src->old_id = src->cur_id;
            src->cur_id = src->cur_id->next;
            break;
        }

        case kNumber:
        {
            node = GetNumber(src);
            GO_TO_NEXT_TOKEN
            break;
        }

        case kLeftBracket:
        {
            GO_TO_NEXT_TOKEN
            node = GetExpr(src);

            if (TOKEN_VAL != kRightBracket)
                SYNTAX_ERROR
            
            GO_TO_NEXT_TOKEN
            break;
        }

        case kSin: 
        case kCos: 
        case kFloor: 
        case kAdd:
        case kSub:
        case kMul:
        case kDiv:
        case kDiff:
        case kSqrt:
        case kPow: 
            GO_TO_NEXT_TOKEN
            node = CreateNode(NULL, NULL, NULL, kConst, {.num = TOKEN_VAL});
            break;

        default:
        {
            SYNTAX_ERROR
        }
    }    

    return node;
}


/*
* Get Number
*/
Node* GetNumber(Parser* src)
{    
    src->old_token = src->cur_token;
    GO_TO_NEXT_TOKEN

    int64_t val = TOKEN_VAL;

    Node* new_node = CreateNode(NULL, NULL, NULL, kConst, {.num = val});

    return new_node;
}


/*
* Get Identifier
*/
Node* GetId(Parser* src)
{
    src->old_token = src->cur_token;
    GO_TO_NEXT_TOKEN

    Node* new_node = CreateNode(NULL, NULL, NULL, kIdentifier, {.str = GET_NODE_DATA(src->cur_id)});

    src->old_id = src->cur_id;
    src->cur_id = src->cur_id->next;

    return new_node;
}


#undef GO_TO_NEXT_TOKEN
#undef TOKEN_VAL
#undef SET_OLD_TOKEN
#undef OLD_TOKEN_VAL
