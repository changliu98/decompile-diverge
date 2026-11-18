int func0(int a, int b) {
    int t;
    if (b < a) {
        t = a;
        a = b;
        b = t;
    }
    return (a * (2 * b + 1) * (3 * b - a + 1)) / 6;
}