void func0(int *arr, int n, int *out) {
    out[0] = arr[n - 1];
    for (int i = 1; i < n; i++) {
        out[i] = arr[i - 1];
    }
}