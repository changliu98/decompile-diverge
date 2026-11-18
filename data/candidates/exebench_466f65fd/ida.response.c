void __cdecl mlVectorSub(float *a, const float *b)
{
  unsigned int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 3; ++i )
    a[i] = a[i] - b[i];
}