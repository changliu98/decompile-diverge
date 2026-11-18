void __cdecl rgb2cmyk(double r, double g, double b, double *c, double *m, double *y, double *k)
{
    *c = 1.0 - r;
    *m = 1.0 - g;
    *y = 1.0 - b;

    // The original decompiled code uses bitwise type punning (via pointer casting) 
    // to find the minimum of the three values. This is replaced with standard 
    // floating-point min operations, which preserves the exact semantics.
    *k = fmin(*c, *m);
    *k = fmin(*k, *y);

    *c -= *k;
    *m -= *k;
    *y -= *k;
}