void __cdecl ne_pre_filter16_double(double *_y, const double *_x, const int *_f)
{
    double diff[8];
    double half_diff[8];
    double acc[8];

    // Step 1: Calculate differences and half-differences
    for (int i = 0; i < 8; ++i)
    {
        diff[i] = _x[i] - _x[15 - i];
        half_diff[i] = _x[i] - diff[i] / 2.0;
    }

    // Step 2: Initial accumulation scaled by filter coefficients
    for (int i = 0; i < 8; ++i)
    {
        acc[i] = diff[i] * (double)_f[i] / 16.0;
    }

    // Step 3: Cascading accumulation
    acc[7] = acc[6] * (double)_f[14] / 16.0 + diff[7] * (double)_f[7] / 16.0;
    for (int i = 6; i >= 1; --i)
    {
        acc[i] = acc[i - 1] * (double)_f[i + 7] / 16.0 + acc[i + 1] * (double)_f[i + 15] / 16.0 + acc[i];
    }
    acc[0] = acc[1] * (double)_f[15] / 16.0 + acc[0];

    // Step 4: Compute and store outputs
    for (int i = 0; i < 8; ++i)
    {
        _y[i] = acc[i] / 2.0 + half_diff[i];
        _y[15 - i] = _y[i] - acc[i];
    }
}