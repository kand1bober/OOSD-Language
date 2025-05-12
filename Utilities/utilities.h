#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h> 
#include <cwchar> 
#include <wctype.h>
#include <locale.h>

#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#define DELETE_COLOR L"\u001b[0m"
#define BLACK        L"\u001b[30m"
#define RED          L"\u001b[31;1m"
#define ORANGE       L"\033[93m"
#define GREEN        L"\u001b[32;1m"
#define YELLOW       L"\u001b[33;1m"
#define SINIY        L"\u001b[34m"
#define PURPLE       L"\u001b[35;1m"
#define BLUE         L"\033[96m"
#define WHITE        L"\u001b[37;1m"

#define kSizeOfCyrillic 2

typedef struct
{   
    FILE* file;
    wchar_t* code;
    size_t size;
} FileInfo;

void OpenFile(FileInfo* file_info, const char* filename);
void CloseFile(FileInfo* file_info);

wchar_t* SkipSpaces(wchar_t* ptr);

#endif 

