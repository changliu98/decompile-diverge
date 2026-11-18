int func0(float *coeff, int n, float x) {
    int i, j;
    float y, t;

    if (x < 0)
        x = 0;
    if (x > 99)
        x = 99;

    i = (int)x;
    if (i > 99)
        i = 99;

    t = coeff[i];
    if (i < 99)
        j = coeff[i + 1];
    else
        j = coeff[99];

    y = t + (j - t) * (x - i);
    y *= (10 * n);
    return (int)y;
}