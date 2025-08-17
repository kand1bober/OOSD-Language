#include "Frontend/main.h"
#include "Frontend/parser.h"
#include "BackendASM/main.h"

int main()
{
    Parser parser = {};
    Lexer lexer = {};

    MakeFrontend(&parser, &lexer);

    MakeBackend(&parser);

    //closing functions are responsible to close only one's they opened
    CloseFrontend(&parser, &lexer);

    CloseBackend();

    return 0;
}
