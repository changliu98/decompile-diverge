void __cdecl vec3_add(float *out, const float *a, const float *b)
{
  out[0] = a[0] + b[0];
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
}