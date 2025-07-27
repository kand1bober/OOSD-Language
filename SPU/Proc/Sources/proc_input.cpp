#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"

void InputFileCode(struct File_proc* file, struct SPU* proc)
{
    printf("type number of file with programm\n");
    unsigned file_number = 0;
    scanf("%u", &file_number);
    
    printf("You chose:\n");
    switch( file_number )
    {
        case 0:
        {
            printf("PROGRAMM_ASM.txt\n"); 
            strcpy(file->name, "PROGRAMM_CODE.txt"); 
            break;
        }
        case 1:
        {
            printf("PROGRAMM_ASM_1.txt\n"); 
            strcpy(file->name, "PROGRAMM_CODE_1.txt"); 
            break;
        }
        case 2:
        {
            printf("PROGRAMM_ASM_2.txt\n");
            strcpy(file->name, "PROGRAMM_CODE_2.txt"); 
            break;  
        }
        case 3:
        {
            printf("PROGRAMM_ASM_3.txt\n");
            strcpy(file->name, "PROGRAMM_CODE_3.txt"); 
            break;  
        }
        default:
        {       

            break;
        }
    }

    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    //====OPEN FILE AND CREATE CHAR BUFFER===========
    FILE* input_file = fopen(filepath, "rb");

    struct stat file_info = {};

    stat(filepath, &file_info);

    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;
    // file->head.size_of_code = size_of_stream;/

    ON_DEBUG( printf("size of file: %lu\n", size_of_stream); )

    //=========READING_HEADER=====================
    fseek(input_file, sizeof(char) * 0L,  SEEK_SET);
    fread(&file->head, sizeof(file->head), 1, input_file);

    file->buffer = (char*)calloc(file->head.size_of_code, sizeof(char) );
    ON_DEBUG
    ( 
        printf("Header:\n"
            "author: %X\n"
            "size_of_code:%d\n"
            "version of coding: %d\n\n", file->head.sign, file->head.size_of_code, file->head.ver);

        printf("Position: %ld\n", ftell(input_file) );
    )

    fread( file->buffer, sizeof(char), file->head.size_of_code, input_file ); assert(fread);
    fclose(input_file);
   //====================================================
}

