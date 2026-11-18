float __cdecl FDot(float *vec1, float *vec2, int n)
{
  int x; // [rsp+0h] [rbp-1Ch]
  float result; // [rsp+4h] [rbp-18h]

  result = 0.0;
  for ( x = 0; x < n; ++x )
    result = (float)(vec1[x] * vec2[x]) + result;
  return result;
}