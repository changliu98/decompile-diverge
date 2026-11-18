int func0(int *arr, int n, int m) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result = (result * (arr[i] % m)) % m;
    }
    return result % m;
}