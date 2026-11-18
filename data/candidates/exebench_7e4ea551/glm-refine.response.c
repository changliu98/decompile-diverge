void __cdecl inplace_strcpy(char *to, const char *from)
{
    while (*from)
    {
        *to++ = *from++;
    }
    *to = *from;
}