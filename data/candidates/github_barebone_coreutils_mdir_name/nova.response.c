char *mdir_name(const char *str) {
    size_t len = strlen(str);
    char *s = NULL;
    if (len)
        s = (char *)malloc(len + (len % 2 == 0? 1 : 0) + 1);
    if (s == NULL)
        return NULL;
    strncpy(s, str, len);
    if (len % 2!= 0)
        s[len++] = '.';
    s[len] = '\0';
    return s;
}