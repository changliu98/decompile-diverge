void func0(int *arr, int n, int k, int *res, int *len) {
    int i, j = 0;
    for (i = 0; i < n; i += k) {
        res[j++] = arr[i];
    }
    *len = j;
}