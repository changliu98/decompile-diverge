bool func0(int *arr, int n, int sum) {
    if (sum == 0)
        return true;
    if (n == 0)
        return false;
    if (arr[n - 1] > sum)
        return func0(arr, n - 1, sum) & func0(arr, n - 1, sum - arr[n - 1]);
    else
        return func0(arr, n - 1, sum) | func0(arr, n - 1, sum - arr[n - 1]);
}