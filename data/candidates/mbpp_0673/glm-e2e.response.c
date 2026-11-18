int func0(int *arr, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = result * 10 + arr[i];
    }
    return result;
}