void ifft4pt(complex *ioptr, float scale)
{
    float f0r, f0i, f1r, f1i, f2r, f2i, f3r, f3i;
    float t0r, t0i, t1r, t1i;

    f0r = ioptr[0].re + ioptr[4].re;
    f0i = ioptr[0].im + ioptr[4].im;
    f1r = ioptr[0].re - ioptr[4].re;
    f1i = ioptr[0].im - ioptr[4].im;

    f2r = ioptr[1].re + ioptr[5].re;
    f2i = ioptr[1].im + ioptr[5].im;
    f3r = ioptr[1].re - ioptr[5].re;
    f3i = ioptr[1].im - ioptr[5].im;

    t0r = ioptr[2].re - ioptr[6].re;
    t0i = ioptr[2].im - ioptr[6].im;
    t1r = ioptr[3].re - ioptr[7].re;
    t1i = ioptr[3].im - ioptr[7].im;

    ioptr[0].re = scale * (f0r + f2r);
    ioptr[0].im = scale * (f0i + f2i);
    ioptr[1].re = scale * (f1r - t1i);
    ioptr[1].im = scale * (f1i + t1r);
    ioptr[2].re = scale * (f0r - f2r);
    ioptr[2].im = scale * (f0i - f2i);
    ioptr[3].re = scale * (f1r + t1i);
    ioptr[3].im = scale * (f1i - t1r);

    ioptr[4].re = scale * (f0r - f2r);
    ioptr[4].im = scale * (f0i - f2i);
    ioptr[5].re = scale * (f1r + t1i);
    ioptr[5].im = scale * (f1i - t1r);
    ioptr[6].re = scale * (f0r + f2r);
    ioptr[6].im = scale * (f0i + f2i);
    ioptr[7].re = scale * (f1r - t1i);
    ioptr[7].im = scale * (f1i + t1r);
}