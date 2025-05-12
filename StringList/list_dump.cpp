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
        wprintf(RED "Error in opening file \"%s\" \n" DELETE_COLOR, output_html);
        exit(1);
    }   
    fprintf(html_stream, "<img src=\"ListGraph.svg\"  alt=\"MyGraph\" >");  // TODO: correct to name from static const char
    fclose(html_stream);
    //=================

    //=== GRAPH FILE ===
    file->file = fopen(output_graph, "w");
    if (!file->file)
    {
        wprintf(RED "Error in opening file \"%s\" \n" DELETE_COLOR, output_graph);
        exit(1);
    }   
    //==================

    //=== Write node settings ===
    fprintf(file->file, "digraph G\n{\nlabel=\"%s\";\n labelloc=\"t\";\n fontsize=30\n fontname=\"%s\";\n fontcolor=\"%s\"\n"
    "\nrankdir=LR; splines=ortho; size=\"200,300\"; bgcolor=\"%s\";\n", graph_header, fontname, fontcolor, bgcolor);
    //===========================

    return kGoodStrList;
}


StrListInfo_t EndDotOutput (FileInfo* file_info)
{
    fprintf(file_info->file, "\n}\n");
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
    fwprintf( file_info->file, L"{ node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%s\", color=\"%s\", "
                                "label=\" { Phantom } | { data: %lX } | { <curr%p> curr: %p } | { { <prev%p> prev: %p } | { <next%p> next: %p } }  \"] \n}\n",
                                 list, first_fillcolor, default_pointer_color, GET_NODE_DATA(list), list, list, list, list->prev, list, list->next);
    //===================

    StrList* curr_node = list->next;
    int nodes_count = 0;
    while (1)
    {
        //=== Description ===
        fwprintf(file_info->file, L"node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%s\", color=\"%s\", "
                                   "label=\" { <num%d> num: %d } | { <data%.2lf> data: %.2lf } | { <curr%p> curr: %p } | { { <prev%p> prev: %p } | { <next%p> next: %p } }  \"] \n", 
                                    curr_node, third_fillcolor, default_pointer_color, nodes_count, nodes_count, GET_NODE_DATA(curr_node), GET_NODE_DATA(curr_node), curr_node, curr_node, curr_node, curr_node->prev, curr_node, curr_node->next );
        //===================

        curr_node = curr_node->next;
        if (curr_node == list) 
            break;

        nodes_count++;
    }
    fprintf(file_info->file, "\n");

    StrList* left_node = list;
    StrList* right_node = left_node->next;
    while (1)
    {
        //=== Arrows ===
        fprintf(file_info->file, "node_%p -> node_%p [color =\"%s\"];\n", left_node, left_node->next, first_fillcolor);
        fprintf(file_info->file, "node_%p -> node_%p [color =\"%s\"];\n", left_node, left_node->prev, second_fillcolor);
        //==============

        if( right_node == list )
            break;

        left_node = right_node;
        right_node = right_node->next;
    }

    return kGoodStrList;
}

