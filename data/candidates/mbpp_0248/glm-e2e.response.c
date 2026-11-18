double func0(int n) {
    double result;
    double temp;

    if (n < 2) {
        result = 1.0;
    } else {
        temp = 1.0 / (double)n;
        result = temp + func0(n - 1);
    }

    return result;
}