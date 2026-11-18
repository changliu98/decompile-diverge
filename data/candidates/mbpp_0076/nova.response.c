int func0(int a, int b) {
    int c;
    if (b < a) {
        c = a;
        a = b;
        b = c;
    }
    int x = (a * (a + 1) * (2 * a + 1)) / 6;
    int y = (b * (b + 1)) / 2;
    return x + y;
}