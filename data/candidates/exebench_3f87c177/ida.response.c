int __cdecl matCalcCross(double *v1, double *v2, double *vr)
{
  *vr = v1[1] * v2[2] - v2[1] * v1[2];
  vr[1] = v1[2] * *v2 - v2[2] * *v1;
  vr[2] = *v1 * v2[1] - *v2 * v1[1];
  return 0;
}