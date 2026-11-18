int func0(int *arr, int n) {
    int sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += arr[i] * (n - i - 1) - arr[i] * (i);
    }
    return sum;
}