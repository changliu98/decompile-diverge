char* __cdecl strcpy4(char *s, char *t)
{
    char *dest = s;

    do
    {
        *dest++ = *t;
    }
    while (*t++);

    return s;
}