bool wc_unescape(char *dst, const char *src) {
    bool result;

    while (*src != '\0') {
        if (*src == '\\') {
            src++;
            if (*src == '\0') {
                break;
            }
            if (dst != NULL) {
                *dst++ = *src;
            }
            src++;
        } else if (*src == '*' || *src == '?' || *src == '[' || *src == ']') {
            result = false;
            goto end;
        } else {
            if (dst != NULL) {
                *dst++ = *src;
            }
            src++;
        }
    }

    if (dst != NULL) {
        *dst = '\0';
    }
    result = true;

end:
    return result;
}