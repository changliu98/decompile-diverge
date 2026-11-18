int func0(int *arr, int n) {
    int result = 0;
    for (int i = n - 1; i >= 0; i--) {
        result += arr[i] * i - arr[i] * (n - 1 - i);
    }
    return result;
}