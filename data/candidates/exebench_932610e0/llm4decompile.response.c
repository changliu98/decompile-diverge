double randlc(double *x, double *a)
{







    long k, i, j;
    double t, x1, r;

    k = (long) (*x * *a);
    i = k / 127773;
    j = k % 127773;
    *x = (double) j;
    t = (double) i;
    x1 = *x / 127773.0;
    r = (t * 16807.0) + x1;
    if (r > (1.0 - 1.2e-7))
        r -= 1.0;
    return r;
}