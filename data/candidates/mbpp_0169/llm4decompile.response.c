int func0(int n) {
    int a, b, c;
    if (n < 3) {
        return n;
    }
    a = 1;
    b = 2;
    for (int i = 3; i <= n; i++) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}