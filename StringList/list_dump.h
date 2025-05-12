#include <wchar.h>
#include <cwchar>

#include "list.h"
#include "../Utilities/utilities.h"

#ifndef LIST_DOT_HEADER
#define LIST_DOT_HEADER

static const char output_image[] = "StringList/dump/ListGraph.svg";
static const char output_graph[] = "StringList/dump/ListGraph.dot";
static const char output_html[]  = "StringList/dump/ListGraph.html";

const size_t START_OUTPUT_FILE_SIZE =  10;
static const char default_pointer_color[] = "#FFE9C7";
static const char pointer_left_color[] = "#9ACD32"; 
static const char pointer_right_color[] = "#FF2B00";

static const char first_fillcolor[] = "#ff6699"; 
static const char second_fillcolor[] = "#34cb34";
static const char third_fillcolor[] = "#9966FF";

static const char bgcolor[] = "#ffd480";
static const char fontcolor[] = "#FFFFFF";

static const char fontname[] = "Verdana";
static const char graph_header[] = "List";

//-------------------------------------------------------------------
StrListInfo_t ListDot (StrList* list);

StrListInfo_t BeginDotOutput (FileInfo* file);

StrListInfo_t EndDotOutput (FileInfo* file);

StrListInfo_t DotDriver (StrList* list, FileInfo* file);

StrListInfo_t DotCollector (StrList* list, FileInfo* file);
//-------------------------------------------------------------------

#endif
