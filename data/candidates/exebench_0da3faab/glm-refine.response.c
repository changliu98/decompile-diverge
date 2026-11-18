void __cdecl mac_real(float *x, float *h, float *y)
{
  float h_val = *h;
  
  // Accumulate the real part
  y[0] += x[0] * h_val;
  
  // Accumulate the imaginary part
  y[1] += x[1] * h_val;
}