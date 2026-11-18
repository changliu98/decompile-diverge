int func0(char *s) {
    int n = strlen(s);
    int c[n][n];
    int l, h, i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            c[i][j] = 0;
    for (l = 2; l <= n; l++) {
        for (i = 0; i < n - l + 1; i++) {
            h = i + l - 1;
            if (s[i] == s[h]) {
                if (l == 2)
                    c[i][h] = 2;
                else
                    c[i][h] = c[i + 1][h - 1] + 2;
            } else {
                c[i][h] = max(c[i + 1][h], c[i][h - 1]);
            }
        }
    }
    return c[0][n - 1];
}