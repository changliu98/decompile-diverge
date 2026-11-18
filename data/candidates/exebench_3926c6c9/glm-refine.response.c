void __cdecl ne_pre_filter8_double(double *y, const double *x, const int *f)
{
    const double scale = 16.0;

    // Unpack input and calculate differences
    double d0 = x[0] - x[7];
    double d1 = x[1] - x[6];
    double d2 = x[2] - x[5];
    double d3 = x[3] - x[4];

    // Calculate intermediate values
    double m0 = x[0] - d0 / 2.0;
    double m1 = x[1] - d1 / 2.0;
    double m2 = x[2] - d2 / 2.0;
    double m3 = x[3] - d3 / 2.0;

    // Apply filter coefficients (scaled by 16.0)
    double s3 = d3 * (double)f[0] / scale;
    double s2 = d2 * (double)f[1] / scale;
    double s1 = d1 * (double)f[2] / scale;
    
    double s0 = s1 * (double)f[6] / scale + d0 * (double)f[3] / scale;
    double s1_f = s2 * (double)f[5] / scale + s0 * (double)f[9] / scale + s1;
    double s2_f = s3 * (double)f[4] / scale + s1_f * (double)f[8] / scale + s2;
    double s3_f = s2_f * (double)f[7] / scale + s3;

    // Calculate and write outputs
    y[0] = m0 + s0 / 2.0;
    y[1] = m1 + s1_f / 2.0;
    y[2] = m2 + s2_f / 2.0;
    y[3] = m3 + s3_f / 2.0;
    
    y[4] = y[3] - s3_f;
    y[5] = y[2] - s2_f;
    y[6] = y[1] - s1_f;
    y[7] = y[0] - s0;
}