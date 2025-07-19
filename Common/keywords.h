#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifndef KEY_WORDS_GENERATOR
#define KEY_WORDS_GENERATOR

typedef enum 
{ 
    // default/initial
    kError = -3,        // Initial value
    kConst = -2,        // numeric constant
    kId = -1,           // identifier

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
    kAdd,               // +
    kSub,               // -
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

    const wchar_t* C_key_word;

    KeyCode key_code;

    size_t key_word_len;

    const wchar_t* html_entity;
} KeyWord;


static const KeyWord keyword_table[] = 
{
    #define DEF_KEYWORD(key_word, C_key_word, key_code, html_entity) {key_word, C_key_word, key_code, wcslen(key_word), html_entity}

    DEF_KEYWORD(L"нахуй",            L"nop",      kNOP,                 L""),
    DEF_KEYWORD(L"блять",            L"nop",      kNOP,                 L""),
    DEF_KEYWORD(L"кунимэн",          L"(",        kLeftBracket,         L"&#x28;"),
    DEF_KEYWORD(L"кишкоблуд",        L")",        kRightBracket,        L"&#x29;"),
    DEF_KEYWORD(L"забаристый",       L"{",        kLeftCurlyBracket,    L"&#x7B;"),
    DEF_KEYWORD(L"с-горемыкой",      L"}",        kRightCurlyBracket,   L"&#x7D;"),
    DEF_KEYWORD(L"если",             L"if",       kIf,                  L""),
    DEF_KEYWORD(L"пока",             L"while",    kWhile,               L""),
    DEF_KEYWORD(L"равно",            L"=",        kEqual,               L"&#x3D;"),
    DEF_KEYWORD(L"синус",            L"sin",      kSin,                 L""),
    DEF_KEYWORD(L"косинус",          L"cos",      kCos,                 L""),
    DEF_KEYWORD(L"опустить",         L"floor",    kFloor,               L""),
    DEF_KEYWORD(L"плюс",             L"+",        kAdd,                 L"&#x2B;"),
    DEF_KEYWORD(L"минус",            L"-",        kSub,                 L"&#x2D;"),
    DEF_KEYWORD(L"умножить",         L"*",        kMul,                 L"&#x2A;"),
    DEF_KEYWORD(L"поделить",         L"/",        kDiv,                 L"&#x2F;"),
    DEF_KEYWORD(L"производная",      L"diff",     kDiff,                L""),
    DEF_KEYWORD(L"корень",           L"sqrt",     kSqrt,                L""),
    DEF_KEYWORD(L"степень",          L"^",        kPow,                 L"&#x5E;"),
    DEF_KEYWORD(L"равно?",           L"==",       kEcmp,                L"&#x3D;&#x3D;"),
    DEF_KEYWORD(L"под",              L"<",        kBcmp,                L"&#x3C;"),
    DEF_KEYWORD(L"над",              L">",        kAcmp,                L"&#x3E;"),
    DEF_KEYWORD(L"сприподнизу",      L"<=",       kBEcmp,               L"&#x3C;&#x3D;"),
    DEF_KEYWORD(L"сприподверху",     L">=",       kAEcmp,               L"&#x3E;&#x3D;"),
    DEF_KEYWORD(L"не-равно?",        L"!=",       kNEcmp,               L"&#x21;&#x3D;"),
    DEF_KEYWORD(L"и",                L"&&",       kAND,                 L"&#x26;&#x26;"),
    DEF_KEYWORD(L"или",              L"||",       kOR,                  L"&#x7C;&#x7C;"),
    DEF_KEYWORD(L"не",               L"!",        kNOT,                 L"&#x21;"),
    DEF_KEYWORD(L"конец",            L";",        kStep,                L"&#x3B;"),
    DEF_KEYWORD(L"к-тому-же",        L",",        kEnum,                L"&#x2C;"),
    DEF_KEYWORD(L"ячейка-из-говна",  L"int",      kNumber,              L""),
    DEF_KEYWORD(L"выслушать",        L"in",       kIn,                  L""),
    DEF_KEYWORD(L"спиздануть",       L"out",      kOut,                 L""),
    DEF_KEYWORD(L"на-базу",          L"return",   kRet,                 L""),
    DEF_KEYWORD(L"стоп",             L"break",    kBreak,               L""),
    DEF_KEYWORD(L"продолжить",       L"continue", kContinue,            L""),
    DEF_KEYWORD(L"аборт",            L"abort",    kAbort,               L""),

    #undef DEF_KEYWORD 
};

static const int kKeyWordsAmount = sizeof(keyword_table) / sizeof(KeyWord);

#endif 
