#include "list.h"

NumList* NumListCreateNumNode (const int64_t data)
{
    NumList* new_node = (NumList* )malloc(sizeof(NumList));

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->data_type = kNumData;
    new_node->data.number = data;

    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}


NumList* NumListCreateConstNode (const int64_t data)
{
    NumList* new_node = (NumList* )malloc(sizeof(NumList));

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->data_type = kConstData;
    new_node->data.number = data;

    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}


NumList* NumListCreatePtrNode (void* data)
{
    NumList* new_node = (NumList* )malloc(sizeof(NumList));

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->data_type = kPtrData;
    new_node->data.ptr = data;

    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}


NumList* NumListCtor ()
{
    NumList* phantom = NumListCreateNumNode(NUM_LIST_POISON);

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
* 2nd arg -- type of data: num or ptr 
*
* 3rd arg -- data: num or ptr
*
* 4th arg -- position in the list (if you want to add in the end, 3rd arg = size of list)
*/
NumListInfo_t NumListAdd (NumList* list, DataTypes data_type, NumListData data, size_t number)
{
    NumList* new_node = NULL;

    if (data_type == kNumData)
    {
        new_node = NumListCreateNumNode(data.number);
    }
    else if (data_type == kPtrData)
    {
        new_node = NumListCreatePtrNode(data.ptr);
    }
    else if (data_type == kConstData)
    {
        new_node = NumListCreateConstNode(data.number);
    }
    else  
    {
        printf("ERRROR\n\n");
        exit(1);
    }

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

    free(tmp_node);

    return kGoodNumList;
}

