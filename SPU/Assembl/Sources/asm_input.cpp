
#include "../Headers/asm_macros.h"
#include "../Headers/asm_functions.h"


//======READING TO THE char* BUFFER=======
void InputFileStruct(struct File_asm* file)
{
    // printf("name: %s\n", file->name);

    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    FILE* stream = fopen(filepath, "r");

    struct stat file_info = {};
    stat(filepath, &file_info);

    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;
    ON_DEBUG( printf("size of file: %lu\n", size_of_stream); )

    file->size_of_file = size_of_stream;

    file->buffer = (char*)calloc( size_of_stream + 1, sizeof(char) );

    fseek(stream, sizeof(char) * 0L,  SEEK_SET);
    fread( (void*)file->buffer, sizeof(char), size_of_stream, stream);
    fclose(stream);

    CreateLinePointers(file);
    CountManAndArg(file);

    printf("amount of lines: %d\nsize of code: %d\n", file->lines_amount, file->size_of_code);

    ON_DEBUG
    (
        printf("Strings printed by pointers to them:\n");
        for(int i = 0; i < file->lines_amount; i++)
        {
            printf("%3d:  %-13s   length: %d\n", i , file->lines_arr[i].start, file->lines_arr[i].length);
        }
        printf("\n\n");
    )
}
//=================================================


//=========Creating pointers to strings============
void CreateLinePointers(struct File_asm* file)
{   
    for(int i = 0; i < file->size_of_file; i++)
    {
        if ( file->buffer[i] == '\n' )  
        {
            file->buffer[i] = '\0';
            (file->lines_amount)++;
        }
        //TODO:  пропуск пустой строки 
    }

    file->lines_arr = (struct Line_ptr*)calloc( file->lines_amount + 1, sizeof( *file->lines_arr ) );
    file->lines_arr[0].start = file->buffer;
    file->lines_arr[0].length = strlen(file->lines_arr->start);

    for(int i = 0, g = 1; g < file->lines_amount; i++)
    {
        if ( file->buffer[i] == '\0' )
        {   
            file->lines_arr[g].start = &file->buffer[ ++i ];
            file->lines_arr[g].length = strlen( file->lines_arr[g].start );
            g++;
        }
    }
}

void CountManAndArg(struct File_asm* file)
{
    file->size_of_code = file->lines_amount;

    for(int i = 0; i < file->lines_amount; i++)
    {
        for( int count = 0; count < file->lines_arr[i].length - 1; count++)
        {
            if( *( file->lines_arr[i].start + count ) == ' ' )
            {
                file->size_of_code++;
                break;
            }
            else 
            {
                continue;
            }
        }
    }
}
