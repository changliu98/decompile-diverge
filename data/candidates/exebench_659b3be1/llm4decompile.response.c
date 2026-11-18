void bitrv208(float *a)
{
    float x1r, x1i, x2r, x2i, x3r, x3i, x4r, x4i,
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
    x7r = a[14];
    x7i = a[15];
    x8r = a[16];
    x8i = a[17];
    a[2] = x8r;
    a[3] = x8i;
    a[4] = x3r;
    a[5] = x3i;
    a[6] = x4r;
    a[7] = x4i;
    a[8] = x7r;
    a[9] = x7i;
    a[10] = x2r;
    a[11] = x2i;
    a[14] = x1r;
    a[15] = x1i;
    a[16] = x5r;
    a[17] = x5i;
}