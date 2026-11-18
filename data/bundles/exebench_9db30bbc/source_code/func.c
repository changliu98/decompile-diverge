
char* stdimpl_strcpy(char *dst, const char *src)
{
    char *start = dst;
    char c;
    do {
        c = *src;
        *dst = c;
        src++;
        dst++;
    } while (c);
    return start;
}
