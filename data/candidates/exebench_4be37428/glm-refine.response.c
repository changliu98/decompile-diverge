void __cdecl sseround(float *vec)
{
    __m128 v = *(__m128 *)vec;

    // 1. Isolate the fractional bits of the floats using the mask
    __m128 frac = _mm_and_ps(v, sseround_mask);

    // 2. Truncate the floats to integers, then convert back to floats.
    //    This zeroes out the fractional bits.
    __m128 int_part = _mm_cvtepi32_ps(_mm_cvtps_epi32(frac));

    // 3. Isolate the bits that are NOT part of the mask (e.g., sign, exponent, integer part)
    __m128 base = _mm_andnot_ps(sseround_mask, v);

    // 4. Combine the rounded integer part with the original base bits
    *(__m128 *)vec = _mm_or_ps(int_part, base);
}