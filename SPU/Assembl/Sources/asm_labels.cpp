
#include "../Headers/asm_macros.h"
#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"


void LabelTableCtor(struct Label_table* spisok)
{
    spisok->labels = (Label*)calloc( LABEL_ARR_SIZE, sizeof(Label) );
    
    spisok->jumps = (Jump*)calloc( JUMP_ARR_SIZE, sizeof(Jump) );
    spisok->jump_count = 0;
}


void LabelTableDtor(struct Label_table* spisok)
{
    free( spisok->labels );
    free( spisok->jumps );
}


//================== ZERO STAGE PROCESSING ==============================
void FindLabels(struct Label_table* spisok, struct File_asm* file)
{
    ON_DEBUG( printf(GREEN "==Preprocessing labelss==\n" DELETE_COLOR); )

    spisok->amount = 1;
    char* ptr1 = nullptr;
    char* ptr2 = nullptr;

    //=========FINDING LABELS========================
    ON_DEBUG( printf(GREEN "===== Searching Labels =====\n" DELETE_COLOR); )
    for (int i = 0; i < file->lines_amount; i++)
    {
        ON_DEBUG( printf("%s\n", file->lines_arr[i].start); ) 

        if ( ( ptr1 = strchr( file->lines_arr[i].start, ':' ) ) != nullptr ) 
        {
            if ( ( ptr2 = strchr( file->lines_arr[i].start, ' ' ) ) == nullptr)
            {
                WriteLabel(spisok, file->lines_arr[i].start, ptr1 - file->lines_arr[i].start + 2);
                ON_DEBUG( printf(YELLOW "length of first metka: %ld\n" DELETE_COLOR, ptr1 - file->lines_arr[i].start + 2 ); );
            }
            else 
            {
                continue;
            }
        }
        else 
        {
            continue; 
        }
        ON_DEBUG( printf("\n"); )
    }

    //============FINDING JUMPS TO LABELS==================
    ON_DEBUG( printf(GREEN "====== Searching Jumps ======\n" DELETE_COLOR); )
    for (int i = 0; i < file->lines_amount; i++)
    {
        ON_DEBUG( printf("%s\n", file->lines_arr[i].start); ) 

        if ( ( ptr1 = strchr( file->lines_arr[i].start, ':' ) ) != nullptr ) 
        {
            if ( ( ptr2 = strchr( file->lines_arr[i].start, ' ' ) ) != nullptr)
            {
                ptr2 = SkipSpaces( ptr2 );

                WriteJump( spisok, ptr2, strlen(ptr2) + 1 ); 
            
                ON_DEBUG( printf(YELLOW "writing jump, length of second metka: %ld\n" DELETE_COLOR, strlen(ptr2) + 1); )
            }
        }
        else 
        {
            continue; 
        }
        ON_DEBUG( printf("\n"); )
    }

    ON_DEBUG
    (
        printf(PURPLE "Result:\n" );
        printf("actual size: %d\n" DELETE_COLOR, spisok->amount);
        for (int i = 0; i < spisok->amount - 1; i++)
        {   
            printf(PURPLE "%d: %s\n" DELETE_COLOR, i, spisok->labels[i].name);
        }
        printf(GREEN "==End of preprocessing labels==\n" DELETE_COLOR);
    )
}


int WriteLabel(struct Label_table* spisok, char* ptr, size_t length)
{
    int status = 0;

    //=======Search to know if label name is new, not discovered yet=======
    for ( int i = 0; i < spisok->amount; i++ )
    {   
        if ( strncmp( spisok->labels[i].name, ptr, length ) == 0 )
        {
            status = 0;
            break;
        }
        else 
        {
            status = 1;
            continue;
        }
    }

    //====Search free space to write label name========
    if( status )
    {
        for ( int i = 0; i < spisok->amount; i++ )
        {
            if ( strlen( spisok->labels[i].name) == 0 )
            {
                snprintf(spisok->labels[i].name, length, "%s", ptr);
                spisok->amount++;
                return 1;
            }
            else
            {
                continue;
            }
        }
    }
    else 
    {
        return 0;
    }

    return -2; // kakoyto pizdec
}


int WriteJump(struct Label_table* spisok, char* ptr, size_t length)
{
    int status = 0;

    //====Simply writing name of label in next jump structure======
    for ( int i = 0; i < spisok->amount; i++ )
    {   
        if ( strncmp( spisok->labels[i].name, ptr, length ) == 0 )
        {
            (spisok->jumps + spisok->jump_count)->label = &spisok->labels[i];
            spisok->jump_count += 1;
            status = 0;
            break;
        }
        else 
        {
            status = 1;
            continue;
        }
    }

    if ( !status )
    {   
        return status;
    }
    else
    {
        printf(RED "No matching labels for this jump/call :(\n" DELETE_COLOR);
        return status;
    }
}


int GetArgJump(struct Output_buffer* output, Line_ptr* line, struct Label_table* spisok)
{
    char* buffer = SkipSpaces(line->start);
    buffer = SkipUntilSpace(buffer); //--> находим имя метки --> находим ей в массиве структур меток и берё её ip 
    buffer = SkipSpaces(buffer);

    Label* search = SearchLabel(spisok, buffer, strlen(buffer) );

        if( search )
        {   
            *(AssemblerElem*)(output->buffer + output->ip) = 0;

            FillArrayOfJumps( search, spisok, output->ip );              // запоминаем положение jump'а

            output->ip += sizeof( AssemblerElem );
            return 0;
        }
        else 
        {
            ON_DEBUG( printf("No such labels\n"); )
            return 1;
        }

    return -1;
}   


Label* SearchLabel( struct Label_table* spisok, char* ptr,  size_t length )
{
    ON_DEBUG( printf("Search labels:\n"); )

    //==============FIRST PATTERN=============================
    int status = 0;

    for ( int i = 0; i < spisok->amount; i++ )
    {   
        if ( strncmp( spisok->labels[i].name, ptr, length ) == 0 )
        {
            status = 1;
            ON_DEBUG( printf(PURPLE "Searching succes\n" DELETE_COLOR); )
            return &spisok->labels[i];
        }
        else 
        {
            status = 0;
            continue;
        }
    }
    if (!status)
    {
        ON_DEBUG( printf(PURPLE "searching failed\n" DELETE_COLOR); )
        return nullptr;
    }

    return nullptr;
}


void LabelDump(struct Label_table* spisok)
{
    printf(SINIY "\nDump of labels:\n" YELLOW);
    printf("amount of jumps: %d\n\n", spisok->jump_count);
    for (int i = 0; i < spisok->jump_count; i++ )
    {
        printf("%d: from: %d to  %s ip = %d\n", i, (spisok->jumps + i)->jump_ip, 
                                                   (spisok->jumps + i)->label->name, 
                                                   (spisok->jumps + i)->label->label_ip );
    }
    printf(DELETE_COLOR SINIY "===End of the dump===\n\n" DELETE_COLOR);
}


void FillArrayOfJumps(struct Label* label, struct Label_table* spisok, int ip)
{
    printf(GREEN "FILL ARRAY OF JUMPS:\n label -- %p ip=%d jump_count=%d" DELETE_COLOR, label, ip, spisok->jump_count );
    (spisok->jumps + spisok->filled_jump_count)->jump_ip = ip;
    spisok->filled_jump_count += 1;
}


