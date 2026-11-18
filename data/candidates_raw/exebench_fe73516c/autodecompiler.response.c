char *strcpy(char *dest, char *src)
{
    char *save = dest;
    for (;;) {
        *dest = *src;
        switch (*dest) {
        case '\0':
            return save;
        default:
            ++src, ++dest;
        }
    }
}