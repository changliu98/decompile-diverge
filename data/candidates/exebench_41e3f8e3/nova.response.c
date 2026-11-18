void table_norm(double *a, int n, double *b, int m, long long *c, int k) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (a[j] > b[i])
                c[i]++;
    for (i = 0; i < k; i++)
        if (c[i] == 0)
            c[i] = 1;
}