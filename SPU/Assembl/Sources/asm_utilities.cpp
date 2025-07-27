
char* SkipSpaces(char* ptr)
{
    int i = 0;
    while( *(ptr + i) == ' ')
    {
        i++;
    }
    return ptr + i;
}


char* SkipUntilSpace( char* ptr )
{
    int i  = 0;
    while( *(ptr + i) != ' ' )
    {
        i++;
    }
    return ptr + i;
}
