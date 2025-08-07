#include "../Frontend/parser.h"
#include "spu_code_gen.h"

int MakeBackend(Parser* parser)
{
    Tree* tree = parser->tree;   //

    GenSpuCode(tree, parser->id_table);

    return 0;
}


void CloseBackend()
{

}

