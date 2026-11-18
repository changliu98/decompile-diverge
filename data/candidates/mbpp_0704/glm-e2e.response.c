double func0(int n) {
    double result;
    double term;

    if (n < 2) {
        result = 1.0;
    } else {
        term = 1.0 / (double)n;
        result = term + func0(n - 1);
    }

    return result;
}