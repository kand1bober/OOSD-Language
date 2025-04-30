#include <sys/stat.h>
#include "stdlib.h"

#include "../../Utilities/utilities.h"
#include "../../List/list.h"

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
} KeyWords;

// 11	if	        Условный оператор
// 12	while	    Оператор цикла
// 13	=	        Оператор присваивания
// 21	sin	        Синус
// 22	cos	        Косинус
// 23	floor	    Округление вниз
// 24	+	        Сложение
// 25	-	        Вычитание
// 26	*	        Умножение
// 27	/	        Деление
// 28	diff	    Оператор дифференцирования
// 29	sqrt	    Квадратный корень
// 31	==	        Равенство
// 32	<	        Меньше
// 33	>	        Больше
// 34	<=	        Меньше или равно
// 35	>=	        Больше или равно
// 36	!=	        Не равно
// 37	&&	        Логическое И
// 38	||	        Логическое ИЛИ
// 39	!	        Отрицание
// 41	;	        Оператор последовательного исполнения
// 42	,	        Оператор перечисления
// 51	number	    Число с плавающей точкой
// 61	in	        Оператор ввода
// 62	out	        Оператор вывода
// 71	return	    Оператор возврата
// 72	break	    Оператор выхода из цикла
// 73	continue	Оператор перехода на следующую итерацию
// 74	abort

static const char* keywords[] = {"if", "while", "=", "sin", "cos", "floor", "+", "-", "*", "/", "diff", "sqrt",
                              "==", "<", ">", "<=", "!=", "&&", "||", "!", ";", ",", "number", 
                              "in", "out", "return", "break", "continue", "abort"}; //TODO: сделать кодогенерацию на любые ключевые слова 

typedef struct
{       
    char* str;      // string
    int len;        // length 
    KeyWords type;  // enum of operation
} Token;

typedef struct 
{   
    FileInfo file;

    size_t pos;       // position in array
    size_t line;      // y position
    size_t colomn;    // x position

    List* list;
    size_t list_size;
} Lexer;

//-----------------------------------------------
void LexicalAnalysis(char* filename);

void InitLexer(Lexer* lexer, char* filename);
void CloseLexer(Lexer* lexer, char* filename);

void MakeAnalysis(Lexer* lexer);

#endif 

