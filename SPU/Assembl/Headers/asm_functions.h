
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../Headers/asm_library.h"
#include "../Headers/asm_utilities.h"

#ifndef ASM_FUNCTIONS_HEADER
#define ASM_FUNCTIONS_HEADER

// TODO: один GetArg без Push и Pop
//       квадратка и факториал

//==============INPUT=====================
void OutputFile(struct File_code* file);
void InputFileStruct(struct File_asm* file);
void OutputBuffer(struct File_asm* file_a, struct Output_buffer* output);
void CreateLinePointers(struct File_asm* file);
void CountManAndArg(struct File_asm* file);
//========================================

//============GET ARGUMENT FOR FUNCITONS WITH ARGUMENTS============
//=====================FIRST PROCESSING============================
void GetArg(char* command_name, struct Line_ptr* line, struct Output_buffer* output, struct Label_table* spisok);
int GetName( char* command_name, struct Output_buffer* output, struct Label_table* spisok, int size);
//=============SECOND PROCESSING===================================
void FillArrayOfJumps(struct Label* label, struct Label_table* spisok, int ip);
//=================================================================

//====================SPECIAL COMMANDS=============================
int GetArgPush(struct Output_buffer* output, struct Line_ptr* line);
int GetArgPop(struct Output_buffer* output, struct Line_ptr* line);

// const int MODE_1 = 1;
// const int MODE_2 = 2;

int GetArgJump(struct Output_buffer* output, Line_ptr* line, struct Label_table* spisok);
//==================================================================


//=========LABLE TABLE==============================================
void LabelTableCtor(struct Label_table* spisok);
void LabelTableDtor(struct Label_table* spisok);
void FindLabels(struct Label_table* spisok, struct File_asm* file);
int WriteLabel(struct Label_table* spisok, char* ptr, size_t length);
int WriteJump(struct Label_table* spisok, char* ptr, size_t length); //

Label* SearchLabel( struct Label_table* spisok, char* ptr,  size_t size );
void LabelDump(struct Label_table* spisok);
//==================================================================


//========ADDITIONAL===============
void BinaryIntOutput(int number);
void BinaryCharOutput(unsigned  char number);
//=================================


//=========EBANIY PARSER======================
void SkipOp( struct Line_ptr* input );
int GetValue( struct Output_buffer* output, struct Line_ptr* input, char* instruction );
int GetRegister( struct Output_buffer* output, struct Line_ptr* input, char* instruction ) ;
int GetArgNum( struct Line_ptr* input );
void BufferResize( struct Output_buffer* output );
//============================================

struct Line_ptr
{
    char* start;    
    int length; // TODO: size_t (если передать -1 в size_t размер станет 2^64-1, значит можно сделать проверку, что lenght > 2^10 (тогда ошибка (отрицательное число)))
    int line_ip;
};

struct File_asm
{
    char name[30];
    int size_of_file;
    char* buffer;
    int lines_amount;
    int size_of_code;
    Line_ptr* lines_arr; //array of structures
};

struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};

struct Output_buffer
{
    char* buffer;
    int ip;
    int capacity;
};

struct File_code
{
    Header head;
    char name[30];
    Output_buffer output_buffer;
};

#endif
