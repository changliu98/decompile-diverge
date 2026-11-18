void __cdecl vsub(const float *src1, const float *src2, float *dst)
{
  *dst = *src1 - *src2;
  dst[1] = src1[1] - src2[1];
  dst[2] = src1[2] - src2[2];
}