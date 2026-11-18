void __cdecl cross(float *a, float *b, float *c)
{
  // c[0] = a[1] * b[2] - a[2] * b[1]
  c[0] = (a[1] * b[2]) - _mm_cvtss_f32(_mm_castsi128_ps(_mm_set_epi32(0, 0, 0, *(unsigned int*)&a[2] * (unsigned int&)b[1])));

  // c[1] = a[2] * b[0] - a[0] * b[2]
  c[1] = (a[2] * b[0]) - _mm_cvtss_f32(_mm_castsi128_ps(_mm_set_epi32(0, 0, 0, *(unsigned int*)&a[0] * (unsigned int&)b[2])));

  // c[2] = a[0] * b[1] - a[1] * b[0]
  c[2] = (a[0] * b[1]) - _mm_cvtss_f32(_mm_castsi128_ps(_mm_set_epi32(0, 0, 0, *(unsigned int*)&a[1] * (unsigned int&)b[0])));
}