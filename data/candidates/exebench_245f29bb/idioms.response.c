static inline float nabs_sf(float *x)
{
  return -((__m128i) (unsigned int) *x & ((__m128i) (unsigned int) 0x80000000).m128i_i32);
}