void rfft4pt(float *a)
{
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
    float wki = 0.707106781186547524400844362104849039284835937688;
    float wkj = 2.0;
    float wdr = ((float) 0.5);
    float wdi = ((float) 0.5);

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
    { float t2r = t0r + x2r; float t2i = t0i + x2i; x2r = t0r - x2r; x2i = t0i - x2i; };
    { float t3r = x1r - t1i; float t3i = x1i + t1r; x1r = x1r + t1i; x1i = x1i - t1r; };
    { float t0r = t2r + t3r; float t0i = t2i + t3i; x3r = t2r - t3r; x3i = t2i - t3i; };
    { float t1r = x1r + t3i; float t1i = x1i - t3r; x1r = x1i + t3r; x1i = t3i - x1r; };
    x2r = t1r + wki * x1r + wki * x1i;
    x2i = t1i - wki * x1r + wki * x1i;
    x3r = 2.0 * t0r - x2r;
    x3i = x2i - 2.0 * t0i;

    a[4] = x2r;
    a[5] = x2i;
    a[0] = t0r;
    a[1] = t0i;
    a[2] = wdr * x1r;
    a[3] = wdr * x1i;
    a[6] = wdr * x3r;
    a[7] = wdr * x3i;
}