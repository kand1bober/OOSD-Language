#include "lexer.h"
#include "../Tree/tree.h"
#include "../Utilities/utilities.h"
// #include "configuration.h"


//-----------------------------------------------
void LexicalAnalysis(Lexer* lexer, const char* filename)
{
    //----------Lexems----------
    InitLexer(lexer, filename);

    SplitLexems(lexer);

    // StrListDot(lexer->str_list);

    //----------Tokens----------
    Tokenization(lexer);

    StrListDot(lexer->id_table);

    NumListDot(lexer->num_list);
}   
//-----------------------------------------------


//-----------------------------------------------
void InitLexer(Lexer* lexer, const char* filename)
{
    OpenFile(&lexer->file, filename);
 
    lexer->str_list = StrListCtor();
    lexer->str_list_size = 0;

    lexer->colomn = 0;
    lexer->line = 0;
    lexer->pos = lexer->file.code;
}


void CloseLexer(Lexer* lexer, const char* filename) 
{
    StrListDtor(lexer->str_list);

    CloseFile(&lexer->file);

    StrListDtor(lexer->id_table);

    NumListDtor(lexer->num_list);
}
//-----------------------------------------------


//-----------------------------------------------

/*
* splits lexems and fills  
* doubly linked list with all lexems
*/
void SplitLexems(Lexer* lexer)
{   
    wchar_t* code = lexer->pos;
    wchar_t* old_code = nullptr;

    size_t lexems_amount = 0;

    // change '\n' to '\0'
    for (size_t i = 0; i < lexer->file.size; i++)
    {
        if (iswspace(*code))
        {   
            old_code = code;
            code = OverwriteSpaces(code);
            i += code - old_code;

            lexems_amount++;
        }

        code++;
    }

    Lexem* lexem_arr = (Lexem*)calloc(lexems_amount, sizeof(Lexem));

    // make array of lexem structs   
    code = lexer->pos;
    size_t lexem_len = 0;
    for (size_t i = 0; i < lexems_amount; i++)
    {   
        code = SkipNulls(code);
        lexem_len = wcslen(code);

        // wprintf(L"lexem: %ls\n", code);

        lexem_arr[i].str = code;
        lexem_arr[i].len = lexem_len;

        code += lexem_len;
    }

    // place  lexems to list
    for (size_t i = 0; i < lexems_amount; i++)
    {
        StrListAdd(lexer->str_list, lexem_arr[i].str, lexer->str_list_size);
        lexer->str_list_size++;
    }   

    free(lexem_arr);
}

//-----------------------------------------------

void Tokenization(Lexer* lexer)
{
    StrList* str_list = lexer->str_list->next;

    lexer->num_list = NumListCtor();
    lexer->num_list_size = 0;

    lexer->id_table = StrListCtor();
    lexer->id_table_size = 0;

    KeyCode token_type = kId;
    while (str_list != lexer->str_list) 
    {
        token_type = SearchKeyWord(GET_NODE_DATA(str_list), str_list->str_len);
        if (token_type == kId)
        {       
            StrListAdd(lexer->id_table, GET_NODE_DATA(str_list), lexer->id_table_size);
            lexer->id_table_size++;

            NumListAdd(lexer->num_list, kPtrData, {.ptr = StrListGetNode(lexer->id_table, lexer->id_table_size)}, lexer->num_list_size);
            lexer->num_list_size++;
        }   
        else if (token_type == kConst)
        {
            wchar_t* end;
            int64_t constant = 0;
            constant = (int64_t)wcstol(GET_NODE_DATA(str_list), &end, 10);

            NumListAdd(lexer->num_list, kConstData, {.number = constant}, lexer->num_list_size);
            lexer->num_list_size++;
        }
        else 
        {
            NumListAdd(lexer->num_list, kNumData, {.number = token_type}, lexer->num_list_size);
            lexer->num_list_size++;
        }

        str_list = str_list->next;
    }   
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

    // keyword not found
    if (IsNum(str, str_len))
        return kConst; 
    else 
        return kId; 
}


bool IsNum(const wchar_t* token, int token_len)
{   
    for (int i = 0; i < token_len; i++)
    {
        if (!iswdigit(token[i]))
            return false;
    }

    return true;
}   