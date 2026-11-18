void __cdecl sse_dot4(float *v1x4, float *v2x4, float *results)
{
  __m128 v3; // xmm1
  __m128 v4; // xmm3
  __m128 v5; // xmm4
  __m128 v6; // xmm0
  __m128 v7; // xmm4
  __m128 v8; // xmm1
  __m128 v9; // xmm2
  __m128 v10; // xmm1

  v3 = _mm_mul_ps(*(__m128 *)(v1x4 + 4), *(__m128 *)(v2x4 + 4));
  v4 = _mm_mul_ps(*(__m128 *)(v1x4 + 12), *(__m128 *)(v2x4 + 12));
  v5 = _mm_mul_ps(*(__m128 *)v1x4, *(__m128 *)v2x4);
  v6 = _mm_unpacklo_ps(v5, v3);
  v7 = _mm_unpackhi_ps(v5, v3);
  v8 = _mm_mul_ps(*(__m128 *)(v1x4 + 8), *(__m128 *)(v2x4 + 8));
  v9 = _mm_add_ps(_mm_unpacklo_ps(v8, v4), _mm_unpackhi_ps(v8, v4));
  v10 = _mm_add_ps(v6, v7);
  *(__m128 *)results = _mm_add_ps(_mm_shuffle_ps(v10, v9, 68), _mm_shuffle_ps(v10, v9, 238));
}