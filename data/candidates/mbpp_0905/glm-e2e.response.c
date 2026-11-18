int func0(int n) {
    int numerator = factorial(n + 1, n * 2);
    int denominator = factorial(1, n);
    return numerator / denominator;
}