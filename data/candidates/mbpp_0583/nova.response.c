int func0(int n) {
    int result;
    if (n <= 1) {
        result = 1;
    } else {
        int i, sum = 0;
        for (i = 0; i < n; i++) {
            sum += func0(i) * func0(n - i - 1);
        }
        result = sum;
    }
    return result;
}