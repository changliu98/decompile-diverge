int __cdecl matCopyVdf(double *v1, float *v2)
{
  float xmm0_4_1; // xmm0_4
  float v3; // xmm0_4
  float v4; // xmm0_4

  xmm0_4_1 = *v1;
  *v2 = xmm0_4_1;
  v3 = v1[1];
  v2[1] = v3;
  v4 = v1[2];
  v2[2] = v4;
  return 0;
}