void __cdecl AddArray2(float *a, float *b, int len)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < len; i += 2 )
  {
    b[i] = b[i] + a[i];
    b[i + 1] = b[i + 1] + a[i + 1];
  }
}