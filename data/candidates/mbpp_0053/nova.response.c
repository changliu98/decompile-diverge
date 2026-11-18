char *func0(char *s) {
    int len = strlen(s);
    char *p;
    if (s[0] == s[len - 1])
        p = "=";
    else
        p = "!";
    return p;
}