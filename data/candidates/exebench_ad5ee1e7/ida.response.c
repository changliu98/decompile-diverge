void __cdecl cross2(const float *v0, float *r0)
{
  *(_DWORD *)r0 = _mm_cvtsi128_si32((__m128i)*((unsigned int *)v0 + 1)) ^ 0x80000000;
  r0[1] = *v0;
}