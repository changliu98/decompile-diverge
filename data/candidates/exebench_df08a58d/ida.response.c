float __cdecl abs_sf(float *p)
{
  float result; // xmm0_4

  LODWORD(result) = _mm_and_si128((__m128i)*(unsigned int *)p, (__m128i)xmmword_2010).m128i_u32[0];
  return result;
}