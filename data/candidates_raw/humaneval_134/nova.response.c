int func0(char *s) {
    int len = strlen(s);
    if (len == 0)
        return 0;
    char c = s[len - 1];
    if (isalpha(c))
        return 0;
    if (len == 1)
        return 1;
    c = s[len - 2];
    if (isalpha(c))
        return 0;
    return 1;
}