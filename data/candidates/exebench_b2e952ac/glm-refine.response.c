void __cdecl ZVdotU32(int n, double *y0, double *y1, double *y2, double *x0, double *x1, double *sums)
{
    // The output array holds 6 complex numbers (12 doubles).
    cplx *out = (cplx *)sums;
    
    // Initialize accumulators for the 6 complex dot products
    cplx dot00 = {0.0, 0.0};
    cplx dot01 = {0.0, 0.0};
    cplx dot10 = {0.0, 0.0};
    cplx dot11 = {0.0, 0.0};
    cplx dot20 = {0.0, 0.0};
    cplx dot21 = {0.0, 0.0};

    for (int i = 0; i < n; ++i)
    {
        // Load the 3 complex elements from vector y
        cplx yv0 = *(cplx *)(y0 + 2 * i);
        cplx yv1 = *(cplx *)(y1 + 2 * i);
        cplx yv2 = *(cplx *)(y2 + 2 * i);

        // Load the 2 complex elements from vector x
        cplx xv0 = *(cplx *)(x0 + 2 * i);
        cplx xv1 = *(cplx *)(x1 + 2 * i);

        // Perform complex multiplications and accumulate
        // (yr + i*yi) * (xr + i*xi) = (yr*xr - yi*xi) + i*(yr*xi + yi*xr)
        
        dot00.re += yv0.re * xv0.re - yv0.im * xv0.im;
        dot00.im += yv0.re * xv0.im + yv0.im * xv0.re;

        dot01.re += yv0.re * xv1.re - yv0.im * xv1.im;
        dot01.im += yv0.re * xv1.im + yv0.im * xv1.re;

        dot10.re += yv1.re * xv0.re - yv1.im * xv0.im;
        dot10.im += yv1.re * xv0.im + yv1.im * xv0.re;

        dot11.re += yv1.re * xv1.re - yv1.im * xv1.im;
        dot11.im += yv1.re * xv1.im + yv1.im * xv1.re;

        dot20.re += yv2.re * xv0.re - yv2.im * xv0.im;
        dot20.im += yv2.re * xv0.im + yv2.im * xv0.re;

        dot21.re += yv2.re * xv1.re - yv2.im * xv1.im;
        dot21.im += yv2.re * xv1.im + yv2.im * xv1.re;
    }

    // Store the computed complex dot products back into the sums array
    out[0] = dot00;
    out[1] = dot01;
    out[2] = dot10;
    out[3] = dot11;
    out[4] = dot20;
    out[5] = dot21;
}