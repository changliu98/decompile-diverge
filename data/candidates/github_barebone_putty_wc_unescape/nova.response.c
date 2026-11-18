static bool wc_unescape(char *dst, const char *src) {
    bool ret = false;

    while (*src) {
        if (*src == '\\') {
            src++;
            if (*src) {
                if (dst)
                    *dst++ = *src;
                src++;
            }
        } else if (*src == '*' || *src == '?' || *src == '[' || *src == ']') {
            ret = true;
            break;
        } else {
            if (dst)
                *dst++ = *src;
            src++;
        }
    }

    if (dst)
        *dst = '\0';

    return ret;
}