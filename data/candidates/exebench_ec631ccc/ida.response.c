void __cdecl lamda2x(double *lamda, double *x, double *h, double *boxlo)
{
  *x = h[4] * lamda[2] + *h * *lamda + h[5] * lamda[1] + *boxlo;
  x[1] = h[1] * lamda[1] + h[3] * lamda[2] + boxlo[1];
  x[2] = h[2] * lamda[2] + boxlo[2];
}