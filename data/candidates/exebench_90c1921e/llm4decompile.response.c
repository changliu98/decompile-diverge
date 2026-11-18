void ifft8pt(float *ioptr, float scale)
{
    float f0r, f0i, f1r, f1i, f2r, f2i, f3r, f3i;
    float f4r, f4i, f5r, f5i, f6r, f6i, f7r, f7i;
    float f00r, f00i, f01r, f01i, f02r, f02i, f03r, f03i;
    float f04r, f04i, f05r, f05i, f06r, f06i, f07r, f07i;
    float f08r, f08i, f09r, f09i, f10r, f10i, f11r, f11i;
    float f12r, f12i, f13r, f13i, f14r, f14i, f15r, f15i;
    float w0r, w0i, w1r, w1i, w2r, w2i, w3r, w3i;
    float w4r, w4i, w5r, w5i, w6r, w6i, w7r, w7i;
    float w8r, w8i, w9r, w9i, w10r, w10i, w11r, w11i;
    float w12r, w12i, w13r, w13i, w14r, w14i, w15r, w15i;
    float Two;

    f0r = ioptr[0] + ioptr[8];
    f0i = ioptr[1] + ioptr[9];
    f1r = ioptr[0] - ioptr[8];
    f1i = ioptr[1] - ioptr[9];
    f2r = ioptr[4] - ioptr[12];
    f2i = ioptr[5] - ioptr[13];
    f3r = ioptr[4] + ioptr[12];
    f3i = ioptr[5] + ioptr[13];
    f00r = f0r + f3r;
    f00i = f0i + f3i;
    f01r = f0r - f3r;
    f01i = f0i - f3i;
    f02r = f1r + f2i;
    f02i = f1i - f2r;
    f03r = f1r - f2i;
    f03i = f1i + f2r;

    f4r = ioptr[2] + ioptr[10];
    f4i = ioptr[3] + ioptr[11];
    f5r = ioptr[2] - ioptr[10];
    f5i = ioptr[3] - ioptr[11];
    f6r = ioptr[6] - ioptr[14];
    f6i = ioptr[7] - ioptr[15];
    f7r = ioptr[6] + ioptr[14];
    f7i = ioptr[7] + ioptr[15];
    f04r = f4r + f7r;
    f04i = f4i + f7i;
    f05r = f4r - f7r;
    f05i = f4i - f7i;
    f06r = f5r + f6i;
    f06i = f5i - f6r;
    f07r = f5r - f6i;
    f07i = f5i + f6r;

    f08r = f02r + f06r;
    f08i = f02i + f06i;
    f09r = f02r - f06r;
    f09i = f02i - f06i;
    f10r = f03r + f07i;
    f10i = f03i - f07r;
    f11r = f03r - f07i;
    f11i = f03i + f07r;

    f12r = f01r + f05i;
    f12i = f01i - f05r;
    f13r = f01r - f05i;
    f13i = f01i + f05r;
    f14r = f09r + f11i;
    f14i = f09i - f11r;
    f15r = f09r - f11i;
    f15i = f09i + f11r;

    ioptr[0] = (f00r + f04r) * scale;
    ioptr[1] = (f00i + f04i) * scale;
    ioptr[2] = (f01r + f01r - f14r) * scale;
    ioptr[3] = (f01i + f01i - f14i) * scale;
    ioptr[4] = (f00r - f04r) * scale;
    ioptr[5] = (f00i - f04i) * scale;
    ioptr[6] = (f01r + f01r - f14r) * scale;
    ioptr[7] = (f01i + f01i - f14i) * scale;
    ioptr[8] = (f00r - f04r) * scale;
    ioptr[9] = (f00i - f04i) * scale;
    ioptr[10] = f14r * scale;
    ioptr[11] = f14i * scale;
    ioptr[12] = (f00r + f04r) * scale;
    ioptr[13] = (f00i - f04i) * scale;
    ioptr[14] = f14r * scale;
    ioptr[15] = f14i * scale;
}