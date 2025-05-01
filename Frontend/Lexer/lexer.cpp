#include "lexer.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"
#include "configuration.h"


//-----------------------------------------------
void LexicalAnalysis(char* filename)
{
    Lexer lexer = {};

    InitLexer(&lexer, filename);

    MakeAnalysis(&lexer);

    CloseLexer(&lexer, filename);
}
//-----------------------------------------------


//-----------------------------------------------
void InitLexer(Lexer* lexer, char* filename)
{
    OpenFile(&lexer->file, filename);
 
    lexer->list = ListCtor();
    lexer->list_size = 0;

    lexer->colomn = 0;
    lexer->line = 0;
    lexer->pos = lexer->file.code;
}


void CloseLexer(Lexer* lexer, char* filename)
{
    /*
    * leaving functions ...
    *
    */

    CloseFile(&lexer->file);
}
//-----------------------------------------------


//-----------------------------------------------
void MakeAnalysis(Lexer* lexer)
{
    wchar_t symbol = 0;

    wchar_t* code = lexer->pos;             // 
    List* list = lexer->list;               // 
    size_t list_size = lexer->list_size;    //

    while (code != code + lexer->file.size)
    {
        SkipSpaces(code);

        ReadLexem(code, list, &list_size);
    }

    lexer->pos = code;
    lexer->list_size = list_size;
}             


void ReadLexem(wchar_t* code, List* list, size_t* list_size)
{
    wchar_t lexem[256] = {0};
    wchar_t* lexem_ptr = lexem;

    while (*code != ' ' || *code != '\t' || *code != '\n' )
    {   
        *lexem_ptr = *code;

        code++;
        lexem_ptr++;
    }

    ListAdd(list, lexem, *list_size);
    list_size++;
}
//-----------------------------------------------


// void ReadToken(Lexer* lexer, Token* token)
// {
//     SkipSpaces(lexer->pos);

//     wchar_t head_symbol = 0;
//     switch (head_symbol)
//     {
    
//     }

//     SkipSpaces(lexer->pos);
// }

// wchar_t symbol = L'а';


