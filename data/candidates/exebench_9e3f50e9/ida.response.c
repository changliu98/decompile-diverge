void __cdecl AddArray4(float *a, float *b, int len)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < len; i += 4 )
  {
    b[i] = b[i] + a[i];
    b[i + 1] = b[i + 1] + a[i + 1];
    b[i + 2] = b[i + 2] + a[i + 2];
    b[i + 3] = b[i + 3] + a[i + 3];
  }
}