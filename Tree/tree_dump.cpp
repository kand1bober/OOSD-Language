#include "tree_dump.h"

//--------------------------DUMP--------------------------------
TreeInfo TreeDotOutput(Tree* tree)
{
    FileInfo file = {};

    StartTreeDotOutput(&file);

    TreeDotPrint(&file, tree);

    StopTreeDotOutput(&file);

    return kGoodTree;
}


TreeInfo StartTreeDotOutput(FileInfo* file)
{
    //-----HTML-----
    FILE* html_stream = fopen(tree_output_html_name, "w");
    if (!html_stream)
    {
        wprintf(RED "Error in opening file for writing\n" DELETE_COLOR);
        exit(1);
    }
    fwprintf(html_stream, L"<img src=\"%s\"  alt=\"MyGraph\" width=\"1300px\" height=\"900px\">", tree_output_image_name);
    fclose(html_stream);
    //--------------

    //-----DOT------
    file->file = fopen(tree_output_graph_name, "w");
    if (!file->file)
    {
        wprintf(RED "Error in opening file for writing\n" DELETE_COLOR);
        exit(1);
    }
    //--------------

    //---------------------Write node settings------------------------
    fwprintf(file->file, L"digraph G\n{\ncharset=\"latin1\";\nlabel=\"%ls\";\nlabelloc=\"t\";\nfontsize=30\nfontname=\"%ls\";\nfontcolor=\"%ls\"\n"
    "\nrankdir=TB;size=\"200,300\";bgcolor=\"%ls\";\n", tree_graph_header, tree_fontname, tree_fontcolor, tree_bgcolor); 
    //----------------------------------------------------------------

    return kGoodTree;
}


TreeInfo StopTreeDotOutput(FileInfo* file)
{
    fwprintf(file->file, L"\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s > %s", tree_output_graph_name, tree_output_image_name);
    ON_DEBUG( printf(SINIY "command for graphviz: " YELLOW "%s\n" DELETE_COLOR, cmd); )

    fclose(file->file);

    system(cmd);

    return kGoodTree;
}


TreeInfo TreeDotPrint(FileInfo* file, Tree* tree)
{   
    TreeDotWriteEdge(file, tree->root);

    return kGoodTree;
}


void TreeDotWriteEdge(FileInfo* file, Node* node)
{
    Node* left = node->left;
    Node* right = node->right;

    wchar_t node_data[100] = {0};
    wchar_t node_type[50] = {0};
    static const wchar_t* node_color = NULL;

    switch((int)node->type)
    {
        case kConstant:
        {   
            swprintf(node_type, 50, L"Constant");
            swprintf(node_data, 100, L"%ld", node->data.num);
            node_color = tree_const_fillcolor;
            break;
        }
        case kIdentifier: 
        {
            swprintf(node_type, 50, L"Identifier");
            swprintf(node_data, 100, L"%ld", node->data.num);
            node_color = tree_id_fillcolor;
            break;  
        }   
        case kKeyWord:
        {
            swprintf(node_type, 50, L"KeyWord");

            int keycode = node->data.num;
            switch (keycode)
            {
                case kLeftBracket:
                case kRightBracket:
                case kLeftCurlyBracket:
                case kRightCurlyBracket:
                case kEqual:
                case kAdd:
                case kSub:
                case kMul:
                case kDiv:
                case kPow:
                case kEcmp:
                case kAcmp:
                case kAEcmp:
                case kBcmp:
                case kBEcmp:
                case kNEcmp:
                case kAND:
                case kOR:
                case kNOT:
                case kStep:
                case kEnum:
                {   
                    swprintf(node_data, 20, L"%ls", KeyWordHTMLVal(node->data.num));
                    break;
                }

                default:
                {
                    swprintf(node_data, 100, L"%ls", KeyWordStrVal(node->data.num));; 
                    break;
                }
            }

            node_color = tree_keyword_fillcolor;
            break;
        }
        case kFuncDef:
        {
            swprintf(node_type, 50, L"Func Def");
            swprintf(node_data, 100, L"%ld", node->data.num);
            node_color = tree_funcdef_fillcolor;
            break;
        }
        case kParameters:
        {
            swprintf(node_type, 50, L"Parameters");
            swprintf(node_data, 100, L"&#8709;");
            node_color = tree_param_fillcolor;
            break;
        }
        case kVarDecl:
        {
            swprintf(node_type, 50, L"Var Decl");
            swprintf(node_data, 100, L"%ls", node->data.str);
            node_color = tree_vardecl_fillcolor;
            break;
        }
        case kCall:
        {
            swprintf(node_type, 50, L"Call");
            swprintf(node_data, 100, L"&#8709;");
            node_color = tree_call_fillcolor;
            break;
        }
        default:
        {
            wprintf(RED L"Error in tree dump\n" DELETE_COLOR);
            exit(1);
            break;
        }
    }

    fwprintf(file->file, L" node_%p [shape=record,style=\"rounded,filled\",fillcolor=\"%ls\",color=\"%ls\","
                "label=\" { { %ls } | { %ls } } \" ]; ",
                node, node_color, tree_default_pointer_color, node_type, node_data );

    if (node->left)
    {
        fwprintf(file->file, L"node_%p -> node_%p [color = \"%ls\", arrowsize = 1] ;\n", node, left, tree_pointer_left_color);    
        TreeDotWriteEdge(file, node->left);
    }

    if (node->right)
    {
        fwprintf(file->file, L"node_%p -> node_%p [color = \"%ls\", arrowsize = 1] ;\n", node, right, tree_pointer_right_color);    
        TreeDotWriteEdge(file, node->right);
    }
}
//------------------------------------------------------------

