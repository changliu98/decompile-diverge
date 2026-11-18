float dot(float *a, float *b, float *out)
{
  int i;
  *out = 0;
  for (i = 0; i < 4; i++)
    *out += a[i] * b[i];
  return *out;
}