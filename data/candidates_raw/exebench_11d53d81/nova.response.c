void func0(double x, double y, double *a, double *b, double *c, double *d) {
    double a1, b1, c1;
    a1 = y * x;
    b1 = a1 + b[0];
    c1 = b1 + c[0];
    d[0] = c1 + a1 * x;
    a[0] = b1 + c1 * x;
    b[0] = c1 * x;
    c[0] = d[0] * x;
}