void __cdecl sse_dot4(float *v1x4, float *v2x4, float *results)
{
    // Cast float pointers to __m128 pointers for correct 16-byte array indexing
    __m128 *vec1 = (__m128 *)v1x4;
    __m128 *vec2 = (__m128 *)v2x4;
    __m128 *res  = (__m128 *)results;

    // Multiply corresponding 4D vectors element-wise
    __m128 mul0 = _mm_mul_ps(vec1[0], vec2[0]);
    __m128 mul1 = _mm_mul_ps(vec1[1], vec2[1]);
    __m128 mul2 = _mm_mul_ps(vec1[2], vec2[2]);
    __m128 mul3 = _mm_mul_ps(vec1[3], vec2[3]);

    // Interleave low and high halves to prepare for horizontal addition
    __m128 unpck_lo_01 = _mm_unpacklo_ps(mul0, mul1);
    __m128 unpck_hi_01 = _mm_unpackhi_ps(mul0, mul1);
    __m128 unpck_lo_23 = _mm_unpacklo_ps(mul2, mul3);
    __m128 unpck_hi_23 = _mm_unpackhi_ps(mul2, mul3);

    // Add interleaved parts together
    __m128 sum_01 = _mm_add_ps(unpck_lo_01, unpck_hi_01);
    __m128 sum_23 = _mm_add_ps(unpck_lo_23, unpck_hi_23);

    // Final horizontal addition using shuffles
    // 68  == 0x44 == _MM_SHUFFLE(0, 2, 0, 2)
    // 238 == 0xEE == _MM_SHUFFLE(3, 1, 3, 1)
    __m128 shuffle_even = _mm_shuffle_ps(sum_01, sum_23, 68);
    __m128 shuffle_odd  = _mm_shuffle_ps(sum_01, sum_23, 238);

    *res = _mm_add_ps(shuffle_even, shuffle_odd);
}