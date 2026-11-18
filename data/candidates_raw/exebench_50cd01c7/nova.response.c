void func0(double *x, double *y, double *z, int n, double *result) {
    double sum = 0.0;
    int i, j, k;

    for (i = 0, j = 1, k = 0; k < n; k++) {
        if (x[k] > x[i])
            j = k;
        if (j % 2 == 0)
            sum = x[k];
        else {
            double a, b, c, d, e, f;
            a = (x[j] - x[k]) / (x[j] - x[i]);
            b = (x[k] - x[i]) / (x[j] - x[i]);
            c = a * a * z[i] + b * b * z[j] - 2 * a * b * z[k];
            d = (x[j] - x[i]) / 2;
            e = (x[j] * x[j] - x[i] * x[i]) / 2;
            f = (x[j] * x[j] * x[i] - x[i] * x[i] * x[j]) / 2;
            sum += c * (y[k] - (d * z[k] + e + f));
        }
        i = j++;
    }
    *result = sum;
}