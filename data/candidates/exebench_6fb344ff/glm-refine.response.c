void __cdecl fft8pt(float *ioptr)
{
    cpx_t *io = (cpx_t *)ioptr;
    cpx_t f0, f1, f2, f3, f4, f5, f6, f7;
    cpx_t t0, t1, t2, t3;
    cpx_t s0, s1, s2, s3;
    cpx_t u0, u1, u2, u3;
    cpx_t v0, v1, v2, v3;

    // Load the 8 complex input values
    f0 = io[0];
    f1 = io[4];
    f2 = io[2];
    f3 = io[6];
    f4 = io[1];
    f5 = io[5];
    f6 = io[3];
    f7 = io[7];

    // Stage 1: 2-point FFTs
    t0.r = f0.r + f1.r; t0.i = f0.i + f1.i;
    t1.r = f0.r - f1.r; t1.i = f0.i - f1.i;
    t2.r = f2.r - f3.r; t2.i = f2.i - f3.i;
    t3.r = f2.r + f3.r; t3.i = f2.i + f3.i;

    s0.r = f4.r + f5.r; s0.i = f4.i + f5.i;
    s1.r = f4.r - f5.r; s1.i = f4.i - f5.i;
    s2.r = f6.r - f7.r; s2.i = f6.i - f7.i;
    s3.r = f6.r + f7.r; s3.i = f6.i + f7.i;

    // Stage 2: 4-point FFTs
    u0.r = t0.r + t3.r; u0.i = t0.i + t3.i;
    u1.r = t1.r - t2.i; u1.i = t1.i + t2.r;
    u2.r = t0.r - t3.r; u2.i = t0.i - t3.i;
    u3.r = t1.r + t2.i; u3.i = t1.i - t2.r;

    v0.r = s0.r + s3.r; v0.i = s0.i + s3.i;
    v1.r = s1.r - s2.i; v1.i = s1.i + s2.r;
    v2.r = s0.r - s3.r; v2.i = s0.i - s3.i;
    v3.r = s1.r + s2.i; v3.i = s1.i - s2.r;

    // Stage 3: 8-point FFT combination with twiddle factors (sqrt(2)/2)
    const float k = 0.70710677f;

    cpx_t w1, w3;
    w1.r = u1.r + k * (v1.r - v1.i);
    w1.i = u1.i + k * (v1.r + v1.i);
    
    w3.r = u3.r + k * (-v3.r - v3.i);
    w3.i = u3.i + k * (v3.r - v3.i);

    // Store the 8 complex output values
    io[0].r = u0.r + v0.r; io[0].i = u0.i + v0.i;
    io[1].r = 2.0f * u1.r - w1.r; io[1].i = 2.0f * u1.i - w1.i;
    io[2].r = u2.r + v2.i; io[2].i = u2.i - v2.r;
    io[3].r = 2.0f * u3.r - w3.r; io[3].i = 2.0f * u3.i - w3.i;
    io[4].r = u0.r - v0.r; io[4].i = u0.i - v0.i;
    io[5].r = w1.r; io[5].i = w1.i;
    io[6].r = u2.r - v2.i; io[6].i = u2.i + v2.r;
    io[7].r = w3.r; io[7].i = w3.i;
}