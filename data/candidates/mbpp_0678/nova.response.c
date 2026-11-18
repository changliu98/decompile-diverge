char *func0(char *s) {
    int i, j;
    j = 0;
    int len = strlen(s);
    for (i = 0; i < len; i++) {
        if (s[i]!='') {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
    return s;
}