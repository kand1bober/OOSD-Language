#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

#include "../Frontend/keywords.h"


#ifndef NUMBER_LIST_FUNC_HEADER
#define NUMBER_LIST_FUNC_HEADER

    const uint64_t NUM_LIST_POISON = 0xBADBABA;

    typedef enum NumListInfo
    {
        kGoodNumList = 54,
        kBadNumList = 55,
    }NumListInfo_t;

    typedef struct num_list
    {
        struct num_list* next; 
        struct num_list* prev;
        KeyCode type;           // instruction 
        uint64_t data;          // number if node == kNumber(kConst in Tree)
    } NumList;

    //-------------------------------------------
    NumList* NumListCreateNode (const uint64_t data, const int type);

    NumList* NumListCtor();

    NumListInfo_t NumListDtor (NumList* list);

    NumList* NumListGetNode (NumList* list, int number);

    NumListInfo_t NumListAdd (NumList* list, uint64_t data, KeyCode type, size_t number);

    NumListInfo_t NumListDelete (NumList* list, int number);

    int NumListFindNode (NumList* list, const double data);
    //-------------------------------------------

#endif

