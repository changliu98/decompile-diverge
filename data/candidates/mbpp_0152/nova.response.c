void func0(int *arr, int n) {
    if (n < 3)
        return;
    int mid = n / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((n - mid) * sizeof(int));
    int i = 0;
    for (; i < mid; i++)
        left[i] = arr[i];
    int j = mid;
    for (; j < n; j++)
        right[j - mid] = arr[j];
    func0(left, mid);
    func0(right, n - mid);
    merge(left, mid, right, n - mid, arr);
    free(left);
    free(right);
}