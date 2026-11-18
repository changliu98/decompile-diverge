int func0(int n) {
    if (n < 0) {
        return 0;
    } else if (n <= 1) {
        return 1;
    } else {
        double x = (double)n;
        double term1 = log10(x / 2.0);
        double term2 = log10(2.0 * x) / 3.0;
        double result = x * term1 + term2;
        return (int)floor(result) + 1;
    }
}