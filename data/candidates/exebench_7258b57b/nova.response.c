int UnicodeToUtf8(unsigned int c, char *s) {
    int n = 0;
    if (c < 0x80) {
        s[n++] = c;
    } else if (c < 0x800) {
        s[n++] = 0xc0 | (c >> 6);
        s[n++] = 0x80 | (c & 0x3f);
    } else if (c < 0x10000) {
        s[n++] = 0xe0 | (c >> 12);
        s[n++] = 0x80 | ((c >> 6) & 0x3f);
        s[n++] = 0x80 | (c & 0x3f);
    } else if (c < 0x110000) {
        s[n++] = 0xf0 | (c >> 18);
        s[n++] = 0x80 | ((c >> 12) & 0x3f);
        s[n++] = 0x80 | ((c >> 6) & 0x3f);
        s[n++] = 0x80 | (c & 0x3f);
    } else {
        s[n++] = '?';
    }
    s[n] = '\0';
    return n;
}