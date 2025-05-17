#include "Tokenizer/tokenizer.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"

#ifndef FRONTEND_HEADER
#define FRONTEND_HEADER

typedef struct
{
    Lexer* lexer;
    Tokenizer* tokenizer;
    Parser* parser; 
} Frontend;

#endif 
