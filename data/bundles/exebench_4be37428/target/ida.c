void __cdecl sseround(float *vec)
{
  *(__m128 *)vec = _mm_or_ps(
                     _mm_cvtepi32_ps(_mm_cvtps_epi32(_mm_and_ps(*(__m128 *)vec, sseround_mask))),
                     _mm_andnot_ps(sseround_mask, *(__m128 *)vec));
}