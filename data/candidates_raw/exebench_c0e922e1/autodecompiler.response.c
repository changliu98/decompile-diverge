char *strcpy(char *dest, char *src)
{
    char *d = dest;
    while (1) {
        switch (*src) {
            case '\0':
                *d = '\0';
                return dest;
            default:
                *d++ = *src++;
        }
    }
}