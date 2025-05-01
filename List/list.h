#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <wchar.h>

#ifndef LIST_FUNC_HEADER
#define LIST_FUNC_HEADER

    const wchar_t LIST_POISON[] = L"BADBABA";

    typedef enum ListInfo
    {
        kGoodList = 52,
        kBadList = 53,
    }ListInfo_t;

    typedef struct List
    {
        struct List* next; 
        struct List* prev;
        int str_len;      // without '\0'
    } List_t;

    #define GET_NODE_DATA(node_ptr) (wchar_t*)node_ptr + sizeof(List_t) // makes offset from struct beginning

    //-------------------------------------------
    List_t* ListCreateNode (const wchar_t* string);

    List_t* ListCtor();

    ListInfo_t ListDtor (List_t* list);

    List_t* ListGetNode (List_t* list, int number);

    ListInfo_t ListAdd (List_t* list, const wchar_t* string, size_t number);

    ListInfo_t ListDelete (List_t* list, int number);

    int ListFindNode (List_t* list, const wchar_t* string);
    //-------------------------------------------

#endif
