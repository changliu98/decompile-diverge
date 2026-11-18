float __cdecl nabs_sf(float *p)
{
  float result; // xmm0_4

  LODWORD(result) = _mm_cvtsi128_si32(_mm_and_si128((__m128i)*(unsigned int *)p, (__m128i)xmmword_2010)) ^ 0x80000000;
  return result;
}