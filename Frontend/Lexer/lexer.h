#include <sys/stat.h>
#include <stdlib.h>
#include <wchar.h>

#include "../../Utilities/utilities.h"
#include "../../StringList/list.h"

#ifndef ENUMS_FRONTEND_HEADER
#define ENUMS_FRONTEND_HEADER

typedef struct 
{   
    FileInfo file;

    wchar_t* pos;        // position in array
    size_t line;      // y position  // just for debug
    size_t colomn;    // x position  // just for debug

    StrList* list;
    size_t list_size;
} Lexer;

//-----------------------------------------------
StrList* LexicalAnalysis(const char* filename);

void InitLexer(Lexer* lexer, const char* filename);
void CloseLexer(Lexer* lexer, const char* filename);

void MakeAnalysis(Lexer* lexer);
void ReadLexem(wchar_t* code, StrList* list, size_t* list_size);

#endif 

