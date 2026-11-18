char *strcpy(char *dest, char *src)
{
    char *d = dest;
    char *s = src;

    while (1) {
        switch (*s) {
            case '\0':
                *d = '\0';
                return dest;
            default:
                *d++ = *s++;
        }
    }
}