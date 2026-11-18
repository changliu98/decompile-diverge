void __cdecl AddArray4(float *a, float *b, int len)
{
  float *p = b;

  for (int i = 0; i < len; i += 4)
  {
    p[0] += a[0];
    p[1] += a[1];
    p[2] += a[2];
    p[3] += a[3];

    a += 4;
    p += 4;
  }
}