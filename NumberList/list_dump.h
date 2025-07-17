#include <wchar.h>
#include <cwchar>

#include "list.h"
#include "../Utilities/utilities.h"
#include "../Common/keywords.h"
#include "../StringList/list.h"

#ifndef NUM_LIST_DOT_HEADER
#define NUM_LIST_DOT_HEADER

static const char num_output_image[] = "NumberList/dump/ListGraph.svg";
static const char num_output_graph[] = "NumberList/dump/ListGraph.dot";
static const char num_output_html[]  = "NumberList/dump/ListGraph.html";

const size_t NUM_START_OUTPUT_FILE_SIZE =  10;
static const wchar_t num_default_pointer_color[] = L"#FFE9C7";
static const wchar_t num_pointer_left_color[] = L"#9ACD32"; 
static const wchar_t num_pointer_right_color[] = L"#FF2B00";

static const wchar_t num_first_fillcolor[] = L"#ff6699"; 
static const wchar_t num_second_fillcolor[] = L"#34cb34";
static const wchar_t num_third_fillcolor[] = L"#9966FF";
static const wchar_t num_fourth_fillcolor[] = L"#e8d92e";

static const wchar_t num_bgcolor[] = L"#ffd480";
static const wchar_t num_fontcolor[] = L"#FFFFFF";

static const wchar_t num_fontname[] = L"DejaVu Sans";
static const wchar_t num_graph_header[] = L"List";

//-------------------------------------------------------------------
NumListInfo_t NumListDot (NumList* list);

NumListInfo_t BeginNumDotOutput (FileInfo* file);

NumListInfo_t EndNumDotOutput (FileInfo* file);

NumListInfo_t NumDotDriver (NumList* list, FileInfo* file);

NumListInfo_t NumDotCollector (NumList* list, FileInfo* file);
//-------------------------------------------------------------------

#endif

