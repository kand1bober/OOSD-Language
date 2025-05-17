#include <wchar.h>
#include <ctype.h>
#include <wctype.h>

#include "../../NumberList/list.h"
#include "../../StringList/list.h"
#include "../../StringList/list_dump.h"
#include "../keywords.h"
#include "../../Utilities/utilities.h"

#ifndef TOKENIZER_HEADER
#define TOKENIZER_HEADER


typedef struct
{       
    wchar_t* str;      // string
    int len;        // length 
    KeyCode type;   // enum of operation
} Token;

typedef struct 
{   
    NumList* num_list;
    size_t num_list_size;

    StrList* str_list;
    size_t str_list_size;

    StrList* id_table;
    size_t id_table_size;
} Tokenizer;    

void Tokenization(Tokenizer* tokenizer);

void CloseTokenizer(Tokenizer* tokenizer);

KeyCode SearchKeyWord(const wchar_t* str, int str_len);

void AddId(const wchar_t* str);

#endif
