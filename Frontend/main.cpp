#include "lexer.h"
#include "parser.h"
#include "../Tree/tree_dump.h"

int main()
{
    Lexer lexer = {};
    Parser parser = {};

    LexicalAnalysis(&lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    GetSyntaxTree(&parser, &lexer);
    
    TreeDotOutput(parser.tree);

    CloseLexer(&lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    TreeTextDump(parser.tree);

    TreeDtor(parser.tree);
        
    return 0;
}
