void __cdecl ZVdotU21(int n, double *y0, double *y1, double *x0, double *sums)
{
  double r00 = 0.0; // Real part of the first dot product (y0 · x0)
  double i00 = 0.0; // Imaginary part of the first dot product (y0 · x0)
  double r10 = 0.0; // Real part of the second dot product (y1 · x0)
  double i10 = 0.0; // Imaginary part of the second dot product (y1 · x0)

  for (int i = 0; i < n; ++i)
  {
    int idx = 2 * i; // Index of the real part; idx + 1 is the imaginary part

    // Extract complex numbers for the current iteration
    double yr0 = y0[idx];
    double yi0 = y0[idx + 1];
    
    double yr1 = y1[idx];
    double yi1 = y1[idx + 1];
    
    double xr0 = x0[idx];
    double xi0 = x0[idx + 1];

    // Complex multiplication and accumulation: (y_r + j*y_i) * (x_r + j*x_i)
    // Real part:      yr * xr - yi * xi
    // Imaginary part: yr * xi + yi * xr
    
    r00 += yr0 * xr0 - yi0 * xi0;
    i00 += yr0 * xi0 + yi0 * xr0;
    
    r10 += yr1 * xr0 - yi1 * xi0;
    i10 += yr1 * xi0 + yi1 * xr0;
  }

  // Store the resulting two complex numbers into the sums array
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r10;
  sums[3] = i10;
}