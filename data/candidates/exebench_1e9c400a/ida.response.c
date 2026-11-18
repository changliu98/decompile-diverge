void __cdecl myArrayDiv(float *src, float divisor, float *result)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 5; ++i )
    result[i] = src[i] / divisor;
}