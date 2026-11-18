char *strncpy(char *dest, char *src, int n)
{
    char *s = src, *p = dest;
    int c;

    while ((c = (*s != 0) && n-- > 0))
        *p++ = *s++;
    *p = '\0';
    return dest;
}