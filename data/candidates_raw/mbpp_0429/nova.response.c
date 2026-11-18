void func0(int *a, int *b, int *c, int n) {
    int i = 0;
    for (; i < n; i++) {
        c[i] = a[i] & b[i];
    }
}