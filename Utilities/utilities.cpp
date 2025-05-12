#include "utilities.h"


void OpenFile(FileInfo* file_info, const char* filename)
{
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL)
    {
        wprintf(RED L"error\n" DELETE_COLOR);
        exit(1);   
    }

    FILE* file = fopen(filename, "r");  

    if (!file)
    {
        wprintf(RED "Error in opening file \"%s\" \n" DELETE_COLOR, filename);
        exit(1);
    }   

    struct stat info = {};                  // 
    stat (filename, &info);                 //
    size_t size = (size_t)info.st_size + 1; // find size
    file_info->size = size;                 //


    wchar_t* array = (wchar_t*)calloc(size, sizeof(wchar_t));   // read  
    char* char_array = (char*)calloc(2 * size, sizeof(char));   // read  
    fread(char_array, sizeof(char), 2 * size, file);                  // to array

    int read_bytes = 0, bytes_sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        read_bytes = mbtowc(array + i, char_array + bytes_sum, sizeof(wchar_t));
    
        if (!read_bytes)
            break;

        bytes_sum += read_bytes;
    }

    free(char_array);

    file_info->file = file;     // save structure
    file_info->code = array;    //
}


void CloseFile(FileInfo* file_info)
{
    fclose(file_info->file);
    free(file_info->code);
}


wchar_t* SkipNulls(wchar_t* ptr)
{
    while (*ptr == '\0')
        ptr ++;

    return ptr;
}

wchar_t* OverwriteSpaces(wchar_t* ptr)
{
    while (iswspace(*ptr))
    {
        *ptr = '\0';
        ptr++;
    }

    return ptr;
}
