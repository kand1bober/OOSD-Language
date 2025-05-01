#include "list.h"

StrList* StrListCreateNode (const wchar_t* string)
{
    int str_len = wcslen(string); 
    StrList* new_node = (StrList* )malloc( sizeof(StrList) + (str_len + 1) * sizeof(wchar_t) );

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->str_len = str_len;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    wcsncpy(GET_NODE_DATA(new_node), string, str_len + 1);

    return new_node;
}


StrList* StrListCtor ()
{
    StrList* phantom = StrListCreateNode (STR_LIST_POISON);

    phantom->next = phantom;
    phantom->prev = phantom;

    return phantom;
}


StrListInfo_t StrListDtor (StrList* list) 
{
    StrList* curr_node = list;
    StrList* next_node = curr_node->next;

    while (curr_node->next != list)
    {
        free (curr_node);
        curr_node = next_node;
        next_node = next_node->next;
    }

    free (curr_node);

    return kGoodStrList;
}
 

StrList* StrListGetNode (StrList* list, int number)
{
    StrList* curr_node = list;

    for (int i = 0; i < number; i++)
    {
        curr_node = curr_node->next; 
    }

    return curr_node;
}


/*
* 1st arg -- list, where to add
*
* 2nd arg -- string to add 
*
* 3rd arg -- position in the list (if you want to add in the end, 3rd arg = size of list)
*/
StrListInfo_t StrListAdd (StrList* list, const wchar_t* string, size_t number)
{
    StrList* new_node = StrListCreateNode (string);

    StrList* tmp_node = StrListGetNode (list, number);

    new_node->prev = tmp_node;
    new_node->next = tmp_node->next;
    
    tmp_node->next->prev = new_node;
    tmp_node->next = new_node;

    return kGoodStrList;
}       


StrListInfo_t StrListDelete (StrList* list, int number)
{
    StrList* tmp_node = StrListGetNode( list, number );

    tmp_node->prev->next = tmp_node->next;
    tmp_node->next->prev = tmp_node->prev;

    free( tmp_node );

    return kGoodStrList;
}


/*
* 1st arg -- list, where to find
* 
* 2nd arg -- string to search 
*
* return -- number of elem node, if found; (< 0), if not found
*/
int StrListFindNode (StrList* list, const wchar_t* string)
{
    StrList* tmp_node = list->next;
    StrList* next_node = nullptr;
    int iter = 0;

    while (1)
    {   
        next_node = tmp_node->next;

        if (next_node)
        {
            if (tmp_node != list)
            {
                if (!wcscmp( GET_NODE_DATA(tmp_node), string))
                {
                    return iter;
                }
                else  
                {
                    tmp_node = next_node;
                    iter++;
                }
            }
            else  
            {
                return -1;
            }
        }
        else  
        {
            printf("Bad list allocation");
            exit(1);
        }
    }

    return -1;
}
