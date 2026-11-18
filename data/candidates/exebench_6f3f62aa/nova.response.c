float ran1(long *x) {
    int i;
    float y;
    long h;

    if (*x <= 0 && next[39]!= 0)
        *x = 1;
    if (next[39] < 2)
        *x = -*x;
    for (i = 39; i >= 0; i--) {
        h = *x / q[i];
        *x = *x - h * q[i];
        if (*x < 0)
            *x = *x + M;
        if (i < 32)
            bit[i] = h;
    }
    uran1[3] = uran1[2];
    uran1[2] = uran1[1];
    uran1[1] = uran1[0];
    uran1[0] = bit[39];
    y = (float)uran1[0] * (1.0 / 4294967296.0);
    if (y > (float)1.0)
        y = (float)1.0;
    return y;
}