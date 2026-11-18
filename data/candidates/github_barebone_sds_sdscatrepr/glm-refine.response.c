sds __cdecl sdscatrepr(sds s, const char *p, size_t len) {
    sds sa = sdscatlen(s, "\"", 1);
    
    while (len--) {
        unsigned char c = *p;
        switch (c) {
            case '\a': // 7
                sa = sdscatlen(sa, "\\a", 2);
                break;
            case '\b': // 8
                sa = sdscatlen(sa, "\\b", 2);
                break;
            case '\t': // 9
                sa = sdscatlen(sa, "\\t", 2);
                break;
            case '\n': // 10
                sa = sdscatlen(sa, "\\n", 2);
                break;
            case '\r': // 13
                sa = sdscatlen(sa, "\\r", 2);
                break;
            case '\\': // 92
            case '\"': // 34
                sa = sdscatprintf(sa, "\\%c", c);
                break;
            default:
                if (isprint(c))
                    sa = sdscatprintf(sa, "%c", c);
                else
                    sa = sdscatprintf(sa, "\\x%02x", c);
                break;
        }
        p++;
    }
    
    return sdscatlen(sa, "\"", 1);
}