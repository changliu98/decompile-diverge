static int func0(const char *s, size_t n, int *result) {
    int c;

    if (n == 0 || *s == '\0') {
        if (result)
            *result = 0;
        c = -1;
    } else if ((*s & 0x80) == 0) {
        if (result)
            *result = 1;
        c = *s & 0x7f;
    } else if ((*s & 0xe0) == 0xc0) {
        if (result)
            *result = 2;
        if (n < 2 || s[1] == '\0') {
            c = -1;
        } else {
            c = ((*s & 0x1f) << 6) | (s[1] & 0x3f);
        }
    } else if ((*s & 0xf0) == 0xe0) {
        if (result)
            *result = 3;
        if (n < 3 || s[1] == '\0' || s[2] == '\0') {
            c = -1;
        } else {
            c = ((*s & 0x0f) << 12) | ((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
        }
    } else if ((*s & 0xf8) == 0xf0) {
        if (result)
            *result = 4;
        if (n < 4 || s[1] == '\0' || s[2] == '\0' || s[3] == '\0') {
            c = -1;
        } else {
            c = ((*s & 0x07) << 18) | ((s[1] & 0x3f) << 12) |
                ((s[2] & 0x3f) << 6) | (s[3] & 0x3f);
        }
    } else {
        if (result)
            *result = 0;
        c = -1;
    }

    return c;
}