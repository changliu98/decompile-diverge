void __cdecl ZVdotC31(int n, const double *y0, const double *y1, const double *y2, const double *x0, double *sums)
{
    double real0 = 0.0, imag0 = 0.0;
    double real1 = 0.0, imag1 = 0.0;
    double real2 = 0.0, imag2 = 0.0;

    for (int i = 0; i < n; ++i)
    {
        // Extract complex numbers for the i-th element
        // Format: [real, imag, real, imag, ...]
        double yr0 = y0[2 * i];
        double yi0 = y0[2 * i + 1];
        
        double yr1 = y1[2 * i];
        double yi1 = y1[2 * i + 1];
        
        double yr2 = y2[2 * i];
        double yi2 = y2[2 * i + 1];
        
        double xr0 = x0[2 * i];
        double xi0 = x0[2 * i + 1];

        // Accumulate complex dot product: Y * conj(X)
        // Real part: (yr * xr + yi * xi)
        // Imag part: (yr * xi - yi * xr)
        
        real0 += yr0 * xr0 + yi0 * xi0;
        imag0 += yr0 * xi0 - yi0 * xr0;

        real1 += yr1 * xr0 + yi1 * xi0;
        imag1 += yr1 * xi0 - yi1 * xr0;

        real2 += yr2 * xr0 + yi2 * xi0;
        imag2 += yr2 * xi0 - yi2 * xr0;
    }

    // Store the resulting 3 complex numbers into the sums array
    sums[0] = real0;
    sums[1] = imag0;
    sums[2] = real1;
    sums[3] = imag1;
    sums[4] = real2;
    sums[5] = imag2;
}