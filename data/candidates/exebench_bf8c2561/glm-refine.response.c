double __cdecl readDummyArray(double *dummy, unsigned __int64 sizeMB)
{
  unsigned __int64 end = sizeMB >> 3;
  double a = 0.0;
  
  for (unsigned __int64 i = 0; i < end; ++i)
    a += dummy[i];

  // The following SIMD logic computes: a / (double)(end * 2)
  __m128d v_end = _mm_loadl_epi64((const __m128i *)&end);
  __m128d v_one = _mm_load_pd((const double *)xmmword_2010);
  __m128d v_two = _mm_load_pd((const double *)xmmword_2020);

  __m128d v_sum = _mm_add_pd(v_end, v_one); // Equivalent to _mm_sub_pd with negative constants
  __m128d v_result = _mm_sub_pd(v_sum, v_two);

  double divisor = v_result.m128d_f64[0] + v_result.m128d_f64[1];
  *dummy = a / divisor;

  return a;
}