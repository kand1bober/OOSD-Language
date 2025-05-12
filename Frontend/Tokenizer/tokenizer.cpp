#include "tokenizer.h"

void MakeTokenization(Tokenizer* tokenizer)
{
    StrList* str_list = tokenizer->str_list->next;      //
    size_t str_list_size = tokenizer->str_list_size;    // take from struct

    tokenizer->num_list = NumListCtor();                //
    NumList* num_list = tokenizer->num_list;            // take from struct
    size_t num_list_size = tokenizer->num_list_size;    //

    KeyCode token_encoding = kNOP; // init
    uint64_t token_data = 0xBADBABA; 
    wchar_t* wrong_character = nullptr;
    while (str_list != tokenizer->str_list) 
    {
        if (iswdigit(*GET_NODE_DATA(str_list)))
        {
            token_data = wcstoull(GET_NODE_DATA(str_list), &wrong_character, 10);
            token_encoding = kNumber;
        }
        else  
        {
            token_data = 0xBADBABA;
            token_encoding = SearchKeyWord(GET_NODE_DATA(str_list));
        }

        NumListAdd(num_list, token_data, token_encoding, num_list_size);
        num_list_size++;
    }   

    tokenizer->num_list_size = num_list_size;   // return struct
}


KeyCode SearchKeyWord(const wchar_t* lexem)
{   
    for (int i = 0; i < keywords_amount; i++)
    {       
        if (!wcsncmp(lexem, keyword_table[i].key_word, keyword_table[i].key_word_len))
        {
            return keyword_table[i].key_code;
        }
        else 
        {
            // добавить имя, не найденное в таблице ключ. слов в таблицу имён, присвоить номер 

        }
        
        //TODO: здесь больше условий. Например несколько лексем это один токен 
    }

    return kError;  // not found
}


void MakeNameTable()
{
    FileInfo file_info = {};

    OpenFile(&file_info, "../../name_table.txt");

        
    
}


void AddToNameTable()
{

}

