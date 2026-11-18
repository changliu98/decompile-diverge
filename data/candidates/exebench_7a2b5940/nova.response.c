char *tcp_strflags(char *dest, int n) {
    int i;
    static int size = 8;
    static char *bits;
    char *s = dest;

    for (i = 0; i < size; i++) {
        if (n & (1 << i))
            *s++ = bits[i];
    }
    *s = '\0';
    return dest;
}