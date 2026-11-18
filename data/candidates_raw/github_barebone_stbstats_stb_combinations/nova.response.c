int func0(int n, int k, int **p) {
    int *a = (int *)calloc(k + 3, sizeof(int));
    int i, j, m, t;
    for (i = 0; i < k + 3; i++)
        a[i] = i;
    do {
        m = n;
        for (i = 1; i < k + 3; i++) {
            m = m * (n - a[i]) / (a[i - 1]);
            t = a[i];
            for (j = i; j > 0 && a[j - 1] > t; j--)
                a[j] = a[j - 1];
            a[j] = t;
        }
        *p = a;
    } while (i <= k);
    free(a);
    return m;
}