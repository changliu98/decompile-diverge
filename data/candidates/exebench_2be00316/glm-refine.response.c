void __cdecl ZVdotU31(int n, double *y0, double *y1, double *y2, double *x0, double *sums)
{
  double dot0_re = 0.0;
  double dot0_im = 0.0;
  double dot1_re = 0.0;
  double dot1_im = 0.0;
  double dot2_re = 0.0;
  double dot2_im = 0.0;

  // Iterate through the array, stepping by 2 for interleaved complex numbers
  for (int i = 0; i < n * 2; i += 2)
  {
    // Extract complex components for the current index
    double y0_re = y0[i];
    double y0_im = y0[i + 1];
    
    double y1_re = y1[i];
    double y1_im = y1[i + 1];
    
    double y2_re = y2[i];
    double y2_im = y2[i + 1];
    
    double x_re = x0[i];
    double x_im = x0[i + 1];

    // Compute complex dot product: y * conj(x)
    // (y_re + j*y_im) * (x_re - j*x_im) = (y_re*x_re + y_im*x_im) + j*(y_im*x_re - y_re*x_im)
    dot0_re += y0_re * x_re + y0_im * x_im;
    dot0_im += y0_im * x_re - y0_re * x_im;

    dot1_re += y1_re * x_re + y1_im * x_im;
    dot1_im += y1_im * x_re - y1_re * x_im;

    dot2_re += y2_re * x_re + y2_im * x_im;
    dot2_im += y2_im * x_re - y2_re * x_im;
  }

  // Store the resulting 3 complex numbers (6 doubles) into the sums array
  sums[0] = dot0_re;
  sums[1] = dot0_im;
  sums[2] = dot1_re;
  sums[3] = dot1_im;
  sums[4] = dot2_re;
  sums[5] = dot2_im;
}