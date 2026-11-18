void bitrv208(double *a)
{
    double x1r, x1i, x2r, x2i, x3r, x3i, x4r, x4i,
        x5r, x5i, x7r, x7i, x8r, x8i;

    x1r = a[2];
    x1i = a[3];
    x2r = a[4];
    x2i = a[5];
    x3r = a[6];
    x3i = a[7];
    x4r = a[8];
    x4i = a[9];
    x5r = a[10];
    x5i = a[11];
    x7r = a[12];
    x7i = a[13];
    x8r = a[14];
    x8i = a[15];
    a[2] = x8r;
    a[3] = x8i;
    a[4] = x4r;
    a[5] = x4i;
    a[6] = x6r;
    a[7] = x6i;
    a[8] = x2r;
    a[9] = x2i;
    a[10] = x3r;
    a[11] = x3i;
    a[12] = x1r;
    a[13] = x1i;
    a[14] = x5r;
    a[15] = x5i;
}