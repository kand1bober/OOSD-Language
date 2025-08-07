#include "lexer.h"
#include "parser.h"
#include "../Tree/tree_dump.h"

int MakeFrontend(Parser* parser, Lexer* lexer)
{
    LexicalAnalysis(lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    GetSyntaxTree(parser, lexer);
    
    TreeDotOutput(parser->tree);
    
    TreeTextDump(parser->tree);
        
    return 0;
}


void CloseFrontend(Parser* parser, Lexer* lexer)
{
    CloseLexer(lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    TreeDtor(parser->tree);
}
