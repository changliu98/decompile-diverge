double func0(double x, double y) {
    double a, b, c, d;
    a = -0.5 * y;
    b = x * y;
    c = -10 * x;
    d = pow(a + b, 2) + pow(c + b, 2);
    return d;
}