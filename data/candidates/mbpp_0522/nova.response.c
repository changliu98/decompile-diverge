int func0(int *a, int n) {
    int i, j, k, l;
    int b[n + 1], c[n + 1];
    for (i = 0; i < n; i++) {
        b[i] = 1;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (a[i] > a[j] && b[i] < b[j] + 1) {
                b[i] = b[j] + 1;
            }
        }
    }
    for (i = n - 1; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (a[i] > a[j] && c[i] < c[j] + 1) {
                c[i] = c[j] + 1;
            }
        }
    }
    k = b[0] + c[0] - 1;
    for (i = 1; i < n; i++) {
        if (k < b[i] + c[i] - 1) {
            k = b[i] + c[i] - 1;
        }
    }
    return k;
}