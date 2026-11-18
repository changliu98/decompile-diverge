void func0(int *a, int n, int *out) {
    for (int i = 0; i < n - 1; i++) {
        out[i] = a[i] + a[i + 1];
    }
}