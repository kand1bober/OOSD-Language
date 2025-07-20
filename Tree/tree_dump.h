#include <cwchar>

#include "tree.h"
#include "../Utilities/utilities.h"

#ifndef TREE_DUMP_HEADER
#define TREE_DUMP_HEADER

static const char tree_project_directory[100] = "/home/vyacheslav/Language/Tree";

static const char tree_output_image_name[100] = "/home/vyacheslav/Language/Tree/dump/TreeGraph.svg";
static const char tree_output_graph_name[100] = "/home/vyacheslav/Language/Tree/dump/TreeGraph.dot";
static const char tree_output_html_name[100] =  "/home/vyacheslav/Language/Tree/dump/TreeGraph.html";

static const char tree_data_name[40] = "Data.txt";

static const size_t TREE_START_OUTPUT_FILE_SIZE =  10;
static const wchar_t tree_default_pointer_color[20] = L"#FFE9C7";
static const wchar_t tree_pointer_left_color[20] =    L"#9ACD32"; 
static const wchar_t tree_pointer_right_color[20] =   L"#FF2B00";

static const wchar_t tree_id_fillcolor[20] = L"#ff6699"; //#FFA9B8
static const wchar_t tree_const_fillcolor[20] = L"#03cffc";
static const wchar_t tree_keyword_fillcolor[20] =  L"#9966FF";
static const wchar_t tree_funcdef_fillcolor[20] =  L"#fca103";
static const wchar_t tree_param_fillcolor[20] =  L"#fc0303";
static const wchar_t tree_vardecl_fillcolor[20] =  L"#08c41e";
static const wchar_t tree_call_fillcolor[20] =  L"#916306";

static const wchar_t tree_bgcolor[20] =   L"#ffd480";
static const wchar_t tree_fontcolor[20] = L"#FFFFFF";

static const wchar_t tree_fontname[30] =     L"Verdana";
static const wchar_t tree_graph_header[30] = L"AST";

//-------------------------------------------------------------------
TreeInfo TreeDotOutput(Tree* tree);
TreeInfo StartTreeDotOutput(FileInfo* file);
TreeInfo StopTreeDotOutput(FileInfo* file);

TreeInfo TreeDotPrint(FileInfo* file, Tree* tree);
void TreeDotWriteEdge(FileInfo* file, Node* node);
//-------------------------------------------------------------------

#endif 
