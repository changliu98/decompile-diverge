void dxpy1(int n, double *a, double *b)
{
  int i;

#pragma omp parallel for schedule(static) shared(a,b,n) private(i)
  for (i=0; i<n; i++)
    b[i] = a[i] + b[i];
}