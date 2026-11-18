unsigned int StrSafeCopy(char *dest, char *src, unsigned int length)
{
    char *d = dest;
    char *s = src;
    unsigned int size = length;

    if (size && --size) {
        do {
            if (!(*d++ = *s++)) {
                break;
            }
        } while (--size);
    }

    if (!size) {
        if (length) {
            *d = '\0';
        }
        while (*s++);
    }

    return s - src - 1;
}