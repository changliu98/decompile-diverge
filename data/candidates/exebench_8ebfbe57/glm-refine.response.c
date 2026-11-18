float __cdecl spline_cubic_val(int n, const float *t, float tval, const float *y, const float *ypp)
{
  int ival = n - 2;
  
  // Find the interval index `ival` such that t[ival] <= tval < t[ival + 1]
  for (int i = 0; i < n - 1; ++i)
  {
    if (t[i + 1] > tval)
    {
      ival = i;
      break;
    }
  }

  float h = t[ival + 1] - t[ival];
  float dt = tval - t[ival];

  // Cubic Hermite spline formulation using second derivatives (ypp)
  float a = y[ival];
  float b = (y[ival + 1] - y[ival]) / h 
          - (ypp[ival + 1] / 6.0f + ypp[ival] / 3.0f) * h;
  float c = ypp[ival] * 0.5f;
  float d = (ypp[ival + 1] - ypp[ival]) / (6.0f * h);

  // Evaluate the polynomial: a + b*dt + c*dt^2 + d*dt^3
  return a + dt * (b + dt * (c + dt * d));
}