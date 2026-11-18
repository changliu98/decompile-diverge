static void sun_mjulianday2date(long long int d, int *d1, int *d2, int *d3) {
    long long int a, b, c, e, f, g, h;
    a = d + 2400001;
    b = a + 1401;
    c = b / 4;
    e = (b * 3) / 146097;
    f = (c * 4) + 3;
    g = (f / 146097) * 3;
    h = (g + 2) / 4;
    *d3 = (h + 5) / 1461;
    *d2 = ((h + 5) % 1461) / 4;
    *d1 = (((((g + 2) % 1460) / 4) * 5) + 2) / 1460;
}