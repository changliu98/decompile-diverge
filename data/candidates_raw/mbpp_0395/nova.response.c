char func0(char *s) {
    int i, j, k, l, m, n;
    int a[256];
    char b[1024];
    char c;

    memset(a, 0, sizeof(a));
    n = strlen(s);
    for (i = j = 0; i < n; i++) {
        c = s[i];
        if (a[c] == 0) {
            b[j++] = c;
            a[c]++;
        }
    }

    for (i = 0; i < j; i++) {
        c = b[i];
        if (a[c] == 1)
            return c;
    }

    return '\0';
}