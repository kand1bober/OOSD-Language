#include <sys/stat.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>

#include "../../Utilities/utilities.h"
#include "../../StringList/list.h"
#include "../../StringList/list_dump.h"

#ifndef ENUMS_FRONTEND_HEADER
#define ENUMS_FRONTEND_HEADER

typedef struct 
{   
    FileInfo file;

    wchar_t* pos;     // position in array
    size_t line;      // y position  // just for debug
    size_t colomn;    // x position  // just for debug

    StrList* list;
    size_t list_size;
} Lexer;

typedef struct 
{
    int len;
    wchar_t* str;
} Lexem;

//-----------------------------------------------
void LexicalAnalysis(Lexer* lexer, const char* filename);

void InitLexer(Lexer* lexer, const char* filename);
void CloseLexer(Lexer* lexer, const char* filename);

void MakeAnalysis(Lexer* lexer);
void SplitLexems(Lexer* lexer);

#endif 

