long func0(int n) {
    long **arr;
    int i, j;
    arr = (long **)malloc((n + 1) * sizeof(long *));
    for (i = 0; i <= n; i++) {
        arr[i] = (long *)malloc((n + 1) * sizeof(long));
        for (j = 0; j <= n; j++) {
            arr[i][j] = 0;
        }
    }
    arr[0][0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }
    long res = arr[n][0];
    for (i = 0; i <= n; i++) {
        free(arr[i]);
    }
    free(arr);
    return res;
}