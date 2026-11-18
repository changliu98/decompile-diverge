char *__cdecl my_strcpy(char *dest, const char *src)
{
    int i = 0;

    // Copy characters until the null terminator is reached
    for (; src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    // Append the null terminator
    dest[i] = '\0';

    return dest;
}