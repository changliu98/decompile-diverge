double func0(uint64_t *x) {
    uint64_t a, b, c, d, e, f, g, h;
    uint64_t i, j, k, l, m, n, o, p;
    double q;

    a = *x & 0xfff;
    b = *x >> 12;
    c = a * 1549;
    d = c & 0xfff;
    e = b * 406;
    f = c + e + a;
    g = f & 0xfff;
    h = f >> 12;
    i = *x >> 24;
    j = i & 0xff;
    k = j * 1549;
    l = k + e + f;
    m = l & 0xff;
    *x = (m << 24) | (g << 12) | (h);
    q = (m * 1000000000.0) + (h * 1000000.0) + (k * 1000.0) + (l * 1.0);
    return (q);
}