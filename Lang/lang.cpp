#include "lang.h"

int main()
{
    StrList* str_list = nullptr;

    LexicalAnalysis("../input.txt");

    Tokenizer tokenizer = {}; 
    tokenizer.str_list = str_list;
    tokenizer.num_list = nullptr;

    MakeTokenization(&tokenizer);
    
    return 0;
}



