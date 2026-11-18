int func0(int **a, int n, int m, int k) {
    int i, j, sum = 0;
    for (i = 0; i < n; i++) {
        int sum1 = 0;
        for (j = 0; j < m; j++) {
            sum1 += a[i][j];
        }
        if (sum1 > 0)
            sum += (sum1 + k - 1) / k;
        else
            i++;
    }
    return sum;
}