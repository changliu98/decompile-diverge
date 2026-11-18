int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; 2 * i + 1 < n; i++) {
        if (arr[2 * i + 1] % 2 == 0) {
            sum += arr[2 * i + 1];
        }
    }
    return sum;
}