static void rifft1pt(float *x, float y)
{
    float f0r, f0i, t0r, t0i;

    f0r = x[0];
    f0i = x[1];
    t0r = f0r + f0i;
    t0i = f0r - f0i;
    x[0] = y * t0r;
    x[1] = y * t0i;
}