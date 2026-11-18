int func0(int n) {
    int sum = 0;
    int i = 1;
    while (i <= n) {
        int term = 2 * i - 1;
        sum += term * term * term * term * term;
        i++;
    }
    return sum;
}