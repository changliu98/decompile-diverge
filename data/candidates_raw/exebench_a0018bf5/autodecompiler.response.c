void cftf082(double *a, double *w, double *w2)
{
    double x0r, x0i, x1r, x1i, y0r, y0i, y1r, y1i,
        y2r, y2i, y3r, y3i, y4r, y4i, y5r, y5i,
        y6r, y6i, y7r, y7i, wn4r, wk1r, wk1i;

    y0r = a[0] + a[7];
    y0i = a[1] + a[6];
    y1r = a[2] + a[5];
    y1i = a[3] + a[4];
    x0r = y0r + y1r;
    x0i = y0i + y1i;
    w2[0] = x0r;
    w2[32] = x0i;
    y0r -= y1r;
    y0i -= y1i;
    w2[16] = y0r * w[2] + y0i * w[3];
    w2[48] = y0i * w[2] - y0r * w[3];
    x0r = a[0] - a[7];
    x0i = a[1] - a[6];
    x1r = a[2] - a[5];
    x1i = a[3] - a[4];
    w2[8] = x0r * w[1] + x0i * w[3] + x1r * w[5] + x1i * w[7];
    w2[24] = x0r * w[3] - x0i * w[1] - x1r * w[7] - x1i * w[5];
    w2[40] = x0r * w[5] - x0i * w[7] + x1r * w[1] + x1i * w[3];
    w2[56] = x0r * w[7] + x0i * w[5] - x1r * w[3] - x1i * w[1];
    wn4r = w[4];
    wk1r = w[2];
    wk1i = w[3];
    y2r = a[2] - a[5];
    y2i = a[3] + a[4];
    y3r = a[0] - a[7];
    y3i = a[1] + a[6];
    y4r = a[0] + a[7];
    y4i = a[1] - a[6];
    y5r = a[2] + a[5];
    y5i = a[3] - a[4];
    y6r = a[4] - a[2];
    y6i = a[3] + a[5];
    y7r = a[6] - a[0];
    y7i = a[7] + a[0];
    x0r = y3r - y2r;
    x0i = y3i - y2i;
    x1r = y4r - y5r;
    x1i = y4i - y5i;
    w2[1] = wn4r * (x0r - x0i);
    w2[33] = wn4r * (x0i + x0r);
    w2[17] = wk1r * x1r - wk1i * x1i;
    w2[49] = wk1i * x1r + wk1r * x1i;
    x0r = y6r - y7r;
    x0i = y6i - y7i;
    x1r = y7r + y2r;
    x1i = y7i + y2i;
    w2[9] = wk1i * x0r + wk1r * x0i + wk1r * x1r + wk1i * x1i;
    w2[25] = wk1r * x0r - wk1i * x0i - wk1i * x1r - wk1r * x1i;
    w2[41] = wk1r * x0r - wk1i * x0i + wk1i * x1r + wk1r * x1i;
    w2[57] = wk1i * x0r + wk1r * x0i - wk1r * x1r - wk1i * x1i;
}