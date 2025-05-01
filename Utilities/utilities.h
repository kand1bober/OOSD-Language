#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#define DELETE_COLOR "\u001b[0m"
#define BLACK "\u001b[30m"
#define RED "\u001b[31;1m"
#define ORANGE "\033[93m"
#define GREEN "\u001b[32;1m"
#define YELLOW "\u001b[33;1m"
#define SINIY "\u001b[34m"
#define PURPLE "\u001b[35;1m"
#define BLUE "\033[96m"
#define WHITE "\u001b[37;1m"

typedef struct
{   
    FILE* file;
    wchar_t* code;
    size_t size;
} FileInfo;

void OpenFile(FileInfo* file_info, const char* filename);
void CloseFile(FileInfo* file_info);

void SkipSpaces(wchar_t* str);

#endif 

