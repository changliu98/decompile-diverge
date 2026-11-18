int func0(int n) {
    int a = 3, b = 0, c = 2, d, e;
    if (n == 0) {
        d = 3;
    } else if (n == 1) {
        d = 3;
    } else if (n == 2) {
        d = 5;
    } else {
        while (n-- > 2) {
            e = a + b;
            e = e + c;
            b = a;
            c = e;
            d = c;
        }
    }
    return d;
}