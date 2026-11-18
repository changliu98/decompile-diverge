int __cdecl find(float xt, float *x, int n)
{
  int il, im;

  // Handle boundary conditions
  if (xt <= x[0])
    return 0;
  if (xt >= x[n - 1])
    return n - 1;

  // Binary search to find the interval index
  il = 1;
  im = n;
  while (im - il > 1)
  {
    int mid = (il + im) / 2;
    if (xt < x[mid - 1])
      im = mid;
    else
      il = mid;
  }

  return il - 1;
}