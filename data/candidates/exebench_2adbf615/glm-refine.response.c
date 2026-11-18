void __cdecl daxpy(unsigned int n, const double da, const double *dx_0, double *dy)
{
  // If the scalar multiplier is zero, no operations are needed.
  if (da == 0.0)
  {
    return;
  }

  // If the scalar multiplier is 1.0, skip the multiplication step.
  if (da == 1.0)
  {
    for (unsigned int i = 0; i < n; ++i)
    {
      dy[i] += dx_0[i];
    }
  }
  else
  {
    for (unsigned int i = 0; i < n; ++i)
    {
      dy[i] += da * dx_0[i];
    }
  }
}