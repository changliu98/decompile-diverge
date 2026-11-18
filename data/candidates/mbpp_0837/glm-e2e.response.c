int func0(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int term = 2 * i + 1;
        sum += term * term * term;
    }
    return sum;
}