#include <stdio.h>
#include <stdlib.h>

#ifndef STACK_HEADER
#define STACK_HEADER

static const int kStackStartSize = 10;

typedef enum
{
    kGoodStack,
    kBadStack,
    kStackOverflow
} StackInfo;

typedef union
{   
    int int_t;
    double double_t;
    void* pointer_t;
} StackElem;

typedef struct
{
    StackElem* data;
    int size;
    int capacity;
} Stack_t;

StackInfo StackCtor(Stack_t* stack);
StackInfo StackDtor(Stack_t* stack);
StackInfo StackPush(Stack_t* stack, StackElem elem);
StackElem StackPop(Stack_t* stack);

#endif
