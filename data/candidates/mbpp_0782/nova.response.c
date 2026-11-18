int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (i + 1) * (n - i) / 2 * arr[i];
    }
    return sum;
}