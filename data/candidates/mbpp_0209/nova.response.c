void func0(int *a, int n, int k, int *b) {
    int i;
    reverse(a, n);
    reverse(a, k);
    reverse(a, n - k);
    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }
}