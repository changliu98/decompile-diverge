void fft4pt(complex *buf)
{
    float t0r, t0i, t1r, t1i, t2r, t2i, t3r, t3i;
    float f0r, f0i, f1r, f1i, f2r, f2i, f3r, f3i;

    t0r = buf[0].re + buf[4].re;
    t0i = buf[0].im + buf[4].im;
    t1r = buf[0].re - buf[4].re;
    t1i = buf[0].im - buf[4].im;
    t2r = buf[2].re - buf[6].re;
    t2i = buf[2].im - buf[6].im;
    t3r = buf[2].re + buf[6].re;
    t3i = buf[2].im + buf[6].im;

    f0r = t0r + t3r;
    f0i = t0i + t3i;
    f1r = t0r - t3r;
    f1i = t0i - t3i;
    f2r = t1r + t2i;
    f2i = t1i - t2r;
    f3r = t1r - t2i;
    f3i = t1i + t2r;

    buf[0].re = f0r;
    buf[0].im = f0i;
    buf[1].re = f1r;
    buf[1].im = f1i;
    buf[2].re = f2r;
    buf[2].im = f2i;
    buf[3].re = f3r;
    buf[3].im = f3i;
}