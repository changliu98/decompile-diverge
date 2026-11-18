float ran1(long *x) {
    int j;
    float y;

    if (*x <= 0 && next[1]!= 0)
        *x = 1;
    if (*x < 0)
        *x = -*x;
    for (j = 39; j >= 0; j--) {
        *x = (IA[j] * *x) % IM;
        if (*x < 0)
            *x += IM;
        if (j < 32)
            bit[j] = *x / IM;
    }
    y = (float)bit[0];
    for (j = 1; j < 32; j++) {
        y = y + (float)bit[j] * (1.0 / (IM * 2));
    }
    return y;
}