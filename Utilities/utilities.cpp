#include "utilities.h"

// char* GeyFilePath(char* filepath, )
// {
//     sprintf(filepath, "", );

//     return path;
// }


void OpenFile(FileInfo* file_info, char* filename)
{
    FILE* file = fopen("../filename", "r");

    if (!file)
    {
        printf(RED "Error in opening file\n" DELETE_COLOR);
        exit(1);
    }   

    struct stat info = {};
    stat ("../filename", &info);
    size_t size = (size_t)info.st_size + 1;
    file_info->size = size;

    char* array = (char*)calloc(size, sizeof(char));

    fread(array, 1, size, file_info->file);

    file_info->code = array;
}


void CloseFile(FileInfo* file_info)
{
    fclose(file_info->file);
    free(file_info->code);

    if (file_info->file || file_info->code)
    {
        printf(RED "Error in closing file\n" DELETE_COLOR);
        exit(1);
    }
}


char* SkipSpaces(char* str)
{
    while(*str == ' ' || *str == '\t' || *str == '\n')
    {
        str++;
    }

    return str;
}
