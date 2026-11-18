void __cdecl dot(float *v1, float *v2, float *result)
{
  int i; // [rsp+0h] [rbp-1Ch]

  *result = 0.0;
  for ( i = 0; i < 4; ++i )
    *result = (float)(v1[i] * v2[i]) + *result;
}