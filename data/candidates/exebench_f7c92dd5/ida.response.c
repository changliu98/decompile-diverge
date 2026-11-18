void __cdecl dot4(float *v1x4, float *v2x4, float *results)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int ia; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 4; ++i )
    results[i] = 0.0;
  for ( ia = 0; ia < 4; ++ia )
  {
    *results = (float)(v1x4[ia] * v2x4[ia]) + *results;
    results[1] = (float)(v1x4[ia + 4] * v2x4[ia + 4]) + results[1];
    results[2] = (float)(v1x4[ia + 8] * v2x4[ia + 8]) + results[2];
    results[3] = (float)(v1x4[ia + 12] * v2x4[ia + 12]) + results[3];
  }
}