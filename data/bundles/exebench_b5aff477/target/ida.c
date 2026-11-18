float __cdecl dotprod(float *vector, float *vector2, int len)
{
  int i; // [rsp+0h] [rbp-1Ch]
  float dot; // [rsp+4h] [rbp-18h]

  dot = 0.0;
  for ( i = 0; i < len; ++i )
    dot = (float)(vector[i] * vector2[i]) + dot;
  return dot;
}