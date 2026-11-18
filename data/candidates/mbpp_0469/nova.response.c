int func0(int *a, int n, int m) {
    int i, j, k, max;
    int b[n][m + 1];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < j; k++) {
                max = b[i][k] > b[i][j] - a[i]? b[i][k] : b[i][j] - a[i];
                if (max < b[i][j])
                    max = b[i][j];
                else
                    max = b[i][j - 1];
            }
            b[i][j] = max;
        }
    }
    return b[n - 1][m];
}