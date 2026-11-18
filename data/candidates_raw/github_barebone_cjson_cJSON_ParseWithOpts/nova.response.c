char *func0(char *s, char *t, int n) {
    char *result;
    if (s == (char *)0)
        result = (char *)0;
    else {
        size_t len = strlen(s);
        result = (char *)alloca(len + 1);
        strncpy(result, s, n);
    }
    return result;
}