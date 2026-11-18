void __cdecl project(int n, double *x, const int *pivot)
{
  for (int i = 0; i < n; ++i)
  {
    if (pivot[i])
      x[i] = 0.0;
  }
}