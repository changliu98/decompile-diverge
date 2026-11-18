void func0(int *arr, int n, int *out) {
    qsort(arr, n, 4, cmpfunc);
    
    for (int i = 0; i < n; i++) {
        out[i] = arr[i];
    }
}