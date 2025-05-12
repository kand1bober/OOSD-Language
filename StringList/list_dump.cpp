#include "list_dump.h"

StrListInfo_t ListDot (StrList* list)
{
    FileInfo file = {};

    BeginDotOutput(&file);

    DotDriver(list, &file);

    EndDotOutput(&file);

    return kGoodStrList;
}


StrListInfo_t BeginDotOutput (FileInfo* file)
{
    //=== HTML FIlE ===
    setlocale(LC_ALL, "");
    FILE* html_stream = fopen(output_html, "w");
    if (!html_stream)
    {
        wprintf(RED L"Error in opening file \"%s\" \n" DELETE_COLOR, output_html);
        exit(1);
    }   
    fwprintf(html_stream, L"<img src=\"ListGraph.svg\"  alt=\"MyGraph\" >");  // TODO: correct to name from static const char
    fclose(html_stream);
    //=================

    //=== GRAPH FILE ===
    file->file = fopen(output_graph, "w");
    if (!file->file)
    {
        wprintf(RED L"Error in opening file \"%s\" \n" DELETE_COLOR, output_graph);
        exit(1);
    }   
    //==================

    //=== Write node settings ===
    fwprintf(file->file, L"digraph G\n{\nlabel=\"%ls\";\n labelloc=\"t\";\n fontsize=30\n fontname=\"%ls\";\n fontcolor=\"%ls\"\n"
    "\nrankdir=LR; splines=ortho; size=\"200,300\"; bgcolor=\"%ls\";\n", graph_header, fontname, fontcolor, bgcolor);
    //===========================

    return kGoodStrList;
}


StrListInfo_t EndDotOutput (FileInfo* file_info)
{
    fwprintf(file_info->file, L"\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s > %s", output_graph, output_image);

    fclose(file_info->file);

    system(cmd);

    return kGoodStrList;
}


StrListInfo_t DotDriver (StrList* list, FileInfo* file)
{   
    DotCollector(list, file);

    return kGoodStrList;
}

StrListInfo_t DotCollector (StrList* list, FileInfo* file_info)
{
    //=== Description ===
    fwprintf(file_info->file, L"{ node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%ls\", color=\"%ls\", "
                                "label=\" { Phantom } | { data: %ls } | { curr: %p } | { { prev: %p } | { next: %p } }  \"] \n}\n",
                                 list, first_fillcolor, default_pointer_color, GET_NODE_DATA(list), list, list->prev, list->next);
    //===================

    StrList* curr_node = list->next;
    int nodes_count = 0;
    while (1)
    {
        //=== Description ===
        fwprintf(file_info->file, L"node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%ls\", color=\"%ls\", "
                                   "label=\" { num: %d } | { data: %ls } | { curr: %p } | { { prev: %p } | { next: %p } }  \"] \n", 
                                    curr_node, third_fillcolor, default_pointer_color, nodes_count, GET_NODE_DATA(curr_node), curr_node, curr_node->prev, curr_node->next );
        //===================

        curr_node = curr_node->next;
        if (curr_node == list) 
            break;

        nodes_count++;
    }
    fwprintf(file_info->file, L"\n");

    StrList* left_node = list;
    StrList* right_node = left_node->next;
    while (1)
    {
        //=== Arrows ===
        fwprintf(file_info->file, L"node_%p -> node_%p [color =\"%ls\"];\n", left_node, left_node->next, first_fillcolor);
        fwprintf(file_info->file, L"node_%p -> node_%p [color =\"%ls\"];\n", left_node, left_node->prev, second_fillcolor);
        //==============

        if( right_node == list )
            break;

        left_node = right_node;
        right_node = right_node->next;
    }

    return kGoodStrList;
}

