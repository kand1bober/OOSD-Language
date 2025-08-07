#include "lexer.h"
#include "parser.h"

#ifndef FRONTEND_CONFIGURATION_HEADER
#define FRONTEND_CONFIGURATION_HEADER

#ifdef DEBUG
    #define ON_DEBUG(expr) expr
#else 
    #define ON_DEBUG(expr) 
#endif

int MakeFrontend(Parser* parser, Lexer* lexer);
void CloseFrontend(Parser* parser, Lexer* lexer);

#endif
