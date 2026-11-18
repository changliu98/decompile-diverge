double func0(int n, double theta) {
    double a = n * n * pow(sin(theta), 2);
    double b = 40.0 * pow(sin(theta / 2.0), 2);
    return a / b;
}