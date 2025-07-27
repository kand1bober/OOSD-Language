#include <cstdint>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "proc_library.h"

#include "MyStackLib.h"


#ifndef PROC_FUNCTIONS_HEADER
#define PROC_FUNCTIONS_HEADER

struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};

struct File_proc 
{
    Header head;
    char name[30];
    char* buffer; 
};

struct Line_ptr
{
    char* begin;    
    int length;
};

struct RAM 
{
    ProcElem* ram;
    uint64_t size;
    uint64_t capacity;
    bool access;
};

struct SPU
{
    uint64_t size_of_code;
    int64_t IP;
    Stack_t stack;
    Stack_t calls_stack;
    int count_calls;

    char* code;
    ProcElem* regs;
    RAM memory;
};


void Run( struct SPU* flow_copy );
void InputFileCode( struct File_proc* file, struct SPU* proc );
void BinaryIntOutput( int number );
void BinaryCharOutput( unsigned char number );

ProcElem GetArgPush( struct SPU* proc );
int DoPop( ProcElem arg, struct SPU* proc );
int DoJump( struct SPU* proc );
int VideoCard( struct RAM* memory );

int ProcCtor( struct SPU* proc, struct File_proc* file );
int ProcDtor( struct SPU* proc ); 
int RamCtor( struct RAM* memory );
void RamDump( struct RAM* memory );
int RegCtor( struct SPU* proc );
void RegDump( ProcElem* regs );


const int MEMORY_START_SIZE = 1000;
const uint64_t RET_STACK_VALUE = 0xB1ADE5;
const uint64_t REGS_AMOUNT = 4;
const double EPSILON = 0.5;
const double NORMAL_EPSILON = 0.5;


#endif