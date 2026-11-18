int func0(int n) {
    if (n < 1) {
        return 0;
    }
    return n + func0(n - 2);
}