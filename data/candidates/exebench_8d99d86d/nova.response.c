static void decode6(long long v, long long d, long long n,
                           long long *xl, long long *xr) {
    long long x, d6 = d * 6;
    x = v / d6;
    d = (d - 4) / 6;
    if (x >= d) {
        x = d;
        d6 = (x * d6) - (x * 6);
    }
    *xl = v - (x * d6);
    *xr = (n - 1) - ((x * d6) / n);
}