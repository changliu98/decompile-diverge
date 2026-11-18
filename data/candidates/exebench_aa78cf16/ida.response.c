void __cdecl vdiff(float *dst, float *a, float *b)
{
  *dst = *a - *b;
  dst[1] = a[1] - b[1];
  dst[2] = a[2] - b[2];
}