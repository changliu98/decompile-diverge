float __cdecl catmull_rom_val(int n, float *x, float xval, float *y, float *tangents)
{
  int ival = n - 2;
  
  // Find the interval index `ival` such that x[ival] <= xval < x[ival + 1]
  for (int i = 0; i < n - 2; ++i)
  {
    if (x[i + 1] > xval)
    {
      ival = i;
      break;
    }
  }

  // Calculate the normalized distance (parameter t) in the current interval
  float h = x[ival + 1] - x[ival];
  float t = (xval - x[ival]) / h;
  
  // Precompute powers of t to avoid redundant multiplications
  float t2 = t * t;
  float t3 = t2 * t;

  // Hermite basis functions
  float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
  float h10 = t3 - 2.0f * t2 + t;
  float h01 = -2.0f * t3 + 3.0f * t2;
  float h11 = t3 - t2;

  // Compute and return the interpolated value
  return h00 * y[ival] 
       + h10 * h * tangents[ival] 
       + h01 * y[ival + 1] 
       + h11 * h * tangents[ival + 1];
}