#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <filesystem>

#include <wchar.h>

#ifndef STRING_LIST_FUNC_HEADER
#define STRING_LIST_FUNC_HEADER

    const wchar_t STR_LIST_POISON[] = L"BADBABA";

    typedef enum ListInfo
    {
        kGoodStrList = 52,
        kBadStrList = 53,
    }StrListInfo_t;

    typedef struct str_list
    {
        struct str_list* next; 
        struct str_list* prev;
        int str_len;      // without '\0'
    } StrList;

    #define GET_NODE_DATA(node_ptr) (wchar_t*)((char*)(node_ptr) + sizeof(StrList)) // makes offset from struct beginning

    //-------------------------------------------
    StrList* StrListCreateNode (const wchar_t* string);

    StrList* StrListCtor();

    StrListInfo_t StrListDtor (StrList* list);

    StrList* StrListGetNode (StrList* list, int number);

    StrListInfo_t StrListAdd (StrList* list, const wchar_t* string, size_t number);

    StrListInfo_t StrListDelete (StrList* list, int number);

    int StrListFindNode (StrList* list, const wchar_t* string);
    //-------------------------------------------

#endif

