char *string_copy(char *dest, const char *src)
{
    char *d = dest;
    const char *s = src;

    if (dest == NULL || src == NULL)
        return NULL;

    while (*s != '\0') {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';

    return dest;
}