int func0(int n, int m, int mod) {
    int i, j, k, a[m + 1];
    for (i = 0; i <= m; i++)
        a[i] = 0;
    a[0] = 1;
    for (i = 1; i <= n; i++) {
        if (i < m)
            k = i;
        else
            k = m;
        for (j = k; j >= 1; j--)
            a[j] = (a[j] + a[j - 1]) % mod;
    }
    return a[m];
}