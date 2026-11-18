void project(int n, double *a, int *pivot)
{
  int i;
  for (i = 0; i < n; i++)
    if (pivot[i])
      a[i] = 0.0;
}