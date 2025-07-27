#include "configuration.h"

#include "library.h"
#include "macros.h"

#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

int STACK_CTOR(struct Stack_t* stk, unsigned int amount);
int STACK_DTOR(struct Stack_t* stk);
int STACK_PUSH(struct Stack_t* stk, StackElem elem);
StackElem STACK_POP(struct Stack_t* stk);
int STACK_RESIZE_UP(struct Stack_t* stk);
int STACK_RESIZE_DOWN(struct Stack_t* stk);

#ifdef DEBUG_STACK_FUNCS
    bool StackValidity(struct Stack_t* stk, const char* file, const char* func, const int line);
    void StackDump(struct Stack_t* stk, const char* file, const char* func, const int line);
    void BinaryOutput(int number);
#endif


#endif
