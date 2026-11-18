void rfft4pt(float *ioptr)
{
    float f0r, f0i, f1r, f1i, f2r, f2i, f3r, f3i;
    float t0r, t0i, t1r, t1i, t2r, t2i, t3r, t3i;
    float Two;
    float w0r;
    float scale;

    f0r = ioptr[0] + ioptr[4];
    f0i = ioptr[1] + ioptr[5];
    f1r = ioptr[0] - ioptr[4];
    f1i = ioptr[1] - ioptr[5];
    f2r = ioptr[2] - ioptr[6];
    f2i = ioptr[3] - ioptr[7];
    f3r = ioptr[2] + ioptr[6];
    f3i = ioptr[3] + ioptr[7];

    t0r = f0r + f3r;
    t0i = f0i + f3i;
    t1r = f0r - f3r;
    t1i = f0i - f3i;
    t2r = f1r - f2i;
    t2i = f1i + f2r;
    t3r = f1r + f2i;
    t3i = f1i - f2r;

    ioptr[0] = t0r + t0i;
    ioptr[1] = t0r - t0i;
    ioptr[2] = 0.5 * (t2r + t2i);
    ioptr[3] = 0.5 * (t2i - t2r);
    ioptr[4] = t1r - t3i;
    ioptr[5] = t1i + t3r;
    ioptr[6] = 0.5 * (t1r + t3i);
    ioptr[7] = 0.5 * (t3r - t1i);

    scale = 0.5;
    ioptr[0] *= scale;
    ioptr[1] *= scale;
    ioptr[2] *= scale;
    ioptr[3] *= scale;
    ioptr[4] *= scale;
    ioptr[5] *= scale;
    ioptr[6] *= scale;
    ioptr[7] *= scale;
}