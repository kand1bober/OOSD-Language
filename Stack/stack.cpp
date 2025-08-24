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

StackInfo StackCtor(Stack_t* stack)
{
    stack->data = (StackElem*)malloc(sizeof(StackElem));
    stack->size = 0;

    AlLOC_ASSERT 

    return kGoodStack;
}


StackInfo StackDtor(Stack_t* stack)
{
    free(stack->data);

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
    stack->data = (StackElem*)realloc(stack->data, sizeof(StackElem) * (stack->size + 1));

    AlLOC_ASSERT

    *(stack->data + stack->size) = elem;
    stack->size++;

    return kGoodStack;
}


StackElem StackPop(Stack_t* stack)
{
    StackElem elem = {};

    stack->size--;

    elem = *(stack->data + stack->size);

    stack->data = (StackElem*)realloc(stack->data, sizeof(StackElem) * stack->size);

    return elem;
}

#undef AlLOC_ASSERT
#undef FREE_ASSERT
