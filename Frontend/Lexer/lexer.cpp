#include "lexer.h"
#include "../../Tree/tree.h"
#include "../../Utilities/utilities.h"
#include "configuration.h"


//-----------------------------------------------
StrList* LexicalAnalysis(const char* filename)
{
    Lexer lexer = {};

    InitLexer(&lexer, filename);

    MakeAnalysis(&lexer);

    CloseLexer(&lexer, filename);

    return lexer.list;
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
    StrList* list = lexer->list;            // 
    size_t list_size = lexer->list_size;    //

    while (code != code + lexer->file.size)
    {
        SkipSpaces(code);

        ReadLexem(code, list, &list_size);
    }

    lexer->pos = code;
    lexer->list_size = list_size;
}             


void ReadLexem(wchar_t* code, StrList* list, size_t* list_size)
{
    wchar_t lexem[256] = {0};
    wchar_t* lexem_ptr = lexem;

    while (*code != ' ' || *code != '\t' || *code != '\n' )
    {   
        *lexem_ptr = *code;

        code++;
        lexem_ptr++;
    }

    StrListAdd(list, lexem, *list_size);
    list_size++;
}
//-----------------------------------------------
