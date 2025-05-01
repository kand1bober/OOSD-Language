#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <wchar.h>

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
        double data;      
    } NumList;

    //-------------------------------------------
    NumList* NumListCreateNode (const double data);

    NumList* NumListCtor();

    NumListInfo_t NumListDtor (NumList* list);

    NumList* NumListGetNode (NumList* list, int number);

    NumListInfo_t NumListAdd (NumList* list, const double data, size_t number);

    NumListInfo_t NumListDelete (NumList* list, int number);

    int NumListFindNode (NumList* list, const double data);
    //-------------------------------------------

#endif

