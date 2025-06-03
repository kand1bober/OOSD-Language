#include "tree.h"

Tree* TreeCtor()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

    tree->data = 0xBADBABA;
    tree->info = kGoodTree;
    tree->root = nullptr;

    return tree;
}

TreeInfo TreeDtor(Tree* tree)
{
    assert(tree);

    FreeTree(tree, tree->root);

    if (!tree)
        return kGoodTree;
    else 
        return kBadTree;
}


Node* CreateNode(Node* left, Node* right, Node* parent, NodeTypes type, TreeData data)
{
    Node* new_node = (Node*)calloc(1, sizeof(Node));
    new_node->type = type;

    if (type == kConst || type == kKeyWord || 
        type == kFuncDef || type == kParam || 
        type == kVarDecl || type == kCall )
    {
        new_node->data.num = data.num;
    }         
    else if (type == kIdentifier)
    {
        new_node->data.str = data.str;
    }         

    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;

    if (left)
        left->parent = new_node;

    if (right)
        right->parent = new_node;

    return new_node;
}   


TreeInfo InsertLeave (Tree* tree, Node* parent, Direction branch, Node* to_connect)
{   
    assert(to_connect);

    if (parent)
    {
        if (branch == kLeft)
        {
            if (!parent->left)
            {
                parent->left = to_connect;
                to_connect->parent = parent;

                return kGoodTree;
            } 
            else 
            {
                wprintf(RED L"your parent node have leaves\n"
                "So call InsertNode function instead of this function\n"
                "And your node deleted for programm to not catch seg-fault\n"
                "So create it again\n" DELETE_COLOR);

                free(to_connect);

                return kBadTree;
            }
        }   
        else if (branch == kRight)
        {
            if (!parent->right)
            {
                parent->right = to_connect;
                to_connect->parent = parent;
            }
            else 
            {
                wprintf(RED L"your parent node have leaves\n"
                "So call InsertNode function instead of this function\n"
                "And your node deleted for programm to not catch seg-fault\n"
                "So create it again\n" DELETE_COLOR);
                
                free(to_connect);

                return kGoodTree;
            }

            return kGoodTree;
        }
    }
    else //случай, когда вставляем корень 
    {
        tree->root = to_connect;
        to_connect->parent = nullptr;
        ON_DEBUG( wprintf(RED L"root inserted in beginning of tree\n" DELETE_COLOR); )
    }

    return kGoodTree;
}


//insert already existing node
TreeInfo InsertNode(Node* left, Node* right, Node* node)
{
    if (left && right)
    {
        ON_DEBUG( wprintf(SINIY L"inserting in the middle of tree\n" DELETE_COLOR); ) 

        if (left->parent == right->parent)
        {
            left->parent->left = node;
            left->parent->right = nullptr; // всегда освобождаем правый элемент при вставке

            node->parent = left->parent;

            left->parent = node;
            right->parent = node;

            node->left = left;
            node->right = right;

            return kGoodTree;
        }
        else
        {
            ON_DEBUG( wprintf(YELLOW L"Pointers don't connect\n" DELETE_COLOR); )
            exit(1);
        }   
    }
    else if (!left && !right) 
    {
        wprintf(RED L"Two null pointers pasted -- means yout parent node have no leaves.\n"
        "free is used to avoid memory leaks\n"
        "Call InsertLeave To create leaves\n" DELETE_COLOR);

        free(node);
        exit(1);

        return kGoodTree;
    }
    else if (left && !right)
    {
        ON_DEBUG( wprintf(SINIY L"insert, left exists, right doesn't\n" DELETE_COLOR); )
        if (left->parent->left == left)
        {
            left->parent->left = node;
        }
        else if (left->parent->right == left)
        {
            left->parent->right = node;
        }

        node->parent = left->parent;
        left->parent = node;
        node->left = left;

        return kGoodTree;
    }
    else if (!left && right)
    {
        ON_DEBUG( wprintf(SINIY L"insert, right exists, left doesn't\n" DELETE_COLOR); )

        if (right->parent->left == right)
        {
            right->parent->left = node;
        }
        else if (right->parent->right == right)
        {
            right->parent->right = node;
        }

        node->parent = right->parent;
        right->parent = node;
        node->right = right;

        return kGoodTree;
    }

    return kBadTree;  
}


void FreeTree (Tree* tree, Node* node)
{   
    assert(tree);
    assert(node);
    
    Node* left = node->left;
    Node* right = node->right;

    if (left)
        FreeTree(tree, left);

    if (right)
        FreeTree(tree, right);

    free(node);
}


TreeInfo BranchDelete (Tree* tree, Node* node, NodeTypes node_type) 
{
    if (node)
    {
        if (!node->left && !node->right)
        {
            ON_DEBUG( wprintf(SINIY L"deleting \"leave\" node\n" DELETE_COLOR); )

            Node* tmp_parent = node->parent;

            if (tmp_parent->left == node)
            {
                tmp_parent->left = nullptr;
                free(node);
            }
            else if (tmp_parent->right == node)
            {
                tmp_parent->right = nullptr;
                free(node);
            }
        }
        else if (node->left && node->right)
        {
            ON_DEBUG( wprintf(SINIY L"deleting node with both branches\n( causes deletion of all nodes under )\n" DELETE_COLOR); )
 
            Node* tmp_parent = node->parent;

            if (tmp_parent->left == node)
            {
                tmp_parent->left = nullptr;
            }
            else if (tmp_parent->right == node)
            {
                tmp_parent->right = nullptr;
            }
            
            FreeTree(tree, node);

            return kGoodTree;
        }
        else if (node->left && !node->right) 
        {
            ON_DEBUG( wprintf(SINIY L"deleting node with only left branch\n" DELETE_COLOR); )

            if (node->parent->left == node)
            {
                node->parent->left = nullptr;
            }
            else if (node->parent->right == node)
            {
                node->parent->right = nullptr;
            }

            FreeTree(tree, node);

            return kGoodTree;
        }
        else if (!node->left && node->right)
        {
            ON_DEBUG( wprintf(SINIY L"extracting node with only right branch\n" DELETE_COLOR); )

            if (node->parent->left == node)
            {
                node->parent->left = nullptr;
            }
            else if (node->parent->right == node)
            {
                node->parent->right = nullptr;
            }

            FreeTree(tree, node);

            return kGoodTree;    
        }
    }
    else 
    {   
        wprintf(RED L"wrong node pointer pasted to extract");
        return kBadTree;
    }

    return kBadTree;
}


Node* FindNode(Node* node_search, NodeTypes type, TreeData to_find)
{
    Node* left_search = node_search->left;
    Node* right_search = node_search->right;

    if (node_search->type != type)
    {
        if (left_search)
        {
            return (FindNode (left_search, type, to_find));
        }

        if (right_search)
        {
            return (FindNode (right_search, type, to_find));
        }
    }
    else 
    {

        if (type == kConst || type == kKeyWord || 
            type == kFuncDef || type == kParam || 
            type == kVarDecl || type == kCall )
        {
            if (node_search->data.num == to_find.num)
                return node_search;
            else 
                return NULL;
        }         
        else if (type == kIdentifier)
        {
            if (!wcscmp(node_search->data.str, to_find.str))
                return node_search;
            else 
                return NULL;
        } 
    }

    return NULL;
}


Node* CopyNode (Tree* tree, Node* node_to_copy)
{
    assert(tree);
    assert(node_to_copy);

    Node* answer = nullptr;
    answer = CreateNode(NULL, NULL, NULL, node_to_copy->type, node_to_copy->data);
        
    return answer;
}


Node* CopyBranch (Tree* tree, Node* to_copy, Node* parent)
{
    Node* tmp_node = nullptr;

    tmp_node = CopyNode(tree, to_copy);
    tmp_node->parent = parent;

    if (to_copy->left)
    {
        tmp_node->left = CopyBranch(tree, to_copy->left, tmp_node);
    }

    if (to_copy->right)
    {
        tmp_node->right = CopyBranch(tree, to_copy->right, tmp_node);
    }

    return tmp_node;
}
