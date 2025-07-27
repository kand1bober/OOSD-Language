#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"
#include "../Headers/proc_macros.h"

int main()
{
    int status = 0;

    //=====OPEN FILE AND CREATE PROCESSOR====
    struct File_proc file = {};
    struct SPU proc = {};

    InputFileCode(&file, &proc);

    status = ProcCtor( &proc, &file );
    //=======================================


    //============CHECK===========================
    PRINT_PROCESS
    ( 
        for( uint32_t i = 0; i < proc.size_of_code; i++)
        {
            printf("%10u\n", *(unsigned char*)(proc.code + i) );
        }
        printf("\n");
    )
    //============================================


    if( !status )
        Run( &proc );
    else
        printf(RED "proc wasn't created\n" DELETE_COLOR);

    return 0;   
}

