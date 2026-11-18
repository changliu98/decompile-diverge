void func0(float *a, int n, float *b) {
    int i;
    for (i = 1; i < n; i++) {
        b[i - 1] = a[i] * i;
    }
}