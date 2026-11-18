int func0(double *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (int)round(arr[i]);
    }
    return sum * n;
}