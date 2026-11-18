void ifft2pt(complex *ioptr, float scale)
{
    float xi, yi;

    xi = ioptr[0].re;
    yi = ioptr[0].im;
    ioptr[0].re = scale * (xi + ioptr[1].re);
    ioptr[0].im = scale * (yi + ioptr[1].im);
    ioptr[1].re = scale * (xi - ioptr[1].re);
    ioptr[1].im = scale * (yi - ioptr[1].im);
}