char *strcpy2(char *dest, const char *src)
{
    char *p = dest;
    while ((*p++ = *src++));
    return dest;
}