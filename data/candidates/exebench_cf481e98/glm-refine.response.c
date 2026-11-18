void __cdecl Sqrt(float x, float *res)
{
  // 'i' is the integer representation of the initial inverse square root guess.
  // The magic number 1597463007 (0x5F3759DF) is a famous constant from the 
  // Fast Inverse Square Root algorithm (Quake III Arena).
  int i = 1597463007 - (SLODWORD(x) >> 1);

  // v2 is used to compute the intermediate value: (0.5 * x) * y0
  // COERCE_UNSIGNED_INT(0.5 * x) creates a 128-bit vector where the lowest 
  // 32-bit lane contains the float bits of (0.5 * x).
  __m128i v2 = (__m128i)COERCE_UNSIGNED_INT(0.5 * x);
  
  // *(float *)v2.m128i_i32 reads the lowest 32-bit float lane, effectively 
  // extracting the (0.5 * x) value and multiplying it by the initial guess y0.
  *(float *)v2.m128i_i32 = (float)(0.5 * x) * *(float *)&i;

  // _mm_cvtsi128_si32(v2) extracts the lowest 32-bit integer from the vector.
  // XORing with 0x80000000 flips the sign bit of the float, negating it.
  // This computes the Newton-Raphson iteration: y1 = y0 * (1.5 - 0.5 * x * y0^2)
  float xa = *(float *)&i * (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000) * *(float *)&i) + 1.5);

  // Clamp to 0 if negative or zero, otherwise return the reciprocal of the 
  // inverse square root to yield the standard square root.
  if ( xa <= 0.0f )
    *res = 0.0f;
  else
    *res = 1.0f / xa;
}