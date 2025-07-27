#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h> 
#include <cwchar> 
#include <wctype.h>
#include <locale.h>

#include "../Common/keywords.h"

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
    wchar_t* buf;
    int size;
} BufferInfo;

typedef struct
{   
    FILE* file;
    BufferInfo buffer_info;
} FileInfo;

void OpenFile(FileInfo* file_info, const char* filename, const char* mode);
void CloseFile(FileInfo* file_info);

wchar_t* SkipNulls(wchar_t* ptr);
wchar_t* OverwriteSpaces(wchar_t* ptr);

const wchar_t* KeyWordStrVal(int64_t keycode);
const wchar_t* KeyWordHTMLVal(int64_t keycode);

void BufAppendBuf(BufferInfo* buf, BufferInfo* to_add);
void BufAppendStr(BufferInfo* buf, const wchar_t* to_add);

#endif 

