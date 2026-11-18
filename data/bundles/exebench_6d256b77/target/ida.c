float __cdecl Intersect(float *S, int i1, int i2, int N)
{
  float interS2; // [rsp+0h] [rbp-2Ch]
  float interS1; // [rsp+4h] [rbp-28h]
  float inter; // [rsp+8h] [rbp-24h]
  int i; // [rsp+Ch] [rbp-20h]

  inter = 0.0;
  interS1 = 0.0;
  interS2 = 0.0;
  for ( i = 0; i < N; ++i )
  {
    if ( S[i + N * i1] == 1.0 && S[i + N * i2] == 1.0 )
      inter = inter + 1.0;
    if ( S[i + N * i1] == 1.0 )
      interS1 = interS1 + 1.0;
    if ( S[i + N * i2] == 1.0 )
      interS2 = interS2 + 1.0;
  }
  if ( interS2 <= interS1 )
    return inter / interS2;
  else
    return inter / interS1;
}