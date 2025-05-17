#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifndef KEY_WORDS_GENERATOR
#define KEY_WORDS_GENERATOR

typedef enum 
{ 
    // default/initial
    kId = -1,           // identificator

    // brackets
    kNOP = 0,           // Not an operation
    kLeftBracket,       // (
    kRightBracket,      // )
    kLeftCurlyBracket,  // {
    kRightCurlyBracket, // }

    // conditions
    kIf = 11,           // if    
    kWhile = 12,        // while   
    kEqual = 13,        // "="  

    // ariphmetic
    kSin = 21,          // sin
    kCos,               // cos
    kFloor,             // floor 
    kPlus,              // +
    kMinus,             // -
    kMul,               // *
    kDiv,               // / 
    kDiff,              // diff 
    kSqrt,              // sqrt
    kPow,               // ^

    // logic
    kEcmp = 31,         // "=="
    kBcmp,              // "<"
    kAcmp,              // ">"
    kBEcmp,             // "<="
    kAEcmp,             // ">="
    kNEcmp,             // "!="
    kAND,               // "&&"
    kOR,                // "||"
    kNOT,               // "!"

    // punctuation
    kStep = 41,         // consistent execution ";"
    kEnum,              // enumeration ","

    //input/output/var type
    kNumber = 51,       // float number ( var declaration ) 
    kIn = 61,           // input
    kOut,               // output

    // execution management 
    kRet = 71,          // ret
    kBreak,             // break
    kContinue,          // continue
    kAbort,             // abort
} KeyCode;

typedef struct 
{
    const wchar_t* key_word;

    const char* C_key_word;

    KeyCode key_code;

    size_t key_word_len;
} KeyWord;


static const KeyWord keyword_table[] = 
{
    #define DEF_KEYWORD(key_word, C_key_word, key_code) {key_word, C_key_word, key_code, wcslen(key_word)}

    DEF_KEYWORD(L"нахуй",            "nop",      kNOP),
    DEF_KEYWORD(L"блять",            "nop",      kNOP),
    DEF_KEYWORD(L"кунимэн",          "(",        kLeftBracket),
    DEF_KEYWORD(L"кишкоблуд",        ")",        kRightBracket),
    DEF_KEYWORD(L"забаристый",       "{",        kLeftCurlyBracket),
    DEF_KEYWORD(L"с-горемыкой",      "}",        kRightCurlyBracket),
    DEF_KEYWORD(L"если",             "if",       kIf),
    DEF_KEYWORD(L"пока",             "while",    kWhile),
    DEF_KEYWORD(L"равно",            "=",        kEqual),
    DEF_KEYWORD(L"синус",            "sin",      kSin),
    DEF_KEYWORD(L"косинус",          "cos",      kCos),
    DEF_KEYWORD(L"опустить",         "floor",    kFloor),
    DEF_KEYWORD(L"собрать",          "+",        kPlus),
    DEF_KEYWORD(L"вынуть",           "-",        kMinus),
    DEF_KEYWORD(L"умножить",         "*",        kMul),
    DEF_KEYWORD(L"поделить",         "/",        kDiv),
    DEF_KEYWORD(L"производная",      "diff",     kDiff),
    DEF_KEYWORD(L"корень",           "sqrt",     kSqrt),
    DEF_KEYWORD(L"степень",          "^",        kPow),
    DEF_KEYWORD(L"натурал?",         "==",       kEcmp),
    DEF_KEYWORD(L"под",              "<",        kBcmp),
    DEF_KEYWORD(L"над",              ">",        kAcmp),
    DEF_KEYWORD(L"сприподнизу",      "<=",       kBEcmp),
    DEF_KEYWORD(L"сприподверху",     ">=",       kAEcmp),
    DEF_KEYWORD(L"не-равно",         "!=",       kNEcmp),
    DEF_KEYWORD(L"и",                "&&",       kAND),
    DEF_KEYWORD(L"или",              "||",       kOR),
    DEF_KEYWORD(L"не",               "!",        kNOT),
    DEF_KEYWORD(L"конец",            ";",        kStep),
    DEF_KEYWORD(L"да",               ",",        kEnum),
    DEF_KEYWORD(L"ячейка-из-говна",  "number",   kNumber),
    DEF_KEYWORD(L"выслушать",        "in",       kIn),
    DEF_KEYWORD(L"высрать-в-чат",    "out",      kOut),
    DEF_KEYWORD(L"на-базу",          "return",      kRet),
    DEF_KEYWORD(L"стоп",             "break",    kBreak),
    DEF_KEYWORD(L"продолжить",       "continue", kContinue),
    DEF_KEYWORD(L"аборт",            "abort",    kAbort),

    #undef DEF_KEYWORD 
};

static const int kKeyWordsAmount = sizeof(keyword_table) / sizeof(KeyWord);

#endif 
