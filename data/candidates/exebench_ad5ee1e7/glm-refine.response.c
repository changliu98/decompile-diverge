void __cdecl cross2(const float *v0, float *r0)
{
  // Extract the second float element (index 1) of v0
  float v0_y = _mm_cvtss_f32(_mm_castsi128_ps(_mm_cvtsi128_si32((__m128i)*((unsigned int *)v0 + 1))));
  
  // Flip the sign bit of v0_y to negate it, and store it in r0[0]
  *(_DWORD *)r0 = *(unsigned int *)&v0_y ^ 0x80000000;
  
  // Store the first float element (index 0) of v0 into r0[1]
  r0[1] = *v0;
}