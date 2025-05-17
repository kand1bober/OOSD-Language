#include "lexer.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"
// #include "configuration.h"


//-----------------------------------------------
void LexicalAnalysis(Lexer* lexer, const char* filename)
{
    InitLexer(lexer, filename);

    MakeAnalysis(lexer);

    ListDot(lexer->list);

    // CloseLexer(&lexer, filename);
}
//-----------------------------------------------


//-----------------------------------------------
void InitLexer(Lexer* lexer, const char* filename)
{
    OpenFile(&lexer->file, filename);
 
    lexer->list = StrListCtor();
    lexer->list_size = 0;

    lexer->colomn = 0;
    lexer->line = 0;
    lexer->pos = lexer->file.code;
}


void CloseLexer(Lexer* lexer, const char* filename) 
{
    StrListDtor(lexer->list);

    CloseFile(&lexer->file);
}
//-----------------------------------------------


//-----------------------------------------------
void MakeAnalysis(Lexer* lexer)
{
    SplitLexems(lexer);
}             


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
        StrListAdd(lexer->list, lexem_arr[i].str, lexer->list_size);
        lexer->list_size++;
    }   

    free(lexem_arr);
}
//-----------------------------------------------

