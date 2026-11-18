float func0(long *x) {
    int j;
    float y;

    if (*x <= 0 &&!seeded)
        *x = 1;
    if (*x <= 0)
        *x = 1;
    for (j = 39; j >= 0; j--) {
        *x = IX1(*x) ^ IX2(*x);
        if (*x < 0)
            *x += IA;
        if (j < 32)
            save[j] = *x;
    }
    y = 0;
    for (j = 31; j >= 0; j--) {
        y = (float)(y * 2.0 + RM1 * (*x));
        *x = IX1(*x) ^ IX2(*x);
        if (*x < 0)
            *x += IA;
        y -= RM2;
        if (j < 32)
            save[j + 32] = *x;
    }
    y = y * TWOPI - TWOPI;
    return y;
}