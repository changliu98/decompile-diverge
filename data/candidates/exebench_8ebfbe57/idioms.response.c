float spline_cubic_val(int n, float *t, float tval, float *y, float *ypp)
{
  int i; int ival = n - 2;
  float h; float dt;
  for (i = 0; i < n - 1; i++)
  {
    if (t[i + 1] > tval)
    {
      ival = i;
      break;
    }
  }
  dt = tval - t[ival];
  h = t[ival + 1] - t[ival];
  return (y[ival] + (dt * ((dt * (ypp[ival] * 0.5 + (dt * ((ypp[ival + 1] - ypp[ival]) / (6.0 * h))))) - (h * (ypp[ival + 1] / 6.0 + ypp[ival] / 3.0)) + (h * ((y[ival + 1] - y[ival]) / h)))));
}