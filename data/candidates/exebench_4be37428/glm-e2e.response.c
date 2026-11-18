void sseround(__m128 *v) {
    // The mask is loaded from a constant memory address (sseround.mask)
    // Based on the bitwise operations, it is typically a vector of 0.5f to implement rounding.
    static const __m128 mask = _mm_set1_ps(0.5f); 
    
    __m128 val = _mm_loadu_ps((const float *)v);
    
    // Truncate the fractional part for values where the mask bit is set
    __m128 truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_and_ps(val, mask)));
    
    // Keep the fractional part for values where the mask bit is not set
    __m128 remainder = _mm_andnot_ps(mask, val);
    
    // Combine both parts and store the result back
    __m128 result = _mm_or_ps(truncated, remainder);
    _mm_storeu_ps((float *)v, result);
}