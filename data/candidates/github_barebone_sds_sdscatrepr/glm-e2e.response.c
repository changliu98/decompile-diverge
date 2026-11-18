char *sdscatrepr(char *s, const char *str, unsigned long len) {
    s = sdscatlen(s, "\"", 1);
    while (len--) {
        char c = *str;
        switch (c) {
            case '\\':
            case '"':
                s = sdscatprintf(s, "\\%c", c);
                break;
            case '\n':
                s = sdscatlen(s, "\\n", 2);
                break;
            case '\r':
                s = sdscatlen(s, "\\r", 2);
                break;
            case '\t':
                s = sdscatlen(s, "\\t", 2);
                break;
            case '\a':
                s = sdscatlen(s, "\\a", 2);
                break;
            case '\b':
                s = sdscatlen(s, "\\b", 2);
                break;
            default:
                if (isprint(c)) {
                    s = sdscatprintf(s, "%c", c);
                } else {
                    s = sdscatprintf(s, "\\x%02x", (unsigned char)c);
                }
                break;
        }
        str++;
    }
    return sdscatlen(s, "\"", 1);
}