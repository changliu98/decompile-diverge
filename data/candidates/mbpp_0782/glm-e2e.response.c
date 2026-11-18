int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i] * ((i + 1) * (n - i) + 1) / 2;
    }
    return sum;
}