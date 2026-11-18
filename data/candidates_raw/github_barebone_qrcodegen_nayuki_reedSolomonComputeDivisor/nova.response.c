void func0(int n, char *x) {
    int i, j;
    char t;
    assert(1 <= n && n <= 30);
    memset(x, 0, n);
    x[n - 1] = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[j] = f(x[j], t);
            if (j + 1 < n)
                x[j + 1] ^= x[j];
        }
        t = f(t, 2);
    }
}