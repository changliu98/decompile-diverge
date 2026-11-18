void cftf040(float *a)
{
    float x0r, x0i, x1r, x1i;

    x0r = a[6] + a[2];
    x0i = a[6] - a[2];
    x1r = a[4] + a[0];
    x1i = a[4] - a[0];
    a[6] = x0r + x1r;
    a[4] = x0r - x1r;
    x0r = a[5] - a[1];
    x1r = a[7] - a[3];
    a[0] = x0i + x1r;
    a[2] = x0i - x1r;
    x0r = a[5] + a[1];
    x0i = a[7] + a[3];
    a[3] = x1r + x1r;
    a[1] = x1r - x1r;
    a[7] = x0i + x0r;
    a[5] = x0i - x0r;
}