char *func0(char *s) {
    int i, j, k;
    char t[100];
    int c[100];

    memset(c, 0, sizeof(c));
    memcpy(t, s, 80);
    for (i = 0; s[i];) {
        for (j = 0; j < 10; j++) {
            if (j == 9)
                t[j] = '\0';
            else
                t[j] = s[i]? s[i] :'';
            i++;
        }
        for (j = 0; j < 10; j++) {
            for (k = 0; t[k]; k++) {
                if (t[k] == a[k])
                    c[j]++;
            }
            c[j + 1] = c[j];
            c[j] = 0;
        }
    }
    for (i = 0; i < 10; i++)
        c[i + 1] = c[i];
    c[0] = 0;
    return c;
}