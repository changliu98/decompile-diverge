int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (i % 3 == 0) {
            sum += arr[i] * arr[i];
        } else if (i % 4 == 0) {
            sum += arr[i] * arr[i] * arr[i];
        } else {
            sum += arr[i];
        }
    }
    return sum;
}