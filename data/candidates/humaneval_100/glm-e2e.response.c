int* func0(int n) {
    int *arr = malloc(n * sizeof(int));
    arr[0] = n;
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + 2;
    }
    return arr;
}