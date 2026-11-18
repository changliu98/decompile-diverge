long long func0(int n) {
    long long **arr = (long long **)malloc((n + 1) * sizeof(long long *));
    
    for (int i = 0; i <= n; i++) {
        arr[i] = (long long *)malloc((n + 1) * sizeof(long long));
        for (int j = 0; j <= n; j++) {
            arr[i][j] = 0;
        }
    }
    
    arr[0][0] = 1;
    
    for (int k = 1; k <= n; k++) {
        arr[k][0] = arr[k - 1][k - 1];
        for (int m = 1; m <= k; m++) {
            arr[k][m] = arr[k - 1][m - 1] + arr[k][m - 1];
        }
    }
    
    long long result = arr[n][0];
    
    for (int i = 0; i <= n; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return result;
}