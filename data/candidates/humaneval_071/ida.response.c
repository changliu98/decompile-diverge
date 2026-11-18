float __cdecl func0(float a, float b, float c)
{
  float v3; // xmm0_4

  if ( c >= (float)(a + b) || b >= (float)(a + c) || a >= (float)(b + c) )
    return -1.0;
  v3 = sqrtf(
         (float)((float)((float)((float)((float)(a + b) + c) / 2.0)
                       * (float)((float)((float)((float)(a + b) + c) / 2.0) - a))
               * (float)((float)((float)((float)(a + b) + c) / 2.0) - b))
       * (float)((float)((float)((float)(a + b) + c) / 2.0) - c));
  return roundf(100.0 * v3) / 100.0;
}