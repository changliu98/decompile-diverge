void ZVdotC11(int n, double *x, double *y, double *out) {
    double sum1 = 0.0;
    double sum2 = 0.0;
    int i, j;
    for (i = 0, j = 1; j < n; i += 2, j += 2) {
        double a = x[i];
        double b = x[j];
        double c = y[i];
        double d = y[j];
        sum1 += (a * d + b * c);
        sum2 += (a * c - b * d);
    }
    out[0] = sum1;
    out[1] = sum2;
}