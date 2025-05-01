#include "list.h"

NumList* NumListCreateNode (const double data)
{
    NumList* new_node = (NumList* )malloc(sizeof(NumList));

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->data = data;

    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}


NumList* NumListCtor ()
{
    NumList* phantom = NumListCreateNode ((const double)NUM_LIST_POISON);

    phantom->next = phantom;
    phantom->prev = phantom;

    return phantom;
}


NumListInfo_t NumListDtor (NumList* list) 
{
    NumList* curr_node = list;
    NumList* next_node = curr_node->next;

    while (curr_node->next != list)
    {
        free (curr_node);
        curr_node = next_node;
        next_node = next_node->next;
    }

    free (curr_node);

    return kGoodNumList;
}
 

NumList* NumListGetNode (NumList* list, int number)
{
    NumList* curr_node = list;

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
NumListInfo_t NumListAdd (NumList* list, const double data, size_t number)
{
    NumList* new_node = NumListCreateNode(data);

    NumList* tmp_node = NumListGetNode(list, number);

    new_node->prev = tmp_node;
    new_node->next = tmp_node->next;
    
    tmp_node->next->prev = new_node;
    tmp_node->next = new_node;

    return kGoodNumList;
}       


NumListInfo_t NumListDelete (NumList* list, int number)
{
    NumList* tmp_node = NumListGetNode(list, number);

    tmp_node->prev->next = tmp_node->next;
    tmp_node->next->prev = tmp_node->prev;

    free( tmp_node );

    return kGoodNumList;
}


/*
* 1st arg -- list, where to find
* 
* 2nd arg -- string to search 
*
* return -- number of elem node, if found; (< 0), if not found
*/
int NumListFindNode (NumList* list, const double data)
{
    NumList* tmp_node = list->next;
    NumList* next_node = nullptr;
    int iter = 0;

    while (1)
    {   
        next_node = tmp_node->next;

        if (next_node)
        {
            if (tmp_node != list)
            {
                if (data == list->data)
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
