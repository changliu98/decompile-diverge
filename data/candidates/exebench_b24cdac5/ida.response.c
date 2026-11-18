void __cdecl vec3_add(float *out, float *a, float *b)
{
  *out = *a + *b;
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
}