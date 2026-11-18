void __cdecl ZVdotC21(int n, double *y0, double *y1, double *x0, double *sums)
{
  double sum0_real = 0.0;
  double sum0_imag = 0.0;
  double sum1_real = 0.0;
  double sum1_imag = 0.0;

  for (int i = 0; i < n; ++i)
  {
    int real_idx = 2 * i;
    int imag_idx = 2 * i + 1;

    // Extract interleaved complex numbers
    double y0_r = y0[real_idx];
    double y0_i = y0[imag_idx];
    
    double y1_r = y1[real_idx];
    double y1_i = y1[imag_idx];
    
    double x_r  = x0[real_idx];
    double x_i  = x0[imag_idx];

    // Complex dot product 1: y0 * conj(x0)
    // (y0_r + j*y0_i) * (x_r - j*x_i) = (y0_r*x_r + y0_i*x_i) + j*(y0_r*x_i - y0_i*x_r)
    sum0_real += y0_r * x_r + y0_i * x_i;
    sum0_imag += y0_r * x_i - y0_i * x_r;

    // Complex dot product 2: y1 * conj(x0)
    sum1_real += y1_r * x_r + y1_i * x_i;
    sum1_imag += y1_r * x_i - y1_i * x_r;
  }

  // Store the 4 resulting components into the sums array
  sums[0] = sum0_real;
  sums[1] = sum0_imag;
  sums[2] = sum1_real;
  sums[3] = sum1_imag;
}