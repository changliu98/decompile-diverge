void fft8pt(float *a)
{
    float wn4r, wk1r, wk1i, x0r, x0i, x1r, x1i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i;

    wn4r = ((float) 0.707106781186547524400844362104849039284835);
    wk1r = 2.0;
    x0r = a[0];
    x0i = a[1];
    x1r = a[8];
    x1i = a[9];
    y0r = x0r + x1r;
    y0i = x0i + x1i;
    x1r = x0r - x1r;
    x1i = x0i - x1i;
    y1r = x2r - x3r;
    y1i = x2i - x3i;
    x2r = x2r + x3r;
    x2i = x2i + x3i;
    y2r = y0r + x2r;
    y2i = y0i + x2i;
    x2r = y0r - x2r;
    x2i = y0i - x2i;
    y3r = x1r - y1i;
    y3i = x1i + y1r;
    x1r = x1r + y1i;
    x1i = x1i - y1r;
    y0r = x4r + x5r;
    y0i = x4i + x5i;
    x5r = x4r - x5r;
    x5i = x4i - x5i;
    y1r = x6r - x7r;
    y1i = x6i - x7i;
    x6r = x6r + x7r;
    x6i = x6i + x7i;
    y4r = y0r + x6r;
    y4i = y0i + x6i;
    x6r = y0r - x6r;
    x6i = y0i - x6i;
    y5r = x5r - y1i;
    y5i = x5i + y1r;
    x5r = x5r + y1i;
    x5i = x5i - y1r;
    y6r = y2r - y4i;
    y6i = y2i + y4r;
    y7r = y3r + y5r;
    y7i = y3i + y5i;
    y2r = y2r + y4i;
    y2i = y2i - y4r;
    y3r = y3r - y5r;
    y3i = y3i - y5i;
    a[0] = y0r + y6r;
    a[1] = y0i + y6i;
    a[2] = y1r + wk1r * y7r + wk1r * y7i;
    a[3] = y1i + wk1r * y7r - wk1r * y7i;
    a[4] = y2r + 2.0 * y6r + y6i;
    a[5] = y2i + 2.0 * y6i - y6r;
    a[6] = y3r + y7r + wk1r * y7i;
    a[7] = y3i + y7i + wk1r * y7r;
    a[8] = y0r - y6r;
    a[9] = y0i - y6i;
    a[10] = y1r - wk1r * y7r - wk1r * y7i;
    a[11] = y1i - wk1r * y7r + wk1r * y7i;
    a[12] = y2r - 2.0 * y6r - y6i;
    a[13] = y2i - 2.0 * y6i + y6r;
    a[14] = y3r - y7r - wk1r * y7i;
    a[15] = y3i - y7i - wk1r * y7r;
}