static char *
mystpcpy(char *dst, const char *src)
{
    *dst = *src;
    while (*dst)
    {
        dst++;
        src++;
    }
    return dst;
}