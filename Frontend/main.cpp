#include "lexer.h"
#include "parser.h"

int main()
{
    Lexer lexer = {};
    Parser parser = {};

    LexicalAnalysis(&lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    // StartParser(&parser, &lexer);

    CloseLexer(&lexer, "/home/vyacheslav/Language/Utilities/input.txt");
        
    return 0;
}
