char *func0(char *dest, const char *src, int count) {
    int i;
    char *tmp = dest;

    for (i = count; --i >= 0 && (*dest++ = *src++)!= 0;)
        ;
    while (i-- > 0)
        *dest++ = 0;
    return tmp;
}