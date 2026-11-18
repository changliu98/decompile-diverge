double func0(double x, int n) {
    double f;
    f = 1 / (1 + pow(x, n)) * (1 - pow(x, n)) / (1 - 2 * x);
    return f;
}