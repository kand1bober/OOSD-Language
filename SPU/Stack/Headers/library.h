#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "macros.h"
#include "configuration.h"

#ifndef SHIT_HEADER

#define SHIT_HEADER

const int START_CAPACITY = 5;

typedef double StackElem;
typedef uint64_t Canary_t; // 8 bytes
const unsigned char POISON = 0;

#ifdef DEBUG_STACK_FUNCS
    const uint32_t LEFT_CANAREYKA = 0xBADDED; // =12246509
    const uint32_t RIGHT_CANAREYKA = 0xBADF00D; // =195948557

    enum StackError
    {
        STACK_NULLPTR = 0,
        DATA_NULL = 1,
        STACK_UNDERFLOW = 2,
        STACK_OVERFLOW = 3,
        LEFT_CANARY = 4,
        RIGHT_CANARY = 5,
        HASH_SUM = 6,
    };
#endif

struct Stack_t
    {
        Canary_t first_canary = 0xCAFEBABE; // =3405691582

        StackElem* data;
        int size;
        int capacity;

        ON_DEBUG(uint64_t hash_1;)
        ON_DEBUG(uint64_t hash_2;)
        ON_DEBUG(int error;)
        ON_DEBUG(int capacity_gap);

        Canary_t second_canary = 0xDEADFA11; // =3735943697
    };

#endif
