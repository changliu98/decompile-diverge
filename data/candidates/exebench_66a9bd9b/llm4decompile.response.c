void fft4pt(complex *buf)
{
    float t0r, t0i, t1r, t1i, t2r, t2i, t3r, t3i;
    float tmp0r, tmp0i, tmp1r, tmp1i, tmp2r, tmp2i, tmp3r, tmp3i;

    tmp0r = buf[0].re;
    tmp0i = buf[0].im;
    tmp1r = buf[1].re;
    tmp1i = buf[1].im;
    tmp2r = buf[2].re;
    tmp2i = buf[2].im;
    tmp3r = buf[3].re;
    tmp3i = buf[3].im;

    t0r = tmp0r + tmp2r;
    t0i = tmp0i + tmp2i;
    t1r = tmp0r - tmp2r;
    t1i = tmp0i - tmp2i;
    t2r = tmp1r - tmp3i;
    t2i = tmp1i + tmp3r;
    t3r = tmp1r + tmp3i;
    t3i = tmp1i - tmp3r;

    buf[0].re = t0r + t3r;
    buf[0].im = t0i + t3i;
    buf[1].re = t0r - t3r;
    buf[1].im = t0i - t3i;
    buf[2].re = t1r + t2i;
    buf[2].im = t1i - t2r;
    buf[3].re = t1r - t2i;
    buf[3].im = t1i + t2r;
}