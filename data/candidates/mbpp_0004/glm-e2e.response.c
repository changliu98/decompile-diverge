void func0(int *arr, int n, int k, int *out) {
    qsort(arr, (long)n, 4, compare);
    for (int i = 0; i < k; i++) {
        out[i] = arr[i];
    }
}