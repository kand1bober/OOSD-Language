// #define DEBUG
// #define STEP
// #define RUN_PROC

#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"
#include "../Headers/proc_macros.h"




ProcElem GetArgPush( struct SPU* proc )
{
    char command = *(char*)(proc->code + proc->IP);
    proc->IP += 1;
    char mode = ( ( command & ~(255 >> 3) ));

    ON_DEBUG_PROC
    (
        printf(GREEN "Subtype of command, first 3 bits\n" DELETE_COLOR);
        BinaryCharOutput( mode );
    )

    ProcElem arg = 0;
    uint64_t ram_addr = 0;

    if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) && (mode & INPUT_MASK) )
    {

        ram_addr = (uint64_t)( proc->regs[ *(char*)(proc->code + proc->IP ) - kAX ] );

        ON_DEBUG_PROC( uint64_t first_arg = ram_addr; )

        proc->IP += 1;
        ram_addr = (uint64_t)( *(ProcElem*)(proc->code + proc->IP));

        ON_DEBUG_PROC( uint64_t second_arg = ram_addr; )

        ON_DEBUG_PROC( printf("push from memory, from [ %lu + %lu ] \n", first_arg, second_arg); )

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);
        proc->memory.size -= 1;

        proc->IP += sizeof( ProcElem );
    }
    else if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) )
    {
        ram_addr = (uint64_t)( proc->regs[ *(char*)(proc->code + proc->IP) - kAX ] );

        ON_DEBUG_PROC( printf("push from memory, from register %d\n", *(char*)(proc->code + proc->IP) - kAX  ); )

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);
        proc->memory.size -= 1;

        proc->IP += 1;
    }
    else if( (mode & MEMORY_MASK ) && (mode & INPUT_MASK) )
    {
        ON_DEBUG_PROC( printf("push from memory, from [ Argument ]\n"); )

        ram_addr = (uint64_t)(*(ProcElem*)(proc->code + proc->IP));

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);
        proc->memory.size -= 1;

        proc->IP += sizeof( ProcElem);
    }
    else if( mode & REGISTER_MASK )
    {
        arg = (ProcElem)( proc->regs[ *(proc->code + proc->IP) - kAX ] );

        ON_DEBUG_PROC( printf("push from register %d\n", *(proc->code + proc->IP) - kAX ); )

        proc->IP += 1;
    }
    else if( mode & INPUT_MASK)
    {
        ON_DEBUG_PROC( printf("standart push\n"); )

        arg = *(ProcElem*)(proc->code + proc->IP );
        proc->IP += sizeof( ProcElem );
    }
    else 
    {
        ON_DEBUG_PROC( printf(RED "Something wrong in the instruction of Push\n" DELETE_COLOR); )
    }

    return arg;
}


int DoPop( ProcElem arg, struct SPU* proc )
{
    char command = *(char*)(proc->code + proc->IP);
    char mode = ( ( command & ~(255 >> 3) ) );
    proc->IP += 1;

    ON_DEBUG_PROC
    (
        printf(GREEN "Subtype of command, first 3 bits\n" DELETE_COLOR);
        BinaryCharOutput( mode );
    )

    uint64_t ram_addr = 0;
    size_t reg_number = 0;

    if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) && (mode & INPUT_MASK) )
    {
        reg_number = *(char*)(proc->code + proc->IP) - kAX;
        ram_addr += (uint64_t)proc->regs[reg_number];

        ON_DEBUG_PROC( uint64_t first_arg = ram_addr; )

        proc->IP += 1;

        ram_addr += (uint64_t)( *(ProcElem*)(proc->code + proc->IP) );
        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;
        proc->memory.size += 1;

        ON_DEBUG_PROC( uint64_t second_arg = ram_addr - first_arg; )

        proc->IP += sizeof( ProcElem);

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, to [ %lu + %lu ] \n" DELETE_COLOR, first_arg, second_arg ); )

        return 0;
    }
    else if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) )
    {
        reg_number = *(char*)(proc->code + proc->IP) - kAX;
        ram_addr += (uint64_t)proc->regs[reg_number];

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, address from register %lu, which contains %lu\n" DELETE_COLOR, reg_number, ram_addr); )

        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;
        proc->memory.size += 1;

        proc->IP += 1;

        return 0;
    }
    else if( (mode & MEMORY_MASK ) && (mode & INPUT_MASK) )
    {
        ram_addr += (uint64_t)( *(ProcElem*)(proc->code + proc->IP) );
        proc->IP += sizeof( ProcElem);

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, addres from value:= %lu\n" DELETE_COLOR, ram_addr); )

        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;
        proc->memory.size += 1;

        return 0;
    }
    else if( mode & REGISTER_MASK )
    {
        reg_number = ( *(char*)(proc->code + proc->IP) - kAX );

        ON_DEBUG_PROC( printf(ORANGE "pop to register %lu\n" DELETE_COLOR, reg_number); )

        *(ProcElem*)(proc->regs + reg_number) = arg;

        proc->IP += 1;

        return 0;
    }
    else 
    {
        ON_DEBUG_PROC( printf(RED "Something wrong in the instruction of Push\n" DELETE_COLOR); )
        return -1;
    }

    return -1; 
}


int DoJump( struct SPU* proc)
{
    uint64_t jump = 0;

    if ( *( proc->code + proc->IP) == kJmp)  
    {
        proc->IP++;
        jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
        proc->IP = jump;
        return 0;
    }
    else if ( *( proc->code + proc->IP) == kCall )
    {   
        STACK_PUSH_CALL( &proc->calls_stack, (ProcElem)proc->IP + sizeof(ProcElem) + 1);  //для того, чтобы прыгал сразу на байт, стоящий за call'ом

        proc->IP = (int64_t)( *(ProcElem*)( proc->code + proc->IP + 1 ) );

        return 0;
    }
    else if ( *( proc->code + proc->IP) == kRet )
    {
        ON_DEBUG_PROC( printf("ret:\n"); )

        if ( proc->calls_stack.size > 0 )
        {
            proc->IP = (uint64_t)STACK_POP_CALL( &proc->calls_stack );
            return 0;
        }
        else
        {
            // STACK_PUSH_CALL( &proc->calls_stack, (ProcElem)RET_STACK_VALUE );
            proc->IP += 1;
            return 0;
        }
    }   
    else if( proc->stack.size > 1)
    {                             
        ProcElem a = STACK_POP_CALL( &proc->stack);
        ProcElem b = STACK_POP_CALL( &proc->stack);

        STACK_PUSH_CALL( &proc->stack, b);
        STACK_PUSH_CALL( &proc->stack, a);

        switch( *(proc->code + proc->IP++ ) ) 
        {
            case kJa:
            {   
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if ( b > a )
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }
            case kJae:
            {   
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if ( (b > a) || ( fabs( b - a ) < EPSILON ) )
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }
            case kJb:
            {
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if (b < a)
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }
            case kJbe:
            {
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if ( (b < a) || ( fabs( a -b ) < EPSILON ) )
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }
            case kJe:
            {
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if ( fabs( b - a ) < EPSILON )
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }
            case kJne:
            {
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
                if ( fabs( b - a ) > EPSILON )
                {
                    proc->IP = jump;
                }
                else 
                {
                    proc->IP += sizeof(ProcElem);
                }
                break;
            }

            default:
            {
                break;
            }
        }

        return 0;
    }
    else 
    {
        ON_DEBUG_PROC( printf(RED "Not enough elements to comapare, and jump\n" DELETE_COLOR); )
        return -1;
    }

    return -1; //HUUUUUUUUUUUUUUUUY
}

//===============PROC CREATE===============
int ProcCtor( struct SPU* proc, struct File_proc* file ) 
{
    int status = 0;

    STACK_CTOR_CALL( &proc->stack, START_CAPACITY);
    STACK_CTOR_CALL( &proc->calls_stack, START_CAPACITY);

    proc->code = file->buffer;
    proc->size_of_code = file->head.size_of_code;
    proc->IP = 0;

    status = RegCtor( proc);

    status = RamCtor( &proc->memory );

    if( !status )
        return 0;
    else
        return -1;
}

int ProcDtor( struct SPU* proc )
{
    STACK_DTOR_CALL(&proc->stack);
    STACK_DTOR_CALL( &proc->calls_stack);
    free( proc->memory.ram );
    free( proc->code );
    free( proc->regs );

    if( (!proc->memory.ram) && (!proc->code) && (!proc->regs) )
        return 0;
    else
        return - 1;
}
//=========================================


//===========REGISTER FUNCTIONS=============
int RegCtor( struct SPU* proc )
{
    proc->regs = (ProcElem*)calloc( REGS_AMOUNT, sizeof(ProcElem) );
    if( proc->regs )
        return 0;
    else
        return -1;
}

void RegDump( ProcElem* regs )
{
    for(int i = 0; i < 3; i++)
    {
        printf("[%d]: %lf\n", i, regs[i] );
    }
}
//===========================================


//================================= MEMORY FUNCTIONS ==========================================
int RamCtor( struct RAM* memory )
{
    memory->capacity = MEMORY_START_SIZE;
    memory->ram = (ProcElem*)calloc( memory->capacity, sizeof(ProcElem) );  
    memory->size = 0;

    //=====FILL WITH POISON=====
    for(uint64_t i = 0; i < memory->capacity; i++)
    {
        *(uint64_t*)(memory->ram + i) = RAM_POISON;
    }
    //==========================

    memory->access = true;

    return 0;
}


void RamDump( struct RAM* memory)
{
    printf(ORANGE "--------------------Memory Dump--------------------\n" DELETE_COLOR);
    
    for(uint64_t i = 0; i < memory->capacity; i += 5 )
    {
        for(uint64_t g = 0; g < 5; g++)
        {
            printf(GREEN "%10ld" DELETE_COLOR, i + g);
        }
        printf("\n");

        for(int k = 0; k < 5; k++)
        {
            ProcElem elem = *(double*)(memory->ram + i + k);
            uint64_t hex_elem = *(uint64_t*)(memory->ram + i + k);

            if( hex_elem == RAM_POISON)
            {
                printf("%10lX", hex_elem );
            }
            else 
            {
                printf(SINIY "%10.4lf" DELETE_COLOR, elem );
            }
        }
        printf("\n");
    }
}


int VideoCard( struct RAM* memory )
{
    printf(YELLOW "\nDrawing: mem_size = %lu\n------------------------\n" DELETE_COLOR, memory->size);

    for(uint64_t i = 0; i < memory->size; i += 31)
    {
        for( uint64_t g = 0; (g < 31) && (i + g < memory->size); g++ )
        {   
            if ( fabs( *(ProcElem*)(memory->ram + i + g) ) < NORMAL_EPSILON )
            {
                printf("**");
            }
            else if ( fabs( *(ProcElem*)(memory->ram + i + g) - 1 ) < NORMAL_EPSILON )
            {
                printf("  ");
            }
        }

        printf("\n");
    }
    printf(YELLOW "------------------------\n" DELETE_COLOR);

    return 0;
}
//===================================================================


void BinaryCharOutput(unsigned char number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR , (unsigned)((number & (1 << i)) >> i) );
    }
    printf("\n");
}


void BinaryIntOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR, (unsigned)((number & (1 << i)) >> i) );
    }
    printf("\n");
}
