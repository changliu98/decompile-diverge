void __cdecl ZVdotC11(int n, double *y, double *x, double *result)
{
    double real_sum = 0.0;
    double imag_sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        // Extract complex numbers from interleaved arrays
        double yr = y[2 * i];     // Real part of y
        double yi = y[2 * i + 1]; // Imaginary part of y
        double xr = x[2 * i];     // Real part of x
        double xi = x[2 * i + 1]; // Imaginary part of x

        // Complex multiplication and accumulation:
        // (yr + yi*i) * (xr - xi*i) = (yr*xr + yi*xi) + (yr*xi - yi*xr)*i
        real_sum += yr * xr + yi * xi;
        imag_sum += yr * xi - yi * xr;
    }

    // Store the resulting complex number
    result[0] = real_sum;
    result[1] = imag_sum;
}