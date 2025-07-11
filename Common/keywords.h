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
} KeyWord;


static const KeyWord keyword_table[] = 
{
    #define DEF_KEYWORD(key_word, C_key_word, key_code) {key_word, C_key_word, key_code, wcslen(key_word)}

    DEF_KEYWORD(L"нахуй",            L"nop",      kNOP),
    DEF_KEYWORD(L"блять",            L"nop",      kNOP),
    DEF_KEYWORD(L"кунимэн",          L"(",        kLeftBracket),
    DEF_KEYWORD(L"кишкоблуд",        L")",        kRightBracket),
    DEF_KEYWORD(L"забаристый",       L"{",        kLeftCurlyBracket),
    DEF_KEYWORD(L"с-горемыкой",      L"}",        kRightCurlyBracket),
    DEF_KEYWORD(L"если",             L"if",       kIf),
    DEF_KEYWORD(L"пока",             L"while",    kWhile),
    DEF_KEYWORD(L"равно",            L"=",        kEqual),
    DEF_KEYWORD(L"синус",            L"sin",      kSin),
    DEF_KEYWORD(L"косинус",          L"cos",      kCos),
    DEF_KEYWORD(L"опустить",         L"floor",    kFloor),
    DEF_KEYWORD(L"плюс",             L"+",        kAdd),
    DEF_KEYWORD(L"минус",            L"-",        kSub),
    DEF_KEYWORD(L"умножить",         L"*",        kMul),
    DEF_KEYWORD(L"поделить",         L"/",        kDiv),
    DEF_KEYWORD(L"производная",      L"diff",     kDiff),
    DEF_KEYWORD(L"корень",           L"sqrt",     kSqrt),
    DEF_KEYWORD(L"степень",          L"^",        kPow),
    DEF_KEYWORD(L"равно?",           L"==",       kEcmp),
    DEF_KEYWORD(L"под",              L"<",        kBcmp),
    DEF_KEYWORD(L"над",              L">",        kAcmp),
    DEF_KEYWORD(L"сприподнизу",      L"<=",       kBEcmp),
    DEF_KEYWORD(L"сприподверху",     L">=",       kAEcmp),
    DEF_KEYWORD(L"не-равно?",        L"!=",       kNEcmp),
    DEF_KEYWORD(L"и",                L"&&",       kAND),
    DEF_KEYWORD(L"или",              L"||",       kOR),
    DEF_KEYWORD(L"не",               L"!",        kNOT),
    DEF_KEYWORD(L"конец",            L";",        kStep),
    DEF_KEYWORD(L"к-тому-же",        L",",        kEnum),
    DEF_KEYWORD(L"ячейка-из-говна",  L"number",   kNumber),
    DEF_KEYWORD(L"выслушать",        L"in",       kIn),
    DEF_KEYWORD(L"спиздануть",       L"out",      kOut),
    DEF_KEYWORD(L"на-базу",          L"return",   kRet),
    DEF_KEYWORD(L"стоп",             L"break",    kBreak),
    DEF_KEYWORD(L"продолжить",       L"continue", kContinue),
    DEF_KEYWORD(L"аборт",            L"abort",    kAbort),

    #undef DEF_KEYWORD 
};

static const int kKeyWordsAmount = sizeof(keyword_table) / sizeof(KeyWord);

#endif 
