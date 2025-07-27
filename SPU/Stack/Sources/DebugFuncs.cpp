#include "../Headers/configuration.h"
#include "../Headers/decoration.h"

#include "../Headers/functions.h"
#include "../Headers/macros.h"
#include "../Headers/library.h"

#ifdef DEBUG_STACK_FUNCS

    bool StackValidity(struct Stack_t* stk, const char* file, const char* func, const int line)
    {
        bool status = 0;
        PRINT_DEBUG( printf(YELLOW "status: %d, stk->error: " DELETE_COLOR, status);
            BinaryOutput(stk->error);
            printf("\n"); )

        stk->error &= 0;

        if ( stk == NULL )
        {
            PRINT_DEBUG( printf(RED "uslovie 0\n" DELETE_COLOR); )
            stk->error |= ( 1 << STACK_NULLPTR );
            status = 1;
        }
        if (stk->data == NULL)
        {
            PRINT_DEBUG( printf(RED "uslovie 1\n" DELETE_COLOR); )
            stk->error |= ( 1 << DATA_NULL );
            status = 1;
        }
        if ( stk->size < 0 )
        {
            PRINT_DEBUG( printf(RED "uslovie 2\n" DELETE_COLOR); )
            stk->error |= ( 1 << STACK_UNDERFLOW );
            status = 1;
        }
        if ( stk->size > stk->capacity )
        {
            PRINT_DEBUG( printf(RED "uslovie 3\n" DELETE_COLOR); )
            stk->error |= ( 1 << STACK_OVERFLOW )   ;
            status = 1;
        }
        if ( *(Canary_t*)( (char*)stk->data - sizeof(Canary_t) ) != LEFT_CANAREYKA )
        {
            PRINT_DEBUG( printf(RED "uslovie 4\n" DELETE_COLOR); )
            stk->error |= ( 1 << LEFT_CANARY );
            status = 1;
        }
        if ( *(Canary_t*)( (char*)stk->data + (size_t)stk->capacity * sizeof(StackElem) + stk->capacity_gap ) != RIGHT_CANAREYKA )
        {
            PRINT_DEBUG( printf(RED "uslovie 5\n"); )
            stk->error |= ( 1 << RIGHT_CANARY );
            status = 1;
        }
        // if ( stk->hash_1 != stk->hash_2 )
        // {
        //     PRINT_DEBUG( printf(RED "uslovie 6" DELETE_COLOR); )
        //     stk->error |= ( 1 << HASH_SUM );
        //     status = 1;
        // }

        return status;
    }


    void StackDump(struct Stack_t* stk, const char* file, const char* func, const int line)
    {
        printf("stack called from %s in file: %s, line: %d\n"
        "pointer to stack: %p\n"
        "stack:\n"
        "{\n"
        "    StackElem* data: %p\n"
        "    int size: %d\n"
        "    int capacity: %d\n"
        "    ON_DEBUG(int error): ", func, file, line, stk, stk->data, stk->size, stk->capacity);
        BinaryOutput(stk->error);
        printf("\n                                        ........|||||||||\n"
        "                                                " WHITE "8" BLACK "7" WHITE "6" PURPLE "5" SINIY "4" BLUE "3" GREEN "2" YELLOW "1" RED "0" DELETE_COLOR "\n"
        RED "0 -- pointer to stack is NULL\n"
        YELLOW "1 -- invalid pointer to array\n"
        GREEN "2 -- underflow\n"
        BLUE "3 -- overflow\n"
        SINIY "4 -- problem with left canareyka\n"
        PURPLE "5 -- problem with right canareyka\n"
        WHITE "6 -- hash sum changed\n" DELETE_COLOR
        "7 -- nothing for now\n"
        "}\n\n"
        YELLOW "Left Canareyka from constant: %X, " PURPLE "Left Canareyka from stack: %lX\n"
        YELLOW "Rigth Canareyka from constant: %X, " PURPLE "Right Canareyka from stack: %lX\n\n" DELETE_COLOR
        "Values of data:\n", LEFT_CANAREYKA, *(Canary_t*)( (char*)stk->data - sizeof(Canary_t) ), RIGHT_CANAREYKA, *(Canary_t*)( (char*)stk->data + (size_t)stk->capacity * sizeof(StackElem) + stk->capacity_gap /*- sizeof(Canary_t) */) );

        for (int i = 0; i < stk->size; i++)
        {
            StackElem output = *(stk->data + i );
            // if(output == POISON)
            //     printf(RED "*[%d] = %d\n" DELETE_COLOR, i, output );
            // else
                printf("*[%d] = %lf\n", i, output );
        }
        printf("\n");
    }


void BinaryOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf("%X", (unsigned)((number & (1 << i)) >> i) );
    }
}


// }

#endif


// int HashSUm()
// {
//
// }


// size_t GetCanarySize()
// {
//     #ifdef DEBUG_STACK_FUNCS
//         return sizeof(Canary_t);
//     #endif
//
//     return 0;

// int InputValidity(StackElem elem, const char* file, const char* func, const int line)
// {
//
//     if()
//         return 0;
// }



