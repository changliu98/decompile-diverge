char *sdscatrepr(char *str, char *s, unsigned long len) {
    str = sdscatlen(str, "\"", 1);
    while (len--) {
        int c = *s;
        switch (c) {
            case '\a': str = sdscatlen(str, "\\a", 2); break;
            case '\b': str = sdscatlen(str, "\\b", 2); break;
            case '\t': str = sdscatlen(str, "\\t", 2); break;
            case '\n': str = sdscatlen(str, "\\n", 2); break;
            case '\r': str = sdscatlen(str, "\\r", 2); break;
            case '\"':
            case '\\': str = sdscatprintf(str, "\\%c", *s); break;
            default:
                if (((*__ctype_b_loc ())[(int) ((*s))] & (unsigned short) _ISprint))
                    str = sdscatprintf(str, "%c", *s);
                else
                    str = sdscatprintf(str, "\\x%02x", *s);
        }
        s++;
    }
    return sdscatlen(str, "\"", 1);
}