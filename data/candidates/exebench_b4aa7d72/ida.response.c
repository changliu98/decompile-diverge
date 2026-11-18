void __cdecl grad1(int hash, float *gx)
{
  *gx = (float)(hash & 7) + 1.0;
  if ( (hash & 8) != 0 )
    *(_DWORD *)gx = _mm_cvtsi128_si32((__m128i)*(unsigned int *)gx) ^ 0x80000000;
}