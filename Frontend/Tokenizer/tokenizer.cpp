#include "tokenizer.h"

void Tokenization(Tokenizer* tokenizer)
{
    StrList* str_list = tokenizer->str_list->next;

    tokenizer->num_list = NumListCtor();
    tokenizer->num_list_size = 0;

    tokenizer->id_table = StrListCtor();
    tokenizer->id_table_size = 0;

    KeyCode token_type = kId;
    while (str_list != tokenizer->str_list) 
    {
        token_type = SearchKeyWord(GET_NODE_DATA(str_list), str_list->str_len);
        if (token_type == kId)
        {
            StrListAdd(tokenizer->id_table, GET_NODE_DATA(tokenizer->str_list), tokenizer->id_table_size);
            tokenizer->id_table_size++;
            NumListAdd(tokenizer->num_list, kPtrData, {.ptr = StrListGetNode(tokenizer->id_table, tokenizer->id_table_size)}, tokenizer->num_list_size);
            tokenizer->num_list_size++;
        }
        else  
        {
            NumListAdd(tokenizer->num_list, kNumData, {.number = token_type}, tokenizer->num_list_size);
            tokenizer->num_list_size++;
        }

        str_list = str_list->next;
    }   

    StrListDot(tokenizer->id_table);
}


KeyCode SearchKeyWord(const wchar_t* str, int str_len)
{   
    int len_to_compare = 0;

    for (int i = 0; i < kKeyWordsAmount; i++)
    {       
        len_to_compare = (str_len > keyword_table[i].key_word_len) ? str_len : keyword_table[i].key_word_len;
        if (!wcsncmp(str, keyword_table[i].key_word, len_to_compare))
        {
            return keyword_table[i].key_code;
        }
    }

    return kId;  // keyword not found
}


void CloseTokenizer(Tokenizer* tokenizer)
{
    StrListDtor(tokenizer->id_table);
    NumListDtor(tokenizer->num_list);
}
