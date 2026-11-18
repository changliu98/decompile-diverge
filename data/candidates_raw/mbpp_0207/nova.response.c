int func0(char *s) {
    int n = strlen(s);
    int i, j, k;
    int **c = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        c[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++) {
        c[i][i] = 0;
    }
    for (k = 1; k < n; k++) {
        for (i = 0; i < n - k; i++) {
            j = i + k;
            if (s[i] == s[j]) {
                c[i][j] = c[i + 1][j - 1];
            } else {
                c[i][j] = min(c[i + 1][j], c[i][j - 1]) + 1;
            }
        }
    }
    return c[0][n - 1];
}