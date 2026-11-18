void cftf040(float *a)
{
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;

    x0r = a[0];
    x0i = a[1];
    x1r = a[4];
    x1i = a[5];
    x2r = a[2];
    x2i = a[3];
    x3r = a[6];
    x3i = a[7];
    { float t0r = x0r + x1r; float t0i = x0i + x1i; x1r = x0r - x1r; x1i = x0i - x1i; };
    { float t1r = x2r - x3r; float t1i = x2i - x3i; x2r = x2r + x3r; x2i = x2i + x3i; };
    { x0r = t0r + x2r; x0i = t0i + x2i; x2r = t0r - x2r; x2i = t0i - x2i; };
    { x3r = x1r - t1i; x3i = x1i + t1r; x1r = x1r + t1i; x1i = x1i - t1r; };
    a[0] = x0r;
    a[1] = x0i;
    a[2] = x1r;
    a[3] = x1i;
    a[4] = x2r;
    a[5] = x2i;
    a[6] = x3r;
    a[7] = x3i;
}