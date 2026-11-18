void __cdecl ZVdotC13(int n, double *y0, double *x0, double *x1, double *x2, double *sums)
{
  double r00 = 0.0, i00 = 0.0; // Accumulators for dot product with x0
  double r01 = 0.0, i01 = 0.0; // Accumulators for dot product with x1
  double r02 = 0.0, i02 = 0.0; // Accumulators for dot product with x2

  for (int i = 0; i < n; ++i)
  {
    // Extract complex numbers (interleaved real and imaginary parts)
    double yr = y0[2 * i];
    double yi = y0[2 * i + 1];
    
    double xr0 = x0[2 * i];
    double xi0 = x0[2 * i + 1];
    
    double xr1 = x1[2 * i];
    double xi1 = x1[2 * i + 1];
    
    double xr2 = x2[2 * i];
    double xi2 = x2[2 * i + 1];

    // Complex multiplication and accumulation:
    // (yr + yi*i) * conj(xr + xi*i) = (yr*xr + yi*xi) + i(yr*xi - yi*xr)
    r00 += yr * xr0 + yi * xi0;
    i00 += yr * xi0 - yi * xr0;

    r01 += yr * xr1 + yi * xi1;
    i01 += yr * xi1 - yi * xr1;

    r02 += yr * xr2 + yi * xi2;
    i02 += yr * xi2 - yi * xr2;
  }

  // Store the 3 complex results (6 doubles) into the output array
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r02;
  sums[5] = i02;
}