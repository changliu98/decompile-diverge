int func0(int n) {
    int i;
    int sum = 0;
    for (i = 1; i <= n; i++) {
        sum += i * 2 * i * 2 * i * 2;
    }
    return sum;
}