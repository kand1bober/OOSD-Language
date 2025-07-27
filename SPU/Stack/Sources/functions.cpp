#include "../Headers/configuration.h"

#include "../Headers/functions.h"
#include "../Headers/macros.h"
#include "../Headers/library.h"

int STACK_CTOR(struct Stack_t* stk, unsigned int amount)
{
    //InputValidity

    size_t razmer = (( amount * sizeof(StackElem)))  ON_DEBUG(+ 2 * sizeof(Canary_t));

    size_t kolvo = razmer ON_DEBUG(+ 8 - razmer % 8 );
    PRINT_DEBUG( printf("kolvo in bytes: %lu\n", kolvo); )

    #ifdef DEBUG_STACK_FUNCS
        stk->capacity_gap = ( 8 - razmer % 8 );
    #endif

    (stk->data) = (StackElem*)( (char*)calloc(kolvo, sizeof(char)) ON_DEBUG(+ sizeof(Canary_t) ) );

    stk->size = 0;
    stk->capacity = (int)amount;

    PRINT_DEBUG( printf("Ctor: amount: %u, stk->data - sizeof(Cnary_t): %p, kolvo: %lu, stk->data + kolvo - sizeof(canary): %p \n", amount, (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ), kolvo, (char*)stk->data + kolvo ON_DEBUG(- sizeof(Canary_t) ) ); )

    #ifdef DEBUG_STACK_FUNCS
        *(Canary_t *)( (char*)stk->data - sizeof(Canary_t) ) = LEFT_CANAREYKA; //creating canareyka's
        *(Canary_t*)( (char*)stk->data + kolvo - 2 * sizeof(Canary_t) ) = RIGHT_CANAREYKA;
    #endif

    CHECK_VALIDITY(stk);

    return 0;
}


int STACK_DTOR(struct Stack_t* stk)
{
    CHECK_VALIDITY(stk);

    stk->size = 0;
    stk->capacity = 0;

    free ( (StackElem*)( (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ) ) );

    return 0;
}


int STACK_PUSH(struct Stack_t* stk, StackElem elem)
{
    CHECK_VALIDITY(stk);

    STACK_RESIZE_UP_CALL( stk );

    *( (stk->data) + (stk->size) ) = elem;
    (stk->size)++;

    CHECK_VALIDITY(stk);

    return 0;
}


StackElem STACK_POP(struct Stack_t* stk)
{
    CHECK_VALIDITY(stk);

    STACK_RESIZE_DOWN_CALL( stk );

    CHECK_VALIDITY(stk);

    if ( stk->size > 0 )
    {
        StackElem output = *( (stk->data ) + ((stk->size)--) - 1);

        return output;
    }
    else
    {
        printf("Cannot pop value, nothing in th stack");
        return -1;
    }
}

int STACK_RESIZE_UP(struct Stack_t* stk)
{
    CHECK_VALIDITY(stk);

    size_t razmer = (( stk->capacity * sizeof(StackElem)) * 2)  ON_DEBUG(+ 2 * sizeof(Canary_t));

    if ( stk->size >= ( stk->capacity - 1) )
    {
        size_t kolvo = ( razmer ON_DEBUG(+ 8 - razmer % 8 ) );

        #ifdef DEBUG_STACK_FUNCS
            stk->capacity_gap = ( 8 - razmer % 8 );
        #endif

        stk->data = (StackElem*)( (char*)realloc( (void*)( (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ) ), kolvo )  ON_DEBUG(+ sizeof(Canary_t) ) );

        PRINT_DEBUG( printf("Resize_up: 2 * stk->capacity: %d, (char*)stk->data - sizeof(Canary_t): %p, kolvo: %lu, stk->data + kolvo - sizeof(canary): %p \n", 2 * stk->capacity, (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ), kolvo, (char*)stk->data + kolvo ON_DEBUG(- sizeof(Canary_t) ) ); )


        // CHECK_VALIDITY(stk);

        if ( stk )
        {
            stk->capacity = stk->capacity * 2;

            #ifdef DEBUG_STACK_FUNCS
                *(Canary_t *)( (char*)stk->data - sizeof(Canary_t) ) = LEFT_CANAREYKA; //creating canareyka's
                *(Canary_t*)( (char*)stk->data + kolvo - 2 * sizeof(Canary_t) ) = RIGHT_CANAREYKA;

                CHECK_VALIDITY(stk);
            #endif

            CHECK_VALIDITY(stk);

            return 0;
        }
        else
            return 1;
    }
    else
        return 0;


    return -1;
}


int STACK_RESIZE_DOWN(struct Stack_t* stk)
{
    CHECK_VALIDITY(stk);

    size_t razmer = (( stk->capacity * sizeof(StackElem)) / 2)  ON_DEBUG(+ 2 * sizeof(Canary_t));

    if ( (stk->size <= (stk->capacity / 4))  && (stk->capacity > START_CAPACITY) )
    {
        size_t kolvo = ( razmer ON_DEBUG(+ 8 - razmer % 8 ) );

        #ifdef DEBUG_STACK_FUNCS
            stk->capacity_gap = ( 8 - razmer % 8 );
        #endif

        stk->data = (StackElem*)( (char*)realloc( (void*)( (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ) ), kolvo) ON_DEBUG(+ sizeof(Canary_t) ) );

        PRINT_DEBUG( printf("Resize_down: stk->capacity/2: %d, (char*)stk->data - sizeof(Canary_t): %p, kolvo: %lu, stk->data + kolvo - sizeof(canary): %p \n", stk->capacity / 2, (char*)stk->data ON_DEBUG(- sizeof(Canary_t) ), kolvo, (char*)stk->data + kolvo ON_DEBUG(- sizeof(Canary_t) ) ); )

        if ( stk )
        {
            stk->capacity = stk->capacity / 2;

            #ifdef DEBUG_STACK_FUNCS
                *(Canary_t *)( (char*)stk->data - sizeof(Canary_t) ) = LEFT_CANAREYKA; //creating canareyka's
                *(Canary_t*)( (char*)stk->data + kolvo - 2 * sizeof(Canary_t) ) = RIGHT_CANAREYKA;

                CHECK_VALIDITY(stk);
            #endif

            return 0;
        }
        else
            return 1;
    }
    else
        return 0;

    return -1;
}

