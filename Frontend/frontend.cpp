#include "frontend.h"

int main()
{
    Lexer lexer = {};
    Tokenizer tokenizer = {};
    Parser parser = {};

    Frontend frontend = {};
    frontend.lexer = &lexer;
    frontend.tokenizer = &tokenizer;
    frontend.parser = &parser;

    LexicalAnalysis(frontend.lexer, "/home/vyacheslav/Language/Utilities/input.txt");

    tokenizer.str_list = lexer.list;
    tokenizer.str_list_size = lexer.list_size;
    Tokenization(frontend.tokenizer);

    SyntaxAnalysis(frontend.parser, frontend.tokenizer);

    CloseLexer(frontend.lexer, "/home/vyacheslav/Language/Utilities/input.txt");
    
    CloseTokenizer(frontend.tokenizer);
    
    // CloseParser(frontend.parser);
    
    return 0;
}
