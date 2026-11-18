void str_copy(char *dst, char *src)
{
    while (*src)
        *dst++ = *src++;
    *dst = 0;
}