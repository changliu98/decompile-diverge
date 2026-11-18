void __cdecl drmp3_L3_idct3(float x0, float x1, float x2, float *dst)
{
  float a1 = x0 - x2 * 0.5f;
  
  dst[1] = x0 + x2;
  *dst   = a1 + 0.86602539f * x1;
  dst[2] = a1 - 0.86602539f * x1;
}