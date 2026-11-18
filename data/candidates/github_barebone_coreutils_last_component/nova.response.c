static const char *last_component(const char *path) {
    const char *p = path;
    const char *q;
    bool slash = false;

    while (1) {
        while (*p == '/') {
            p++;
        }
        q = p;
        while (*q!= '\0' && *q!= '/') {
            q++;
        }
        if (slash) {
            return p;
        }
        if (*q == '\0') {
            break;
        }
        p = q;
        slash = true;
    }
    return p;
}