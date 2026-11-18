void r3sums(double x[3], double y[3], double a, double b) {
    x[0] = a * y[0] + b * y[1];
    x[1] = a * y[1] + b * y[2];
    x[2] = a * y[2] + b * y[0];
}