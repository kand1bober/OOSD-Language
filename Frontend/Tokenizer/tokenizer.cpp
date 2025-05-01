#include "tokenizer.h"

void MakeTokenization(Tokenizer* tokenizer)
{
    StrList* str_list = tokenizer->str_list->next;      //
    size_t str_list_size = tokenizer->str_list_size;    // take from struct

    tokenizer->num_list = NumListCtor();                //
    NumList* num_list = tokenizer->num_list;            // take from struct
    size_t num_list_size = tokenizer->num_list_size;    //

    int token_encoding = -1; // init
    while (str_list != tokenizer->str_list) 
    {
        token_encoding = SearchKeyWord(GET_NODE_DATA(str_list));

        NumListAdd(num_list, token_encoding, num_list_size);
        num_list_size++;
    }

    tokenizer->num_list_size = num_list_size;   // return struct
}


int SearchKeyWord(const wchar_t* lexem)
{   
    for (int i = 0; i < keywords_amount; i++)
    {       
        if (!wcsncmp(lexem, keyword_table[i].key_word, keyword_table[i].key_word_len))
        {
            return keyword_table[i].key_code;
        }
        
        //TODO: здесь больше условий. Например несколько лексем это один токен 
    }

    return -1;  // not found
}

