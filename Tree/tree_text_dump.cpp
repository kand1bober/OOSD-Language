#include "../Utilities/utilities.h"
#include "tree.h"
#include "tree_dump.h"

void TreeTextDump(Tree* tree)
{
    FILE* file = fopen("Tree/text_dump/prefix_entry.txt", "w");

    char* node_data = (char*)calloc(10, sizeof(char));

    RecursiveTreeDump(tree->root, node_data, file);

    fclose(file);
    free(node_data);
}   

void RecursiveTreeDump(Node* node, char* node_data, FILE* file)
{
    sprintf(node_data, "( %d ", node->type);
    fwrite(node_data, strlen(node_data), sizeof(char), file);

    switch ((int)node->type)
    {
        case kConstant:
        case kIdentifier:
        case kKeyWord:
        case kFuncDef:
        case kVarDecl:
        {
            sprintf(node_data, "%ld ", node->data.num);

            break;
        }
        case kCall:
        case kParameters:
        {
            sprintf(node_data, " ");
            break;
        }
    }
    fwrite(node_data, strlen(node_data), sizeof(char), file);

    if (node->left)
    {
        RecursiveTreeDump(node->left, node_data, file);
    }
    else  
    {
        fwrite("_ ", 2, sizeof(char), file);
    }

    if (node->right)
    {
        RecursiveTreeDump(node->right, node_data, file);
    }
    else  
    {
        fwrite("_ ", 2, sizeof(char), file);
    }

    fwrite(") ", 2, sizeof(char), file);
}

