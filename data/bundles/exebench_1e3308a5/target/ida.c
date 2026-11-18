void __cdecl neg_s(const float *source, float *target)
{
  *(_DWORD *)target = _mm_cvtsi128_si32((__m128i)*(unsigned int *)source) ^ 0x80000000;
}