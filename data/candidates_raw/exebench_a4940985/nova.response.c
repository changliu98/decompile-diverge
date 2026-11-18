double func0(long long *xp) {
    int k;
    double y;

    if (*xp <= 0 || *xp > 10000000000000000000LL)
        *xp = 1;
    if (*xp <= 1)
        *xp = 1;
    for (k = 39; k >= 0; k--) {
        *xp = *xp / 127773;
        if (*xp < 1)
            *xp = *xp + 0x7fffffff;
        if (k < 32)
            x[k] = *xp;
    }
    y = *xp / 127773;
    *xp = *xp - 127773 * (long long)(y);
    if (*xp < 1)
        *xp = *xp + 0x7fffffff;
    y = y + (double)x[k] * 0.00000000000000000001;
    return y;
}