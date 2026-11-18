static char *func0(const char *s, int len) {
    static char buf[21];
    char *p = buf;
    int i = 1;
    while (1) {
        if (i <= 6) {
            snprintf(p, 21 - (buf - p), "%%%02x", (unsigned char)s[i++]);
            p += strlen(p);
            if (i == 2 || i == 4)
                *p++ = '.';
        } else {
            if (len >= 8) {
                snprintf(p, 21 - (buf - p), "%%%02x", (unsigned char)s[i++]);
                p += strlen(p);
                if (i == len)
                    snprintf(p, 21 - (buf - p), "%%%02x", (unsigned char)s[i++]);
            } else {
                snprintf(p, 21 - (buf - p), "%%%02x", (unsigned char)s[i++]);
            }
            break;
        }
    }
    return buf;
}