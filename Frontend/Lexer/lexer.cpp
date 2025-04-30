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
    lexer->pos = 0;
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
    
}             


void ReadToken(Token* token)
{

}
//-----------------------------------------------

