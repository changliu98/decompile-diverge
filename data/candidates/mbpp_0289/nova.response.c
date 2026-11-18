int func0(int n) {
    int a = n / 100;
    int b = n / 400;
    int c = n >> 2;
    int d = n - c;
    if (a) {
        d += a;
        c -= a;
    }
    if (b) {
        d -= b;
        c += b;
    }
    int e = d + (c << 1);
    int f = e % 7;
    return f;
}