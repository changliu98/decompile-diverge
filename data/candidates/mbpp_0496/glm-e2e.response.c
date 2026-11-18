void func0(int *arr, int size, int n, int *out) {
    qsort(arr, size, sizeof(int), compare);
    
    for (int i = 0; i < n; i++) {
        out[i] = arr[i];
    }
}