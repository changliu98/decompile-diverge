void c_saxpy(int n, double a, double *x, double *y) {
    if (n <= 0 || a == 0.0) {
        return;
    }

    int rem = n % 4;

    // Scalar remainder loop
    for (int i = 1; i <= rem; i++) {
        y[i - 1] += a * x[i - 1];
    }

    // Unrolled vector loop (processes 4 elements per iteration)
    for (int i = rem + 1; i <= n; i += 4) {
        y[i - 1] += a * x[i - 1];
        y[i]     += a * x[i];
        y[i + 1] += a * x[i + 1];
        y[i + 2] += a * x[i + 2];
    }
}