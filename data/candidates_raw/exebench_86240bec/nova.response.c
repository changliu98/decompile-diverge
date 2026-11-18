char *func0(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++)!= '\0')
        ;
    return dest;
}