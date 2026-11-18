void __cdecl ZVdotC32(int n, double complex *y0, double complex *y1, double complex *y2, 
                     double complex *x0, double complex *x1, double complex *sums)
{
    // Initialize the 3x2 output matrix (6 complex numbers = 12 doubles)
    double complex sum00 = 0.0, sum01 = 0.0;
    double complex sum10 = 0.0, sum11 = 0.0;
    double complex sum20 = 0.0, sum21 = 0.0;

    for (int i = 0; i < n; ++i)
    {
        // Load the complex vectors for the current iteration
        double complex v0 = y0[i];
        double complex v1 = y1[i];
        double complex v2 = y2[i];
        
        double complex u0 = x0[i];
        double complex u1 = x1[i];

        // Compute the complex dot products (conjugating the 'y' vectors)
        // The original code computes: (yr - j*yi) * (xr + j*xi) = (yr*xr + yi*xi) + j*(yr*xi - yi*xr)
        sum00 += conj(v0) * u0;
        sum01 += conj(v0) * u1;
        
        sum10 += conj(v1) * u0;
        sum11 += conj(v1) * u1;
        
        sum20 += conj(v2) * u0;
        sum21 += conj(v2) * u1;
    }

    // Store the resulting 3x2 complex matrix into the flat output array
    sums[0]  = sum00;
    sums[1]  = sum01;
    sums[2]  = sum10;
    sums[3]  = sum11;
    sums[4]  = sum20;
    sums[5]  = sum21;
}