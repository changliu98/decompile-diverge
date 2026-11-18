void __cdecl AddArray2(float *a, float *b, int len)
{
  for (int i = 0; i < len; i += 2)
  {
    b[i] += a[i];
    b[i + 1] += a[i + 1];
  }
}