#include "../Frontend/parser.h"
#include "spu_code_gen.h"

int main()
{
    extern Parser parser;       // from frontend main.cpp
    Tree* tree = parser.tree;   //

    GenSpuCode(tree);

    return 0;
}
