static void func0(unsigned long x, char *s, int digits) {
    static const char *hex = "0123456789ABCDEF";
    char c, *p = s;
    int i;

    c = 0;
    i = 1;
    while (digits-- > 8) {
        *p++ = hex[(x & 15)];
        x >>= 4;
        i++;
    }
    while (i) {
        *p++ = hex[(x & 15)];
        x >>= 4;
        i--;
    }
    while (p) {
        *p++ = hex[(x & 15)];
        x >>= 4;
    }
}