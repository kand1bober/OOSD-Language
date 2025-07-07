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

