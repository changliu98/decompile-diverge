int __cdecl matCalcCross(double *v1, double *v2, double *vr)
{
  vr[0] = v1[1] * v2[2] - v1[2] * v2[1];
  vr[1] = v1[2] * v2[0] - v1[0] * v2[2];
  vr[2] = v1[0] * v2[1] - v1[1] * v2[0];
  
  return 0;
}