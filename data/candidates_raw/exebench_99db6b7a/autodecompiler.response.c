void cftf040(float *a, float w)
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
    { float _xr, _xi; _xr = x0r + x1r; _xi = x0i + x1i; x1r = x0r - x1r; x1i = x0i - x1i; _x0r = x2r - x3r; _x0i = x2i - x3i; x2r = x2r + x3r; x2i = x2i + x3i; x0r = _xr + x2r; x0i = _xi + x2i; x2r = _xr - x2r; x2i = _xi - x2i; _xr = x1r + _x0i; _xi = x1i - _x0r; x3r = x1r - _x0i; x3i = x1i + _x0r; a[0] = w * x0r; a[1] = w * x0i; a[2] = w * x2r; a[3] = w * x2i; a[4] = w * x1r; a[5] = w * x1i; a[6] = w * x3r; a[7] = w * x3i; };
}