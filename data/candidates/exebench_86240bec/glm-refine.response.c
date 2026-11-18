char *__cdecl ft_strcpy(char *dst, const char *src)
{
    char *d = dst;

    do
    {
        *d++ = *src++;
    }
    while (*(d - 1)); // Equivalent to checking the copied character, breaking on '\0'

    return dst;
}