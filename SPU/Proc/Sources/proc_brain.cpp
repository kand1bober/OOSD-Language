// #define DEBUG
// #define STEP
// #define RUN_PROC

#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"
#include "../Headers/proc_macros.h"
#include "../Headers/MyStackLib.h"

void Run(  struct SPU* proc_copy )
{   
    printf("Run processor:\n\n");

    struct SPU* proc = proc_copy;

    while(1)
    {
        char command = *(proc->code + proc->IP);

        char command_type = ( (command  & ~(255 << 5)) );

        ON_DEBUG_PROC
        (   
            printf("\n");
            printf(RED "Begin of cycle\n" DELETE_COLOR);
            printf("IP: %lu\n", proc->IP);
            printf(SINIY "Command, all 8 bits:\n" DELETE_COLOR);
            BinaryCharOutput( command );
            printf(PURPLE "Type of command, last 5 bits:\n" DELETE_COLOR); 
            BinaryCharOutput( command_type );
        )


        if ( (uint64_t)proc->IP < proc->size_of_code)
        {

            switch( command_type )
            {   
                case kPush:
                {
                    PRINT_PROCESS( printf("Push\n"); )

                    ProcElem arg = GetArgPush( proc ); //Takes all arguments of this command, one or two

                    PRINT_PROCESS( printf("arg: %lf\n", arg); )

                    STACK_PUSH_CALL( &proc->stack, arg );

                    continue;
                }

                case kPop:
                {
                    PRINT_PROCESS( printf("Pop\n"); )

                    ProcElem arg = 0;

                    arg = STACK_POP_CALL( &proc->stack );

                    PRINT_PROCESS( printf("poped value: %lf\n", arg); )

                    DoPop( arg, proc );

                    continue;
                }

                //=====JUMP PROCESSING=============
                case kJmpspace:
                {
                    proc->IP += 1;
                    continue;
                }
                case kRet:
                {
                    DoJump( proc );
                    continue;
                }
                case kJa:
                {        
                    DoJump( proc );
                    continue;
                }
                case kJae:
                {
                    DoJump( proc );
                    continue;
                }
                case kJb:
                {
                    DoJump( proc );
                    continue;
                }
                case kJbe:
                {
                    DoJump( proc );
                    continue;
                }
                case kJe:
                {
                    DoJump( proc );
                    continue;
                }
                case kJne:
                {
                    DoJump( proc );
                    continue;
                }
                case kJmp:
                {
                    DoJump( proc );
                    continue;
                }
                case kCall:
                {
                    DoJump( proc );
                    continue;
                }
                //====END OF JUMP PROCESSING=========

                case kOut:
                {
                    ProcElem arg = 0;
                    proc->IP += 1;
                    arg = STACK_POP_CALL(&proc->stack);
                    printf("OUT: %lf\n", arg); 
                    PAUSE;
                    continue;
                }

                case kIn:
                {
                    printf("In\n");
                    ProcElem arg = 0;
                    scanf("%lf", &arg);
                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, arg);
                    PAUSE;
                    continue;
                }

                case kAdd:
                {
                    PRINT_PROCESS( printf("Add\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    STACK_PUSH_CALL(&proc->stack, a + b);
                    proc->IP += 1;
                    PAUSE;
                    continue;
                }

                case kSub:
                {
                    PRINT_PROCESS( printf("Sub\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    STACK_PUSH_CALL(&proc->stack, (b - a) );
                    proc->IP += 1;

                    PAUSE;
                    continue;
                }

                case kMul:
                {
                    PRINT_PROCESS( printf("Mul\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    STACK_PUSH_CALL(&proc->stack, (a * b) );
                    proc->IP += 1;

                    PAUSE;
                    continue;
                }

                case kDiv:
                {
                    PRINT_PROCESS( printf("Div\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    STACK_PUSH_CALL(&proc->stack, (b / a) );
                    proc->IP += 1;

                    PAUSE;
                    continue;
                }

                case kSin:
                {
                    PRINT_PROCESS( printf("Sin\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                
                    STACK_PUSH_CALL(&proc->stack, sin( (double)a ) );
                    proc->IP += 1;

                    continue;
                }

                case kCos:
                {
                    PRINT_PROCESS( printf("Cos\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);

                    STACK_PUSH_CALL(&proc->stack, cos( (double)a ) );
                    proc->IP += 1;
                    
                    PAUSE;
                    continue;
                }

                case kRoot:
                {
                    PRINT_PROCESS( printf("Root\n"); )
                    ProcElem a = STACK_POP_CALL( &proc->stack );

                    STACK_PUSH_CALL(&proc->stack, sqrt( (ProcElem)a ) );
                    proc->IP += 1;

                    PAUSE;
                    continue;
                }

                case kDump:
                {
                    printf(YELLOW "-----------------------DUMP-----------------------\n" DELETE_COLOR); 
                    #ifdef DEBUG_STACK_FUNCS
                        StackDump( &proc->stack, __FILE__, __PRETTY_FUNCTION__, __LINE__);
                    #endif

                    printf(ORANGE "REGISETRS:\n" DELETE_COLOR);
                    RegDump( proc->regs );

                    printf(ORANGE "MEMORY:\n" DELETE_COLOR);
                    RamDump( &proc->memory );

                    printf(ORANGE "-------------------END OF DUMP-------------------\n" DELETE_COLOR);

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }

                case kHlt:
                {
                    PRINT_PROCESS( printf("Hlt\n"); )
                    ProcDtor( proc );
                    printf("Processor stopped\n");
                    PAUSE;
                    break;
                }


                case kNull:
                {
                    PRINT_PROCESS( printf("NUUUUL\n"); )

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }

                case kDraw:
                {
                    VideoCard( &proc->memory );
                    proc->IP += 1;

                    PAUSE;
                    continue;
                }
                
                case kFloor:
                {
                    PRINT_PROCESS( printf("Floor\n"); );
                    ProcElem a = STACK_POP_CALL( &proc->stack );
                    ProcElem b = 0;
                    modf( a, &b );
                    STACK_PUSH_CALL( &proc->stack, b );
                    proc->IP += 1;
                    continue;
                }

                default:
                {
                    PRINT_PROCESS( printf("SNTXERR: %d\n", command); )

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }
            }
            break;
        }
        else 
        {
            printf("Reached the end of programm with no halt, stoping\n");
            ProcDtor( proc );
            break;
        }
    }

}
