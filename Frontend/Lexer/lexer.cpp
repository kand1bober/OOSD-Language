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

    ListDot(lexer.list);

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
    StrListDtor(lexer->list);

    CloseFile(&lexer->file);
}
//-----------------------------------------------


//-----------------------------------------------
void MakeAnalysis(Lexer* lexer)
{
    Lexem* lexem_arr = nullptr;
    SplitLexems(lexer, lexem_arr);



    free(lexem_arr);
}             


void SplitLexems(Lexer* lexer, Lexem* lexem_arr)
{   
    wchar_t* code = lexer->pos;
    char* char_code = (char*)code;

    size_t spaces_num = 0;

    wprintf(L"%ls\n", code + 1);
    // for (size_t i = 0; i < lexer->file.size; i++)
    // {
    //     char_code = (char*)code;
    //     if (iswspace(*code))
    //     {   
    //         *code = '\0';
    //     }
    //     else if (iswspace(*(wchar_t*)(char_code + 2)))
    //     {
    //         *(wchar_t*)(char_code + 2) = '\0';
    //     }

    //     code++;
    // }

    // lexem_arr = (Lexem*)calloc(spaces_num, sizeof(Lexem));

    // code = lexer->pos;
    // for (size_t i = 0; i < spaces_num; i++)
    // {   
    //     wcscpy();
    // }
}
 
//-----------------------------------------------

