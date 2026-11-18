void func0(int *arr, int n, int *sum) {
    int i = 0;
    while (i < n - 1) {
        sum[i] = arr[i] + arr[i + 1];
        i++;
    }
}