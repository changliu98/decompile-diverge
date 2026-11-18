int func0(unsigned long long m, unsigned long long n,
               unsigned long long a, unsigned long long b,
               unsigned long long *x, unsigned long long *y) {
    unsigned long long x0 = 0, y0 = 0, x1 = 1, y1 = 1;
    while (x1 <= a && y1 <= b) {
        if (n == 0)
            break;
        unsigned long long q = m / n, r = m % n;
        m = n;
        n = r;
        unsigned long long t = x1;
        x1 = x0 + q * x1;
        x0 = t;
        t = y1;
        y1 = y0 + q * y1;
        y0 = t;
    }
    *x = x1;
    *y = y1;
    return 0;
}