#include "list_dump.h"

NumListInfo_t NumListDot (NumList* list)
{
    FileInfo file = {};

    BeginNumDotOutput(&file);

    NumDotDriver(list, &file);

    EndNumDotOutput(&file);

    return kGoodNumList;
}


NumListInfo_t BeginNumDotOutput (FileInfo* file)
{
    //=== HTML FIlE ===
    setlocale(LC_ALL, "");
    FILE* html_stream = fopen(num_output_html, "w");
    if (!html_stream)
    {
        wprintf(RED L"Error in opening file \"%s\" \n" DELETE_COLOR, num_output_html);
        exit(1);
    }   
    fwprintf(html_stream, L"<img src=\"ListGraph.svg\"  alt=\"MyGraph\" >");
    fclose(html_stream);
    //=================

    //=== GRAPH FILE ===
    file->file = fopen(num_output_graph, "w");
    if (!file->file)
    {
        wprintf(RED L"Error in opening file \"%s\" \n" DELETE_COLOR, num_output_graph);
        exit(1);
    }   
    //==================

    //=== Write node settings ===
    fwprintf(file->file, L"digraph G\n{\ncharset=\"latin1\";\nlabel=\"%ls\";\n labelloc=\"t\";\n fontsize=30\n fontname=\"%ls\";\n fontcolor=\"%ls\"\n"
    "\nrankdir=LR; splines=ortho; size=\"200,300\"; bgcolor=\"%ls\";\n", num_graph_header, num_fontname, num_fontcolor, num_bgcolor);
    //===========================

    return kGoodNumList;
}


NumListInfo_t EndNumDotOutput (FileInfo* file_info)
{
    fwprintf(file_info->file, L"\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s > %s", num_output_graph, num_output_image);

    fclose(file_info->file);

    system(cmd);

    return kGoodNumList;
}


NumListInfo_t NumDotDriver (NumList* list, FileInfo* file)
{   
    NumDotCollector(list, file);

    return kGoodNumList;
}

NumListInfo_t NumDotCollector (NumList* list, FileInfo* file_info)
{
    //=== Description ===

    fwprintf(file_info->file, L"{ node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%ls\", color=\"%ls\", "
                                "label=\" { Phantom } | {data: %ls } | { curr: %p } | { { prev: %p } | { next: %p } }  \"] \n}\n",
                                 list, num_first_fillcolor, num_default_pointer_color, L"Phantom", list, list->prev, list->next);
    //===================

    NumList* curr_node = list->next;
    int nodes_count = 0;
    while (1)
    {
        //=== Description ===
        wchar_t node_data_type[20] = {0};
        wchar_t node_data[20] = {0};
        wchar_t buffer[20] = {0};

        static const wchar_t* fillcolor = NULL;

        switch ((int)curr_node->data_type)
        {
            case kPtrData:
            {
                wcscpy(node_data_type, L"Identifier");
                wcscpy(node_data, GET_NODE_DATA(curr_node->data.ptr));
                fillcolor = num_second_fillcolor;
                break;
            }
            case kNumData:
            {
                wcscpy(node_data_type, L"KeyWord");
                wcscpy(node_data, KeyWordStrVal(curr_node->data.number)); 

                if (curr_node->data.number == kLeftCurlyBracket)
                {
                    swprintf(node_data, 20, L"\\{");
                }
                else if (curr_node->data.number == kRightCurlyBracket)
                {
                    swprintf(node_data, 20, L"\\}");
                }

                fillcolor = num_third_fillcolor;

                break;
            }
            case kConstData:
            {
                wcscpy(node_data_type, L"Constant");
                swprintf(node_data, 20, L"%ld", curr_node->data.number);
                fillcolor = num_fourth_fillcolor;
                break;
            }
            default:
            {
                wprintf(L"Error in switch\n");
                exit(1);
                break;
            }
        }

        fwprintf(file_info->file, L"node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%ls\", color=\"%ls\", "
                                   "label=\" { num: %d } | { data_type: %ls } | {data: %ls } | { curr: %p } | { { prev: %p } | { next: %p } }  \"] \n", 
                                    curr_node, fillcolor, num_default_pointer_color, nodes_count, node_data_type, node_data, 
                                    curr_node, curr_node->prev, curr_node->next );
        //===================

        curr_node = curr_node->next;
        if (curr_node == list) 
            break;

        nodes_count++;
    }
    fwprintf(file_info->file, L"\n");

    NumList* left_node = list;
    NumList* right_node = left_node->next;
    while (1)
    {
        //=== Arrows ===
        fwprintf(file_info->file, L"node_%p -> node_%p [color =\"%ls\"];\n", left_node, left_node->next, num_first_fillcolor);
        fwprintf(file_info->file, L"node_%p -> node_%p [color =\"%ls\"];\n", left_node, left_node->prev, num_second_fillcolor);
        //==============

        if( right_node == list )
            break;

        left_node = right_node;
        right_node = right_node->next;
    }

    return kGoodNumList;
}
