
#ifndef PROC_MACROS_HEADER
#define PROC_MACROS_HEADER

    #ifdef DEBUG

        #define ON_DEBUG_PROC( expr ) expr

    #else 

        #define ON_DEBUG_PROC( expr ) 
        
    #endif


    #ifdef STEP
        #define PAUSE getchar() 
    #else       
        #define PAUSE 
    #endif


    #ifdef RUN_PROC
        #define PRINT_PROCESS( expr ) expr
    #else       
        #define PRINT_PROCESS( expr )
    #endif
     

#endif
