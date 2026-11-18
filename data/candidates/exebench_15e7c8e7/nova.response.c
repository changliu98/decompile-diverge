void j2gcal(int *d, int *m, int *y, double jd) {
    int L, N, i, a, b, c, dd, mm, yy;

    L = (int)(jd + 68569);
    N = 4 * L / 146097;
    L = L - (146097 * N + 3) / 4;
    i = 4000 * (L + 1) / 1461001;
    L = L - 1461 * i / 4 + 31;
    a = 80 * L / 2447;
    b = (2 - a + i) / 11;
    c = (20 + a - b * c) / 10;
    dd = L - (11 * c + 29) / 30;
    mm = b + 2 - c * 12;
    yy = c - 4715;
    *d = dd;
    *m = mm;
    *y = yy;
}