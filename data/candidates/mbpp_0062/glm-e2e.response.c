int func0(int *arr, int n) {
    int min = INT_MAX;  // 0x7fffffff
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}