void func0(double *y, int n, double *func0, double a, double b, int flag) {
    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
    int i;
    for (i = 1; i <= n; i++) {
        sum1 += y[i - 1];
        if (flag == 0) {
            sum2 += y[i - 1] * (n - i);
            sum3 += y[i - 1] * (n - i) * (n - i - 1);
        }
        if (flag == 1) {
            sum2 += y[i - 1] * (i - 1);
            sum3 += y[i - 1] * (i - 1) * (i - 2);
        }
    }
    func0[0] = sum1 / n;
    func0[1] = sum2 / n / (n - 1);
    func0[2] = sum3 / n / (n - 1) / (n - 2);
}