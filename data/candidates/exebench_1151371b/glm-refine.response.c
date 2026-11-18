void __cdecl ne_post_filter8_double(double *x, const double *y, const int *f)
{
    // 1. Calculate differences between symmetric elements of y
    double d7 = y[0] - y[7];
    double d6 = y[1] - y[6];
    double d5 = y[2] - y[5];
    double d4 = y[3] - y[4];

    // 2. Calculate midpoints between symmetric elements of y
    double m0 = y[0] - d7 / 2.0;
    double m1 = y[1] - d6 / 2.0;
    double m2 = y[2] - d5 / 2.0;
    double m3 = y[3] - d4 / 2.0;

    // 3. Apply filter coefficients (scaled by 16.0)
    double f4 = (double)f[4];
    double f5 = (double)f[5];
    double f6 = (double)f[6];
    double f7 = (double)f[7];
    double f8 = (double)f[8];
    double f9 = (double)f[9];

    double a4 = d4 - d5 * f7 / 16.0;
    double a5 = d5 - a4 * f4 / 16.0 - d6 * f8 / 16.0;
    double a6 = d6 - a5 * f5 / 16.0 - d7 * f9 / 16.0;
    double a7 = 16.0 * (d7 - a6 * f6 / 16.0) / (double)f[3];

    // 4. Normalize filtered differences
    double n4 = 16.0 * a4 / (double)f[0];
    double n5 = 16.0 * a5 / (double)f[1];
    double n6 = 16.0 * a6 / (double)f[2];
    double n7 = a7; // Already normalized in the previous step

    // 5. Reconstruct the symmetric output array x
    x[0] = m0 + n7 / 2.0;
    x[1] = m1 + n6 / 2.0;
    x[2] = m2 + n5 / 2.0;
    x[3] = m3 + n4 / 2.0;
    
    x[4] = m3 - n4 / 2.0;
    x[5] = m2 - n5 / 2.0;
    x[6] = m1 - n6 / 2.0;
    x[7] = m0 - n7 / 2.0;
}