void daxpy(int n, double a, double *x, double *y) {
    if (a == 0.0) {
        return;
    }

    if (a == 1.0) {
        while (--n >= 0) {
            y[n] += x[n];
        }
        return;
    }

    while (--n >= 0) {
        y[n] += a * x[n];
    }
}