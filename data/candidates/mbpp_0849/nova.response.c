int func0(int n) {
    int a[n + 1], i, j, k;
    for (i = 0; i <= n; i++)
        a[i] = 0;
    for (i = 2; i <= n; i++) {
        if (a[i] == 0) {
            for (j = i; j <= n; j = j + i) {
                if (a[j] == 0)
                    a[j] = i;
            }
        }
    }
    return a[n];
}