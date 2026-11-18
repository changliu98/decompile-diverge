int func0(int *arr, int n) {
    int i, func0 = 1;
    for (i = 0; i < n; i++) {
        func0 *= arr[i];
    }
    return func0;
}