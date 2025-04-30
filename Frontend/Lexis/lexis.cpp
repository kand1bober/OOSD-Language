#include "../Headers/tree_input.h"
#include "../Headers/tree_functions.h"

//------------------DRIVER-----------------------
enum TreeErrors MakeTreeData( struct File_text* dump, struct File_text* file, struct Tree* tree )
{
    ON_DEBUG( printf(RED "====== START MakeTreeData ======\n" DELETE_COLOR); )

    //-------------------FILE WORK-------------------
    char filepath[256] = {};
    GetFilePath( filepath, tree_data_name_old);
    FILE* stream = fopen( filepath, "r" );

    struct stat file_info = {};
    stat( filepath, &file_info );
    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;
    file->stream_size = size_of_stream;

    if( file->stream_size > 0 )
    {
        file->buffer = (char*)calloc( size_of_stream + 1, sizeof(char) );
        fseek(stream, sizeof(char) * 0L,  SEEK_SET);
        fread( (void*)file->buffer, sizeof(char), size_of_stream, stream);

        //------INPUT-----------------
        struct ParserSrc src = {};
            //----Init------
            src.p = 0;
            src.old_p = 0;
            strcpy( src.s, file->buffer );
            src.tree = tree;
            //--------------

        Node_t* answer = nullptr;
        GetG( &src );
        //----------------------------

        fclose(stream);
        free( file->buffer );
    }

    return GOOD_INPUT;
}
//-----------------------------------------------


//------------RECURSIVE DESCENT------------------
void GetG( struct ParserSrc* src )
{
    if( src->s[src->p] != '$' )
    {
        SyntaxError (__FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(0);
    }
    src->p++;

    src->tree->root = GetE( src );
    
    if( src->s[src->p] != '$' )
    {
        printf(RED "Syntax error in the end of GetG\n" DELETE_COLOR);
        exit(0);
    }
    src->p++;
}


Node_t* GetE( struct ParserSrc* src )
{
    Node_t* val = GetT( src );
 
    while( (src->s[src->p] == '+') || (src->s[src->p] == '-') )
    {
        int op = src->p;

        src->p++;
        Node_t* val2 = GetT( src );
        if( src->s[op] == '+' )
        {
            Node_t* tmp_node = nullptr;
            Data_t value = {};
            value.op = kAdd;
            tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

            InsertLeave( src->tree, tmp_node, LEFT, val );
            InsertLeave( src->tree, tmp_node, RIGHT, val2 );

            //----exchange----
            Node_t* new_tmp = tmp_node;
            tmp_node = val;
            val = new_tmp;
            //----------------
        }
        else
        {
            Node_t* tmp_node = nullptr;
            Data_t value = {};
            value.op = kSub;
            tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

            InsertLeave( src->tree, tmp_node, LEFT, val );
            InsertLeave( src->tree, tmp_node, RIGHT, val2 );

            //----exchange----
            Node_t* new_tmp = tmp_node;
            tmp_node = val;
            val = new_tmp;
            //----------------
        }
    }

    return val;
}


Node_t* GetT( struct ParserSrc* src )
{
    Node_t* val = GetD( src );

    while( src->s[src->p] == '*' || src->s[src->p] == '/' )
    {
        int op = src->p;
        src->p++;
        Node_t* val2 = GetD( src );
        if( src->s[op] == '*' )
        {
            Node_t* tmp_node = nullptr;
            Data_t value = {};
            value.op = kMul;
            tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
            // val *= val2;
            InsertLeave( src->tree, tmp_node, LEFT, val );
            InsertLeave( src->tree, tmp_node, RIGHT, val2 );

            //----exchange----
            Node_t* new_tmp = tmp_node;
            tmp_node = val;
            val = new_tmp;
            //----------------
        }
        else if( src->s[op] == '/' )
        {
            Node_t* tmp_node = nullptr;
            Data_t value = {};
            value.op = kDiv;
            tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
            // val *= val2;
            InsertLeave( src->tree, tmp_node, LEFT, val );
            InsertLeave( src->tree, tmp_node, RIGHT, val2 );

            //----exchange----
            Node_t* new_tmp = tmp_node;
            tmp_node = val;
            val = new_tmp;
            //----------------
        }
        else 
        {
            printf(RED "unknown problem in %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
            exit(0);
        }
    }
    return val;
}


Node_t* GetD( struct ParserSrc* src )
{
    Node_t* val = GetSL( src ); 

    while( src->s[src->p] == '^' )
    {
        int op = src->p;
        src->p++;
        Node_t* val2 = GetSL( src ); 

        Node_t* tmp_node = nullptr;
        Data_t value = {};
        value.op = kDeg;
        tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

        InsertLeave( src->tree, tmp_node, LEFT, val );
        InsertLeave( src->tree, tmp_node, RIGHT, val2 );

        //----exchange----
        Node_t* new_tmp = tmp_node;
        tmp_node = val;
        val = new_tmp;
        //----------------
    }

    return val;
}


Node_t* GetSL( struct ParserSrc* src )
{
    Data_t value = {};
    Node_t* val1 = nullptr;
    Node_t* val2 = nullptr;
    Node_t* val = nullptr;

    switch( src->s[src->p] )
    {   
        case 's':
        {
            if( strncmp( src->s + src->p, "sin", 3 ) == 0 )
            {
                src->p += 3;

                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kSin;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else 
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                    exit(0);
                }
            }
            else 
            {
                printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
            }

            break;
        }

        case 'c':
        {
            if( strncmp( src->s + src->p, "cos", 3 ) == 0  )
            {
                src->p += 3;

                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kCos;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                    exit(0);
                }
            }
            else if(  strncmp( src->s + src->p, "ctg", 3 ) == 0 )
            {
                src->p += 3;

                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kCtg;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                    exit(0);
                }
            }
            else 
            {
                printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                exit(0);
            }

            break;
        }

        case 't':
        {
            if( strncmp( src->s + src->p, "tg", 2 ) == 0 )
            {
                src->p += 2;

                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kTg;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );  
                    exit(0);
                }
            }
            else
            {
                printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );   
                exit(0);
            }

            break;
        }

        case 'e':
        {
            if( strncmp( src->s + src->p, "exp", 3 ) == 0  )
            {
                src->p += 3;
                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kExp;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                    exit(0);
                }
            }
            else
            {
                printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                exit(0);
            }

            break;
        }

        case 'l':
        {
            if( strncmp( src->s + src->p, "log", 3 ) == 0 )
            {   
                src->p += 3;

                if( src->s[src->p] == '(' )
                {
                    src->p++;

                    val1 = GetP( src );

                    if( src->s[src->p] != ',' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }   
                    src->p++;

                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kLog;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, LEFT, val1 );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
                else
                {
                    printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                    exit(0);
                }
            }
            else if( strncmp( src->s + src->p, "ln", 2 ) == 0 )
            {
                src->p += 2;

                if( src->s[src->p] == '(' )
                {
                    src->p++;
                    val2 = GetP( src ); 

                    if( src->s[src->p] != ')' )
                    {
                        printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
                        exit(0);
                    }
                    src->p++;

                    value.op = kLn;
                    val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
                    InsertLeave( src->tree, val, RIGHT, val2 );
                }
            }
            else 
            {
                printf(RED "Syntax error %s in %s on line %d " DELETE_COLOR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );  
                exit(0);
            }
            break;
        }

        default:
        {
            val = GetP( src );
            break;  
        }
    }

    return val;
}


Node_t* GetP( struct ParserSrc* src )
{
    if( src->s[src->p] == '(' )
    {
        src->p++;
        Node_t* val = GetE( src );
        if( src->s[src->p] != ')' )
        {
            printf(RED "Syntax error in GetP\n" DELETE_COLOR);
            exit(0);
        }
        src->p++;

        return val;
    }
    else if( '0' <= src->s[src->p] && src->s[src->p] <= '9' )
    {
        return GetN( src );
    }
    else if( src->s[src->p] == 'x' )
    {
        return GetV( src );
    }
    else 
    {
        printf("Wrong input\n");
        exit(0);
    }
}

Node_t* GetN( struct ParserSrc* src )
{
    int val = 0;
    src->old_p = src->p;

    while( '0' <= src->s[src->p] && src->s[src->p] <= '9' )
    {   
        val = val*10 + src->s[src->p] - '0';
        src->p++;
    }
    assert( src->old_p != src->p );

    Node_t* new_node = nullptr;
    Data_t value = {};
    value.num = (double)val;
    new_node = CreateNode( src->tree, NULL, NULL, NULL, value, NUM );
    return new_node;
}

Node_t* GetV (struct ParserSrc* src)
{
    char val[2] = "";
    src->old_p = src->p;

    val[0] = src->s[src->p];
    src->p++;

    assert( src->old_p != src->p );

    Node_t* new_node = nullptr;
    Data_t value = {};
    value.var = val;
    new_node = CreateNode( src->tree, NULL, NULL, NULL, value, VAR );
    return new_node;
}
//-----------------------------------------------


//-----------------------------------------------
void SyntaxError (const char* file, const char* func, const unsigned long int line)
{
    printf(RED "Syntax error:" 
               "file: %s\n"
               "func: %s\n" 
               "line: %d\n" DELETE_COLOR, file, func, line);
}
//-----------------------------------------------