double func0(int n, int k, double p) {
    int i, j, l;
    double sum1, sum2, sum3, sum4;
    l = k;
    if (k > n / 2)
        k = n - k;
    sum1 = 1.0;
    for (i = 1; i <= k; i++) {
        sum1 = sum1 * (n - k + i) / i;
        sum1 = sum1 / i;
    }
    sum2 = sum1 * pow(p, l) * pow(1 - p, n - l);
    return sum2;
}