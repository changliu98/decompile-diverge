int func0(int n) {
    int a, b, c, d, e, f, g, h, i, j, k, l, m, o, p, q, r, s, t, u, v, w, x, y,
        z;
    a = 0;
    b = 2 * n;
    c = b * b;
    d = 1;
    while (1) {
        if (d < (2 * n)) {
            e = 1;
            while (1) {
                if (e < (2 * n)) {
                    f = d * d + e * e;
                    if (f <= c) {
                        a = a + 1;
                    } else {
                        e = e + 1;
                    }
                } else {
                    break;
                }
            }
        } else {
            break;
        }
        d = d + 1;
    }
    return a;
}