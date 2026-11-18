int func0(int a, int b, int c) {
    int d;
    while (c > 0) {
        c--;
        a *= 10;
        d = a / b;
        a %= b;
    }
    return d;
}