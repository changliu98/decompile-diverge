char *func0(int n, int k) {
    static char s[10000];
    static char t[10000];
    int i, j;
    sprintf(s, "%d", n);
    i = strlen(s);
    if (i < k) {
        for (j = 0; j < i / 2; j++) {
            t[j] = s[j];
            s[j] = s[i - 1 - j];
            s[i - 1 - j] = t[j];
        }
    } else {
        strcpy(t, s + i - k);
        t[k] = '\0';
        strcpy(s, t);
    }
    return s;
}