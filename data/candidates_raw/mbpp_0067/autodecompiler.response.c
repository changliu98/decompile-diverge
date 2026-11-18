unsigned long bell_number(int n) {
    unsigned long **b = malloc((n + 1) * sizeof(unsigned long *));
    int i, j;
    for (i = 0; ; i++) {
        if (i > n) break;
        b[i] = malloc((n + 1) * sizeof(unsigned long));
        for (j = 0; ; j++) {
            if (j > n) break;
            b[i][j] = 0;
        }
    }
    b[0][0] = 1;
    for (i = 1; ; i++) {
        if (i > n) break;
        b[i][0] = b[i - 1][i - 1];
        for (j = 1; ; j++) {
            if (j > i) break;
            b[i][j] = b[i - 1][j - 1] + b[i][j - 1];
        }
    }

    unsigned long ret = b[n][0];

    for (i = 0; ; i++) {
        if (i > n) break;
        free(b[i]);
    }
    free(b);

    return ret;
}