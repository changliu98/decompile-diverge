int func0(int *a, int n, int *b, int m) {
    char c[1000] = {0};
    int i, j;
    for (i = 0; i < n; i++) {
        c[a[i]] = 1;
    }
    for (j = 0; j < m; j++) {
        if (c[b[j]] % 2!= 0) {
            return 0;
        }
    }
    return 1;
}