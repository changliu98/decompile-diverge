float __cdecl nabs_sf(float *p)
{
  // Load the float's 32-bit bit-pattern into an SSE register
  __m128i val = _mm_cvtsi32_si128(*(const unsigned int *)p);
  
  // Bitwise OR with 0x80000000 (the sign bit mask) to force the value to be negative.
  // This is semantically identical to the original XOR against the mask, 
  // but more clearly expresses "set the sign bit".
  __m128i neg_val = _mm_or_si128(val, _mm_cvtsi32_si128(0x80000000));
  
  // Extract the 32-bit pattern back and reinterpret it as a float
  float result;
  *(unsigned int *)&result = _mm_cvtsi128_si32(neg_val);
  
  return result;
}