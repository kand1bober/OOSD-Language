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
static const wchar_t default_pointer_color[] = L"#FFE9C7";
static const wchar_t pointer_left_color[] = L"#9ACD32"; 
static const wchar_t pointer_right_color[] = L"#FF2B00";

static const wchar_t first_fillcolor[] = L"#ff6699"; 
static const wchar_t second_fillcolor[] = L"#34cb34";
static const wchar_t third_fillcolor[] = L"#9966FF";

static const wchar_t bgcolor[] = L"#ffd480";
static const wchar_t fontcolor[] = L"#FFFFFF";

static const wchar_t fontname[] = L"Verdana";
static const wchar_t graph_header[] = L"List";

//-------------------------------------------------------------------
StrListInfo_t ListDot (StrList* list);

StrListInfo_t BeginDotOutput (FileInfo* file);

StrListInfo_t EndDotOutput (FileInfo* file);

StrListInfo_t DotDriver (StrList* list, FileInfo* file);

StrListInfo_t DotCollector (StrList* list, FileInfo* file);
//-------------------------------------------------------------------

#endif
