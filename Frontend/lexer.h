#include <sys/stat.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>

#include "../Utilities/utilities.h"
#include "../StringList/list.h"
#include "../StringList/list_dump.h"
#include "../NumberList/list.h"
#include "../NumberList/list_dump.h"
#include "../Common/keywords.h"


#ifndef ENUMS_FRONTEND_HEADER
#define ENUMS_FRONTEND_HEADER

//-----------------------------------------------

typedef struct
{       
    wchar_t* str;   // string
    int len;        // length 
    KeyCode type;   // enum of operation
} Lexem;

typedef struct 
{   
    FileInfo file;

    wchar_t* pos;     // position in array
    size_t line;      // y position  // just for debug
    size_t colomn;    // x position  // just for debug

    //-------------------------------------------

    NumList* num_list;      // codes of keywords and "kId" code for id's
    size_t num_list_size;

    StrList* str_list;      // original words
    size_t str_list_size;

    StrList* id_table;      // id's, took out from original text 
    size_t id_table_size;
} Lexer;    

//-----------------------------------------------

void LexicalAnalysis(Lexer* lexer, const char* filename);

void InitLexer(Lexer* lexer, const char* filename);

void CloseLexer(Lexer* lexer, const char* filename);

void SplitLexems(Lexer* lexer);

//-----------------------------------------------

void Tokenization(Lexer* tokenizer);

KeyCode SearchKeyWord(const wchar_t* str, int str_len);

bool IsNum(const wchar_t* token, int token_len);

//-----------------------------------------------

#endif 

