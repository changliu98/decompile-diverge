void fft2pt(FFTComplex *c)
{
    float r0, r1, i0, i1;

    r0 = c->re;
    i0 = c->im;
    r1 = c->re + c->im;
    i1 = c->im - c->re;
    c->re = r0 + r1;
    c->im = i0 + i1;
    c++;
    c->re = r0 - r1;
    c->im = i0 - i1;
}