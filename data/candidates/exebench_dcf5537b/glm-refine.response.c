void __cdecl ZVdotU23(int n, double *y0, double *y1, double *x0, double *x1, double *x2, double *sums)
{
  // Accumulators for the real and imaginary parts of the 2x3 complex matrix
  double r00 = 0.0, i00 = 0.0;
  double r01 = 0.0, i01 = 0.0;
  double r02 = 0.0, i02 = 0.0;
  double r10 = 0.0, i10 = 0.0;
  double r11 = 0.0, i11 = 0.0;
  double r12 = 0.0, i12 = 0.0;

  // The arrays represent complex numbers stored as interleaved real/imaginary pairs.
  // rloc tracks the real component index, iloc tracks the imaginary component index.
  for (int ii = 0; ii < n; ++ii)
  {
    int rloc = ii * 2;
    int iloc = rloc + 1;

    // Load complex components for Y vector
    double yr0 = y0[rloc], yi0 = y0[iloc];
    double yr1 = y1[rloc], yi1 = y1[iloc];

    // Load complex components for X vector
    double xr0 = x0[rloc], xi0 = x0[iloc];
    double xr1 = x1[rloc], xi1 = x1[iloc];
    double xr2 = x2[rloc], xi2 = x2[iloc];

    // Complex multiplication and accumulation: Y[j] * X[k]
    // (yr + i*yi) * (xr + i*xi) = (yr*xr - yi*xi) + i*(yr*xi + yi*xr)
    
    // Row 0 (y0 * x0, x1, x2)
    r00 += yr0 * xr0 - yi0 * xi0;
    i00 += yr0 * xi0 + yi0 * xr0;
    
    r01 += yr0 * xr1 - yi0 * xi1;
    i01 += yr0 * xi1 + yi0 * xr1;
    
    r02 += yr0 * xr2 - yi0 * xi2;
    i02 += yr0 * xi2 + yi0 * xr2;

    // Row 1 (y1 * x0, x1, x2)
    r10 += yr1 * xr0 - yi1 * xi0;
    i10 += yr1 * xi0 + yi1 * xr0;
    
    r11 += yr1 * xr1 - yi1 * xi1;
    i11 += yr1 * xi1 + yi1 * xr1;
    
    r12 += yr1 * xr2 - yi1 * xi2;
    i12 += yr1 * xi2 + yi1 * xr2;
  }

  // Store the resulting 2x3 complex matrix into the output array
  // Format: [real0, imag0, real1, imag1, ...]
  sums[0]  = r00;
  sums[1]  = i00;
  sums[2]  = r01;
  sums[3]  = i01;
  sums[4]  = r02;
  sums[5]  = i02;
  sums[6]  = r10;
  sums[7]  = i10;
  sums[8]  = r11;
  sums[9]  = i11;
  sums[10] = r12;
  sums[11] = i12;
}