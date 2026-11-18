void __cdecl mlVectorScaleTo(const float *a, float b, float *result)
{
  unsigned int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 3; ++i )
    result[i] = a[i] * b;
}