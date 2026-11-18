double __cdecl randlc(double *x, double *a)
{
  double v2; // xmm1_8

  v2 = (double)((int)*a * (int)*x);
  *x = v2;
  return 1.4210854715202e-14 * v2;
}