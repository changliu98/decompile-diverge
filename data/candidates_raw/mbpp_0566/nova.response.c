int func0(int n) {
    if (n == 0) {
        return 0;
    }
    int sum = n % 10 + func0(n / 10);
    return sum;
}