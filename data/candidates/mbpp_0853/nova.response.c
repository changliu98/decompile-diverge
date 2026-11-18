int func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, x, y, z;
    double a, b, c, d, e, f, g, h, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1,
        t1, u1, v1, w1, x1, y1, z1;
    int res;

    res = 1;
    while (1) {
        if (n % 2 == 0)
            n /= 2;
        else
            break;
    }
    for (i = 3; i <= sqrt(n) + 1e-9; i += 2) {
        p = 0;
        while (1) {
            if (n % i == 0) {
                p++;
                n /= i;
                i *= i1;
                i1 = i;
                i11 = i1;
            } else
                break;
        }
        res *= (p + 1);
    }
    if (n >= 3)
        res *= (p + 1);
    return res;
}