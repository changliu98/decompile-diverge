void __cdecl vec2_add(float *out, float *a, float *b)
{
  *out = *a + *b;
  out[1] = a[1] + b[1];
}