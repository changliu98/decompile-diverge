void fft4pt(float *a)
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
    { float _x0r = x0r + x1r; float _x0i = x0i + x1i; x1r = x0r - x1r; x1i = x0i - x1i; { float _y0r = x2r - x3r; float _y0i = x2i - x3i; x2r = x2r + x3r; x2i = x2i + x3i; x0r = _x0r + x2r; x0i = _x0i + x2i; x2r = _x0r - x2r; x2i = _x0i - x2i;}; { float _y0r = x1r - x2i; float _y0i = x1i + x2r; x3r = x1r + x2i; x3i = x1i - x2r;};
    a[0] = x0r;
    a[1] = x0i;
    a[2] = x3r;
    a[3] = x3i;
    a[4] = x2r;
    a[5] = x2i;
    a[6] = x1r;
    a[7] = x1i;
}