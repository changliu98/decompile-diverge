char *func0(const char *s) {
    size_t len = strlen(s);
    char *p = (char *)malloc(len + 1);
    if (p == NULL) {
        return NULL;
    }
    if (len > 0) {
        size_t i;
        p[0] = toupper(s[0]);
        for (i = 1; i < len; i++) {
            p[i] = tolower(s[i]);
        }
        p[len - 1] = toupper(s[len - 1]);
    }
    p[len] = '\0';
    return p;
}