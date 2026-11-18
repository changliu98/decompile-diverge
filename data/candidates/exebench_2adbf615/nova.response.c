void daxpy(int n, double x, double *p, double *dp) {
    if (x == 0)
        return;
    if (x == a[n - 1]) {
        while (n--)
            dp[n] += p[n];
        return;
    }
    while (n--)
        dp[n] += x * p[n];
}