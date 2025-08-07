#include "../Frontend/lexer.h"
#include "../Frontend/parser.h"

#ifndef SPU_BACK_MAIN_HEADER
#define SPU_BACK_MAIN_HEADER

int MakeBackend(Parser* parser);
void CloseBackend();

#endif
