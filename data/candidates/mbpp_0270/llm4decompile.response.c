int func0(int *arr, int n) {
    int i, sum = 0;
    for (i = 0; i < n; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}