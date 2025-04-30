#ifndef ENUMS_FRONTEND_HEADER
#define ENUMS_FRONTEND_HEADER

typedef enum 
{ 
    kIf = 11,       // if    
    kWhile = 12,    // while   
    kEqual = 13,    // "="  
 
    kSin = 21,
    kCos,
    kFloor,
    kPlus,
    kMinus,
    kMul,
    kDiv,
    kDiff,
    kSqrt,

    kEcmp = 31,     // "=="
    kBcmp,          // "<"
    kAcmp,          // ">"
    kBEcmp,         // "<="
    kAEcmp,         // ">="
    kNEcmp,         // "!="
    kAND,           // "&&"
    kOR,            // "||"
    kNOT,           // "!"
 
    kStep = 41,     // consistent execution ";"
    kEnum,          // enumeration ","

    kNumber = 51,   // float number

    kIn = 61,       // input
    kOut,           // output

    kRet = 71,      
    kBreak,         
    kContinue,
    kAbort,

} KeyWords_t;

void SyntaxError (const char* file, const char* func, const unsigned long int line); 

#endif 
