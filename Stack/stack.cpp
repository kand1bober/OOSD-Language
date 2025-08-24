#include "stack.h"

#define AlLOC_ASSERT    if (!stack) \
                        { \
                            printf("Error in allocating stack\n"); \
                            exit(1); \
                        }

#define FREE_ASSERT     if (!stack) \
                        { \
                            printf("Error in allocating stack\n"); \
                            exit(1); \
                        }

Stack_t* StackCtor()
{
    Stack_t* stack = (Stack_t*)malloc(sizeof(StackElem));
    stack->size = 0;

    AlLOC_ASSERT 

    return stack;
}


StackInfo StackDtor(Stack_t* stack)
{
    free(stack);

    if (!stack)
        return kGoodStack;
    else  
    {
        FREE_ASSERT;
        return kBadStack;
    }
}


StackInfo StackPush(Stack_t* stack, StackElem elem)
{
    stack = (Stack_t*)realloc(stack, sizeof(StackElem) * stack->size + 1);

    AlLOC_ASSERT

    *(stack->data + stack->size * sizeof(StackElem)) = elem;
    stack->size++;

    return kGoodStack;
}


StackElem StackPop(Stack_t* stack)
{
    StackElem elem = {};

    stack->size--;

    elem = *(stack->data + stack->size * sizeof(StackElem));

    stack = (Stack_t*)realloc(stack, sizeof(StackElem) * stack->size);

    return elem;
}

#undef AlLOC_ASSERT
#undef FREE_ASSERT
