#include "utilities.h"


void OpenFile(FileInfo* file_info, const char* filename, const char* mode)
{
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL)
    {
        wprintf(RED L"error\n" DELETE_COLOR);
        exit(1);   
    }

    FILE* file = fopen(filename, mode);  

    if (!file)
    {
        wprintf(RED "Error in opening file \"%s\" \n" DELETE_COLOR, filename);
        exit(1);
    }   

    switch (*mode)
    {
        case 'r':
        {
            struct stat info = {};                  // 
            stat (filename, &info);                 //
            size_t size = (size_t)info.st_size + 1; // find size
            file_info->buffer_info.size = size;                 //

            wchar_t* array = (wchar_t*)calloc(size, sizeof(wchar_t));   // read  
            char* char_array = (char*)calloc(size, sizeof(char));   // read  
            fread(char_array, sizeof(char), size, file);    // to array

            int read_bytes = 0, bytes_sum = 0;
            for (size_t i = 0; i < size; i++)
            {
                read_bytes = mbtowc(array + i, char_array + bytes_sum, sizeof(wchar_t));
            
                if (!read_bytes)
                    break;

                bytes_sum += read_bytes;
            }
            
            free(char_array);
            
            file_info->buffer_info.buf = array;    

            break;
        }
        case 'w':
        {
            break;
        }
        default:
        {
            printf("\nError in opening file for writing\n");
        }
    }
    
    file_info->file = file;     // save structure
}


void CloseFile(FileInfo* file_info)
{
    fclose(file_info->file);
    free(file_info->buffer_info.buf);
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


const wchar_t* KeyWordStrVal(int64_t keycode)
{   
    for (int i = 0; i < kKeyWordsAmount; i++)
    {       
        if (keycode == (int64_t)keyword_table[i].key_code)
        {
            return keyword_table[i].C_key_word;
        }
    }

    return L"huy";
}


const wchar_t* KeyWordHTMLVal(int64_t keycode)
{
    for (int i = 0; i < kKeyWordsAmount; i++)
    {       
        if (keycode == (int64_t)keyword_table[i].key_code)
        {
            return keyword_table[i].html_entity;
        }
    }

    return L"huy";
}


void BufferAppend(BufferInfo* buf, BufferInfo* to_add)
{
    buf->buf = (wchar_t*)realloc(buf->buf, (buf->size + to_add->size) * 4);
    swprintf(buf->buf + buf->size + 1, to_add->size, L"%ls", to_add->buf);
    buf->size += to_add->size;

    if (!buf->buf)
    {
        wprintf(RED L"Error in allocating memory for BufferAppend\n" DELETE_COLOR);
        exit(1);
    }
}
