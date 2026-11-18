void func0(int *a, int n, int *b, int m, int *c) {
    int i = 0, j = 0;
    while (i < n - 1) {
        c[i] = a[i];
        i++;
    }
    while (j < m) {
        c[n - 1 + j] = b[j];
        j++;
    }
}