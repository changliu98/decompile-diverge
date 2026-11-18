char *str_cpy(char *dst, char *src)
{
    char *d = dst;
    while ((*d++ = *src++));
    return dst;
}