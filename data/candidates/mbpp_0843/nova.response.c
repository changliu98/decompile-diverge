long long func0(int n, int *a, int m) {
    long long *c = (long long *)malloc(n * sizeof(long long));
    long long *t = (long long *)calloc(m, sizeof(long long));
    long long *p = (long long *)malloc(m * sizeof(long long));
    int i, j;
    c[0] = 1;
    for (i = 0; i < m; i++) {
        p[i] = a[i];
    }
    for (i = 1; i < n; i++) {
        long long max = p[0];
        for (j = 1; j < m; j++) {
            if (p[j] > max)
                max = p[j];
        }
        c[i] = max;
        for (j = 0; j < m; j++) {
            if (p[j] == max) {
                p[j] = c[i] + 1;
                p[j] *= a[j];
                break;
            }
        }
    }
    long long result = c[n - 1];
    free(c);
    free(t);
    free(p);
    return result;
}