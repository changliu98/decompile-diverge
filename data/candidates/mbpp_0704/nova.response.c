double func0(int n) {
    if (n < 3) {
        return 1.0;
    } else {
        return 1.0 / n + func0(n - 1);
    }
}