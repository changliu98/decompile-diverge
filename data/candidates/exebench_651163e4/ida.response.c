int __cdecl matV3toV4(double *v3, double *v4)
{
  *v4 = *v3;
  v4[1] = v3[1];
  v4[2] = v3[2];
  v4[3] = 1.0;
  return 0;
}