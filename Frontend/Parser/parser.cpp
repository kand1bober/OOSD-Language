#include "parser.h"

// //------------RECURSIVE DESCENT------------------
void SyntaxAnalysis(Parser* parser, Tokenizer* tokenizer)
{

}

// /*
// * Get  Assignment   
// */
// void GetA(RecursiveDescent* src)
// {

// }


// /*
// * Get Begin/End
// */
// void GetG(RecursiveDescent* src)
// {
//     if (src->s[src->p] != '$')
//         SYNTAX_ERROR

//     src->p++;

//     src->tree->root = GetE( src );
    
//     if( src->s[src->p] != '$' )
//         SYNTAX_ERROR

//     src->p++;
// }


// /*
// * Get Plus/Minus
// */
// Node* GetE(RecursiveDescent* src)
// {
//     Node* val = GetT(src);
 
//     while( (src->s[src->p] == '+') || (src->s[src->p] == '-') )
//     {
//         int op = src->p;

//         src->p++;
//         Node* val2 = GetT( src );
//         if( src->s[op] == '+' )
//         {
//             Node* tmp_node = nullptr;
//             Data_t value = {};
//             value.op = kAdd;
//             tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

//             InsertLeave( src->tree, tmp_node, LEFT, val );
//             InsertLeave( src->tree, tmp_node, RIGHT, val2 );

//             //----exchange----
//             Node* new_tmp = tmp_node;
//             tmp_node = val;
//             val = new_tmp;
//             //----------------
//         }
//         else
//         {
//             Node* tmp_node = nullptr;
//             Data_t value = {};
//             value.op = kSub;
//             tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

//             InsertLeave( src->tree, tmp_node, LEFT, val );
//             InsertLeave( src->tree, tmp_node, RIGHT, val2 );

//             //----exchange----
//             Node* new_tmp = tmp_node;
//             tmp_node = val;
//             val = new_tmp;
//             //----------------
//         }
//     }

//     return val;
// }


// /*
// * Get Mul/Div
// */
// Node* GetT(RecursiveDescent* src )
// {
//     Node* val = GetD( src );

//     while( src->s[src->p] == '*' || src->s[src->p] == '/' )
//     {
//         int op = src->p;
//         src->p++;
//         Node* val2 = GetD( src );
//         if( src->s[op] == '*' )
//         {
//             Node* tmp_node = nullptr;
//             Data_t value = {};
//             value.op = kMul;
//             tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//             // val *= val2;
//             InsertLeave( src->tree, tmp_node, LEFT, val );
//             InsertLeave( src->tree, tmp_node, RIGHT, val2 );

//             //----exchange----
//             Node* new_tmp = tmp_node;
//             tmp_node = val;
//             val = new_tmp;
//             //----------------
//         }
//         else if( src->s[op] == '/' )
//         {
//             Node* tmp_node = nullptr;
//             Data_t value = {};
//             value.op = kDiv;
//             tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//             // val *= val2;
//             InsertLeave( src->tree, tmp_node, LEFT, val );
//             InsertLeave( src->tree, tmp_node, RIGHT, val2 );

//             //----exchange----
//             Node* new_tmp = tmp_node;
//             tmp_node = val;
//             val = new_tmp;
//             //----------------
//         }
//         else 
//             SYNTAX_ERROR
//     }
//     return val;
// }


// /*
// * Get Power Operation 
// */
// Node* GetD(RecursiveDescent* src )
// {
//     Node* val = GetSL( src ); 

//     while( src->s[src->p] == '^' )
//     {
//         int op = src->p;
//         src->p++;
//         Node* val2 = GetSL( src ); 

//         Node* tmp_node = nullptr;
//         Data_t value = {};
//         value.op = kDeg;
//         tmp_node = CreateNode( src->tree, NULL, NULL, NULL, value, OP );

//         InsertLeave( src->tree, tmp_node, LEFT, val );
//         InsertLeave( src->tree, tmp_node, RIGHT, val2 );

//         //----exchange----
//         Node* new_tmp = tmp_node;
//         tmp_node = val;
//         val = new_tmp;
//         //----------------
//     }

//     return val;
// }


// /*
// * Get Sin/Cos/Tg/Ctg/Log Operation 
// */
// Node* GetT(RecursiveDescent* src )
// {
//     Data_t value = {};
//     Node* val1 = nullptr;
//     Node* val2 = nullptr;
//     Node* val = nullptr;

//     switch( src->s[src->p] )
//     {   
//         case 's':
//         {
//             if (!strncmp( src->s + src->p, "sin", 3 ))
//             {
//                 src->p += 3;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kSin;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else 
//                     SYNTAX_ERROR
//             }
//             else 
//                 SYNTAX_ERROR

//             break;
//         }

//         case 'c':
//         {
//             if( strncmp( src->s + src->p, "cos", 3 ) == 0  )
//             {
//                 src->p += 3;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kCos;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else
//                     SYNTAX_ERROR
//             }
//             else if(  strncmp( src->s + src->p, "ctg", 3 ) == 0 )
//             {
//                 src->p += 3;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kCtg;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else
//                     SYNTAX_ERROR
//             }
//             else 
//                 SYNTAX_ERROR

//             break;
//         }

//         case 't':
//         {
//             if( strncmp( src->s + src->p, "tg", 2 ) == 0 )
//             {
//                 src->p += 2;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kTg;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else
//                     SYNTAX_ERROR
//             }
//             else
//                 SYNTAX_ERROR

//             break;
//         }

//         case 'e':
//         {
//             if( strncmp( src->s + src->p, "exp", 3 ) == 0  )
//             {
//                 src->p += 3;
//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kExp;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else
//                     SYNTAX_ERROR
//             }
//             else
//                 SYNTAX_ERROR

//             break;
//         }

//         case 'l':
//         {
//             if( strncmp( src->s + src->p, "log", 3 ) == 0 )
//             {   
//                 src->p += 3;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;

//                     val1 = GetP( src );

//                     if( src->s[src->p] != ',' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR

//                     src->p++;

//                     value.op = kLog;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, LEFT, val1 );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//                 else
//                     SYNTAX_ERROR
//             }
//             else if( strncmp( src->s + src->p, "ln", 2 ) == 0 )
//             {
//                 src->p += 2;

//                 if( src->s[src->p] == '(' )
//                 {
//                     src->p++;
//                     val2 = GetP( src ); 

//                     if( src->s[src->p] != ')' )
//                         SYNTAX_ERROR 

//                     src->p++;

//                     value.op = kLn;
//                     val = CreateNode( src->tree, NULL, NULL, NULL, value, OP );
//                     InsertLeave( src->tree, val, RIGHT, val2 );
//                 }
//             }
//             else 
//                 SYNTAX_ERROR

//             break;
//         }

//         default:
//         {
//             val = GetP( src );
//             break;  
//         }
//     }

//     return val;
// }


/*
* Get Bracket
*/
// Node* GetP(Parser* src )
// {
//     if (src->cur_node->type == kLeftBracket)
//     {
//         src->cur_node = src->cur_node->next;

//         Node* val = GetE(src);

//         if (src->cur_node->type == kLeftBracket)
//             SYNTAX_ERROR    // closing bracket needed //TODO: SYNTAX_ERROR(CLOSING_BRACKET), enum ошибок

//         src->cur_node = src->cur_node->next;

//         return val;
//     }
//     else if (src->cur_node->type == kNumber)
//     {
//         return GetN(src);
//     }
//     else if (src->cur_node->type == kSin  || src->cur_node->type == kCos   || src->cur_node->type == kFloor || 
//              src->cur_node->type == kPlus || src->cur_node->type == kMinus || src->cur_node->type == kMul   ||
//              src->cur_node->type == kDiv  || src->cur_node->type == kDiff  || src->cur_node->type == kSqrt  ||
//              src->cur_node->type == kPow)  // F(E)
//     {
//         KeyCode data = kError;

//         switch((int)src->cur_node->type)
//         {
//             case kSin:
//                 data = kSin;
//                 break;


//         }

//         return(CreateNode(src->tree, NULL, NULL, NULL, , kConst));
//     }
//     else if (src->cur_node->type == )
//     {

//     }
//     else  
//     {
//         SYNTAX_ERROR
//     }
// }


// /*
// * Get Number
// */
// Node* GetN(Parser* src )
// {    
//     src->old_node = src->cur_node;

//     Data val = src->cur_node->data;

//     Node* new_node = CreateNode(src->tree, NULL, NULL, NULL, val, kConst);

//     return new_node;
// }


// /*
// * Get Identifier
// */
// Node* GetId (Parser* src)
// {
//     src->old_node = src->cur_node;

//     Data val = src->cur_node->data;
//     NodeTypes type = kNoType;

//     Node* new_node = CreateNode(src->tree, NULL, NULL, NULL, val, kIdentifier);

//     return new_node;
// }
