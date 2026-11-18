int func0(int *a, int n, int *b, int m) {
    int i, j, k = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                k++;
                break;
            } else
                continue;
        }
    }
    return k;
}