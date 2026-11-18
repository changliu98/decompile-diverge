char *__cdecl strset(char *str, int c)
{
    char *s = str;
    
    while (*s)
    {
        *s = (char)c;
        s++;
    }
    
    return str;
}