#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

#include "../Common/keywords.h"


#ifndef NUMBER_LIST_FUNC_HEADER
#define NUMBER_LIST_FUNC_HEADER

    const int64_t NUM_LIST_POISON = 0xBADBABA;

    typedef enum NumListInfo
    {
        kGoodNumList = 54,
        kBadNumList = 55,
    }NumListInfo_t;

    typedef union
    {   
        void* ptr;
        int64_t number;
    } NumListData;

    typedef enum 
    {
        kPtrData = 1,   // for identifiers 
        kNumData,   // for keywords
        kConstData, // for numeric constants 
    } DataTypes;

    typedef struct num_list
    {
        struct num_list* next; 
        struct num_list* prev;
               
        DataTypes data_type;                   
        NumListData data;
    } NumList;

    //-------------------------------------------
    NumList* NumListCreateNumNode (DataTypes type, const int64_t data);
    NumList* NumListCreatePtrNode (DataTypes type, void* data);

    NumList* NumListCtor();

    NumListInfo_t NumListDtor (NumList* list);

    NumList* NumListGetNode (NumList* list, int number);

    NumListInfo_t NumListAdd (NumList* list, DataTypes data_type, NumListData data, size_t number);

    NumListInfo_t NumListDelete (NumList* list, int number);

    int NumListSearchNode(NumList* list, int64_t to_search);
    //-------------------------------------------

#endif

